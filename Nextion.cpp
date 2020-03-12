/*! \file */

#include "Nextion.h"
#include "INextionTouchable.h"
#include "NextionLogger.h"
#include <FS.h>
#include <MD5Builder.h>
#include <vector>

/*!
 * \brief Determines if the message is solicited vs unsolicited.
 * Unsolicited means it is an event raised by the device on its own (e.g. not
 * due to a request by this lib) \param commandId Message command ID
 */
static bool isMessageUnsolicited(uint8_t commandId)
{
    return commandId == NEX_RET_EVENT_TOUCH_HEAD ||
           commandId == NEX_RET_EVENT_POSITION_HEAD ||
           commandId == NEX_RET_EVENT_SLEEP_POSITION_HEAD;
}

/*!
 * \brief Calculates the message length in a buffer.
 * \param buffer Message buffer
 * \param start Start index
 * \param length Length of the message (including termination bytes) found
 * \return True if a message was found.
 */
static bool calcMessageLength(const std::vector<uint8_t> &buffer, std::size_t start,
                              std::size_t &length)
{
    for (std::size_t i = start + 2; i < buffer.size(); ++i)
    {
        if (buffer[i - 2] == 0xFF && buffer[i - 1] == 0xFF && buffer[i] == 0xFF)
        {
            length = i - start - 2;
            return true;
        }
    }
    return false;
}

/*!
 * \brief Creates a new device driver.
 * \param stream Stream (serial port) the device is connected to
 */
Nextion::Nextion(Stream &stream, uint16_t timeout)
    : m_serialPort(stream)
    , m_timeout(timeout)
    , m_commandResultRequired(false)
{
    m_buffer.reserve(32);
    m_solicitedBuffer.reserve(32);
    m_unsolicitedBuffer.reserve(16);
    m_printBuffer.resize(64);
}

/*!
 * \brief Initialises the device.
 * \return True if initialisation was successful.
 */
bool Nextion::init()
{
    m_buffer.clear();

    bool result1 = requireCommandResult(true);

    sendCommand("page 0");
    bool result2 = checkCommandComplete();

    return result1 && result2;
}

/*!
 * \brief Sets whether the device should return command results
 * \param require If true then sets the device return commands both success nand failure results.
 * \return True if successful
 */
bool Nextion::requireCommandResult(bool require)
{
    if (require)
    {
        sendCommand("bkcmd=3");
        if (checkCommandComplete())
        {
            m_commandResultRequired = true;
            return true;
        }
        return false;
    }
    else
    {
        sendCommand("bkcmd=0");
        m_commandResultRequired = false;
        return true;
    }
}

/*!
 * \brief Polls for unsolicited messages (e.g. touch events) and processes them
 */
void Nextion::poll()
{
    readMessage(false);
    processUnsolicited();
}

/*!
 * \brief Tries to read a solicited message and calls the callback if one is
 * read. 
 * \param callback Callback
 */
void Nextion::readSolicited(
    const std::function<void(const std::vector<uint8_t> &buffer,
                             std::size_t length)> &callback)
{
    readMessage(true);
    std::size_t length = 0;
    if (calcMessageLength(m_solicitedBuffer, 0, length))
    {
        callback(m_solicitedBuffer, length);
        if (m_solicitedBuffer.size() == length + 3)
        {
            m_solicitedBuffer.clear();
        }
        else
        {
            m_solicitedBuffer.erase(m_solicitedBuffer.begin(), m_solicitedBuffer.begin() + length + 3);
        }
    }
    else
    {
        NextionLog("Nextion::readSolicited: No message received.\n");
    }
}

/*!
 * \brief Reads a message from the device and places it to its respective
 * buffer. 
 * \param waitForSolicited Whether to wait for a solicited message
 */
void Nextion::readMessage(bool waitForSolicited)
{
    if (!waitForSolicited && m_serialPort.available() == 0)
    {
        return;
    }

    int read = 0;
    uint64_t startMillis = 0;
    while (true)
    {
        startMillis = millis();
        while (true)
        {
            read = m_serialPort.read();
            if (read >= 0)
            {
                break;
            }
            if (millis() - startMillis > m_timeout)
            {
                return;
            }
        }
        m_buffer.push_back(static_cast<uint8_t>(read));
        std::size_t size = m_buffer.size();
        if (size >= 3 && m_buffer[size - 3] == 0xFF && m_buffer[size - 2] == 0xFF &&
            m_buffer[size - 1] == 0xFF)
        {
            bool isUnsolicited = isMessageUnsolicited(m_buffer[0]);
            std::vector<uint8_t> &targetBuffer = isUnsolicited ? m_unsolicitedBuffer : m_solicitedBuffer;
            targetBuffer.reserve(targetBuffer.size() + size);
            std::copy(m_buffer.cbegin(), m_buffer.cend(), std::back_inserter(targetBuffer));
            m_buffer.clear();

            if (isUnsolicited)
            {
                NextionLog("Nextion::readMessage: Unsolicited message buffer: ");
            }
            else
            {
                NextionLog("Nextion::readMessage: Solicited message buffer: ");
            }
            NextionLogBin(targetBuffer, 0, targetBuffer.size());

            if (!waitForSolicited || !isUnsolicited)
            {
                break;
            }
        }
    }
}

/*!
 * \brief Processes unsolicited messages from unsolicited message buffer.
 */
void Nextion::processUnsolicited()
{
    std::size_t start = 0;
    std::size_t length = 0;
    while (calcMessageLength(m_unsolicitedBuffer, start, length))
    {
        switch (m_unsolicitedBuffer[start])
        {
        case NEX_RET_EVENT_TOUCH_HEAD:
            if (length != 4)
            {
                NextionLog("Nextion::processUnsolicited: NEX_RET_EVENT_TOUCH_HEAD did "
                           "not get all the data.\n");
            }
            else
            {
                NextionLog("Nextion::processUnsolicited: NEX_RET_EVENT_TOUCH_HEAD processed. pageID: %u, componentID: %u, eventType: %u\n",
                           m_unsolicitedBuffer[start + 1],
                           m_unsolicitedBuffer[start + 2],
                           m_unsolicitedBuffer[start + 3]);

                for (auto iter = m_touchableList.cbegin(); iter != m_touchableList.cend(); ++iter)
                {
                    if ((*iter)->processEvent(m_unsolicitedBuffer[start + 1],
                                              m_unsolicitedBuffer[start + 2],
                                              m_unsolicitedBuffer[start + 3]))
                    {
                        NextionLog("Nextion::processUnsolicited: NEX_RET_EVENT_TOUCH_HEAD accepted by: %s\n", (*iter)->getName().c_str());
                    }
                }
            }
            break;

        case NEX_RET_EVENT_POSITION_HEAD:
            NextionLog("Nextion::processUnsolicited: NEX_RET_EVENT_POSITION_HEAD not "
                       "implemented.\n");
            break;

        case NEX_RET_EVENT_SLEEP_POSITION_HEAD:
            NextionLog("Nextion::processUnsolicited: NEX_RET_EVENT_POSITION_HEAD not "
                       "implemented.\n");
            break;

        default:
            NextionLog("Nextion::processUnsolicited: Message not implemented: ");
            NextionLogBin(m_unsolicitedBuffer, start, length);
            break;
        }

        start += length + 3;
    }

    m_unsolicitedBuffer.clear();
}

/*!
 * \brief Resets the device.
 * \return True if successful
 */
bool Nextion::reset()
{
    sendCommand("rest");
    return checkCommandComplete();
}

/*!
 * \brief Refreshes the entire page.
 * \return True if successful
 */
bool Nextion::refresh()
{
    sendCommand("ref 0");
    return checkCommandComplete();
}

/*!
 * \brief Refreshes a specific object.
 * \param objectName Name of the object to refresh
 * \return True if successful
 */
bool Nextion::refresh(const String &objectName)
{
    sendCommand("ref %s", objectName.c_str());
    return checkCommandComplete();
}

/*!
 * \brief Puts the device into sleep mode.
 * \return True if successful
 */
bool Nextion::sleep()
{
    sendCommand("sleep=1");
    return checkCommandComplete();
}

/*!
 * \brief Wakes the device from sleep mode.
 * \return True if successful
 */
bool Nextion::wake()
{
    sendCommand("sleep=0");
    return checkCommandComplete();
}

/*!
 * \brief Gets the current backlight brightness.
 * \param brightness Brightness value (0-100)
 * \return True if successful
 */
bool Nextion::getBrightness(uint16_t &brightness)
{
    sendCommand("get dim");
    uint32_t val;
    if (receiveNumber(val))
    {
        brightness = val;
        return true;
    }
    return false;
}

/*!
 * \brief Sets the backlight brightness.
 * \param brightness Brightness value (0-100)
 * \param persist If set to true value will be set as new power on default
 * \return True if successful
 */
bool Nextion::setBrightness(uint16_t brightness, bool persist)
{
    if (persist)
    {
        sendCommand("dims=%d", brightness);
    }
    else
    {
        sendCommand("dim=%d", brightness);
    }
    return checkCommandComplete();
}

/*!
 * \brief Gets the ID of the current displayed page.
 * \param id Page ID
 * \return True if successful
 */
bool Nextion::getCurrentPage(uint8_t &id)
{
    sendCommand("sendme");
    bool result = false;
    bool exit = false;
    while (!exit)
    {
        readSolicited(
            [this, &id, &result, &exit](const std::vector<uint8_t> &buffer, std::size_t length) {
                if (length == 0)
                {
                    NextionLog("Nextion::getCurrentPage: Reading response timed out.\n");
                    exit = true;
                }
                else if (length == 1)
                {
                    result = checkCommandCompleteIntrn(buffer, length);
                    if (!result)
                    {
                        exit = true;
                    }
                }
                else
                {
                    if (buffer[0] == NEX_RET_CURRENT_PAGE_ID_HEAD)
                    {
                        id = buffer[1];
                        NextionLog("Nextion::getCurrentPage: %d\n", id);
                        result = true;
                        exit = true;
                    }
                    else
                    {
                        NextionLog("Nextion::getCurrentPage: Unexpected response: 0x%x\n", buffer[0]);
                        exit = true;
                    }
                }
            });
    }
    return result;
}

/*!
 * \brief Clears the current display.
 * \param colour Colour to set display to
 * \return True if successful
 */
bool Nextion::clear(uint32_t colour)
{
    sendCommand("cls %d", colour);
    return checkCommandComplete();
}

/*!
 * \brief Draws a pre uploaded picture on the display.
 * \param x X position
 * \param y Y position
 * \param id ID of the picture to display
 * \return True if successful
 */
bool Nextion::drawPicture(uint16_t x, uint16_t y, uint8_t id)
{
    sendCommand("pic %d,%d,%d", x, y, id);
    return checkCommandComplete();
}

/*!
 * \brief Draws a cropped pre uplaoded picture on the display.
 * \param x X position
 * \param y Y position
 * \param w Width
 * \param h Height
 * \param id ID of the picture to display
 * \return True if successful
 */
bool Nextion::drawPicture(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t id)
{
    sendCommand("picq %d,%d,%d,%d,%d", x, y, w, h, id);
    return checkCommandComplete();
}

/*!
 * \brief Draws a string on the display.
 * \param x X position
 * \param y Y position
 * \param w Width
 * \param h Height
 * \param fontID ID of the font to use
 * \param str String to draw
 * \param bgColour Colour of the background of the bounding box
 * \param fgColour Colour of the text
 * \param bgType Background type
 * \param xCentre X alignment
 * \param yCentre Y alignment
 * \return True if successful
 */
bool Nextion::drawStr(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
                      uint8_t fontID, const String &str, uint32_t bgColour,
                      uint32_t fgColour, uint8_t bgType,
                      NextionFontAlignment xCentre,
                      NextionFontAlignment yCentre)
{
    if (str.indexOf('\"') >= 0)
    {
        String strEscaped(str);
        strEscaped.replace("\"", "\\\"");
        sendCommand("xstr %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,\"%s\"", x, y, w, h, fontID,
                    fgColour, bgColour, xCentre, yCentre, bgType, strEscaped.c_str());
    }
    else
    {
        sendCommand("xstr %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,\"%s\"", x, y, w, h, fontID,
                    fgColour, bgColour, xCentre, yCentre, bgType, str.c_str());
    }
    return checkCommandComplete();
}

/*!
 * \brief Draws a line on the display.
 * \param x1 X position of first vertex
 * \param y1 Y position of first vertex
 * \param x2 X position of second vertex
 * \param y2 Y position of second vertex
 * \param colour Colour
 * \return True if successful
 */
bool Nextion::drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                       uint32_t colour)
{
    sendCommand("line %d,%d,%d,%d,%d", x1, y1, x2, y2, colour);
    return checkCommandComplete();
}

/*!
 * \brief Draws a rectangle on the display.
 * \param x X position
 * \param y Y position
 * \param w Width
 * \param h Height
 * \param filled If the rectangle should be filled with a solid colour
 * \param colour Colour
 * \return True if successful
 */
bool Nextion::drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool filled, uint32_t colour)
{
    if (filled)
    {
        sendCommand("draw %d,%d,%d,%d,%d", x, y, x + w, y + h, colour);
    }
    else
    {
        sendCommand("fill %d,%d,%d,%d,%d", x, y, x + w, y + h, colour);
    }
    return checkCommandComplete();
}

/*!
 * \brief Draws a circle on the display.
 * \param x X position
 * \param y Y position
 * \param r Radius
 * \param filled If the rectangle should be filled with a solid colour
 * \param colour Colour
 * \return True if successful
 */
bool Nextion::drawCircle(uint16_t x, uint16_t y, uint16_t r, bool filled, uint32_t colour)
{
    if (filled)
    {
        sendCommand("cirs %d,%d,%d,%d", x, y, r, colour);
    }
    else
    {
        sendCommand("cir %d,%d,%d,%d", x, y, r, colour);
    }
    return checkCommandComplete();
}

/*!
 * \brief Adds a INextionTouchable to the list of registered touchable
 *        elements.
 * \param touchable Pointer to the INextionTouchable
 *
 * Required for touch events from an INextionTouchable to be polled.
 *
 * Should be called automatically by INextionTouchable::INextionTouchable.
 */
void Nextion::registerTouchable(INextionTouchable *touchable)
{
    m_touchableList.push_front(touchable);
}

/*!
 * \brief Removes a INextionTouchable to the list of registered touchable
 *        elements.
 * \param touchable Pointer to the INextionTouchable
 *
 * Should be called automatically by INextionTouchable::~INextionTouchable.
 */
void Nextion::unregisterTouchable(INextionTouchable *touchable)
{
    m_touchableList.remove(touchable);
}

/*!
 * \brief Sends a command to the device.
 * \param command Command to send
 * \param commandSize The size of the command to send (excluding null character)
 */
void Nextion::sendCommand(const char *command, std::size_t commandSize)
{
    NextionLog("Nextion::sendCommand: Sending %u bytes -> ", commandSize);
    NextionLogStr(command, 0, commandSize);

    m_serialPort.write(command, commandSize);
    m_serialPort.write(0xFF);
    m_serialPort.write(0xFF);
    m_serialPort.write(0xFF);
}

/*!
 * \brief Sends a command to the device.
 * \param command Command to send
 */
void Nextion::sendCommand(const String &command)
{
    sendCommand(command.c_str(), command.length());
}

void Nextion::sendCommand(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    sendCommand(format, args);
    va_end(args);
}

void Nextion::sendCommand(const char *format, va_list args)
{
    int written = vsnprintf(&m_printBuffer[0], m_printBuffer.size(), format, args);
    if(written < 0)
    {
        NextionLog("Nextion::sendCommand: Failed to format the string");
    }
    else 
    {
        if (written >= m_printBuffer.size())
        {
            m_printBuffer.resize(written + 1);
            vsnprintf(&m_printBuffer[0], m_printBuffer.size(), format, args);
        }

        sendCommand(&m_printBuffer[0], written);
    }
}

/*!
 * \brief Checks if the last command was successful.
 * \return True if command was successful
 */
bool Nextion::checkCommandCompleteIntrn(const std::vector<uint8_t> &buffer, std::size_t length)
{
    if (length == 0)
    {
        NextionLog("Nextion::checkCommandComplete: Reading response timed out.\n");
        return false;
    }
    switch (buffer[0])
    {
    case NEX_RET_CMD_FAILED:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_CMD_FAILED\n");
        return false;
    case NEX_RET_CMD_FINISHED:
        NextionLog("Nextion::checkCommandComplete: OK\n");
        return true;
    case NEX_RET_INVALID_COMPONENT_ID:
        NextionLog(
            "Nextion::checkCommandComplete: NEX_RET_INVALID_COMPONENT_ID\n");
        return false;
    case NEX_RET_INVALID_PAGE_ID:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_INVALID_PAGE_ID\n");
        return false;
    case NEX_RET_INVALID_PICTURE_ID:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_INVALID_PICTURE_ID\n");
        return false;
    case NEX_RET_INVALID_FONT_ID:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_INVALID_FONT_ID\n");
        return false;
    case NEX_RET_INVALID_FILE_OP:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_INVALID_FILE_OP\n");
        return false;
    case NEX_RET_INVALID_CRC:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_INVALID_CRC\n");
        return false;
    case NEX_RET_INVALID_BAUD:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_INVALID_BAUD\n");
        return false;
    case NEX_RET_INVALID_WAVEFORM_ID_CHANNEL:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_INVALID_WAVEFORM_ID_CHANNEL\n");
        return false;
    case NEX_RET_INVALID_VARIABLE:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_INVALID_VARIABLE\n");
        return false;
    case NEX_RET_INVALID_OPERATION:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_INVALID_OPERATION\n");
        return false;
    case NEX_RET_FAILED_TO_ASSIGN:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_FAILED_TO_ASSIGN\n");
        return false;
    case NEX_RET_EEPROM_OP_FAILED:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_EEPROM_OP_FAILED\n");
        return false;
    case NEX_RET_INVALID_NUM_PARAMS:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_INVALID_NUM_PARAMS\n");
        return false;
    case NEX_RET_IO_OP_FAILED:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_IO_OP_FAILED\n");
        return false;
    case NEX_RET_INVALID_ESCAPE_CHAR:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_INVALID_ESCAPE_CHAR\n");
        return false;
    case NEX_RET_VAR_NAME_TOO_LONG:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_VAR_NAME_TOO_LONG\n");
        return false;
    case NEX_RET_SERIAL_BUFFER_OVERFLOW:
        NextionLog("Nextion::checkCommandComplete: NEX_RET_SERIAL_BUFFER_OVERFLOW\n");
        return false;
    default:
        NextionLog("Nextion::checkCommandComplete: Unexpected response: 0x%x\n",
                   buffer[0]);
        return false;
    }
}

/*!
 * \brief Checks if the last command was successful.
 * \return True if command was successful
 */
bool Nextion::checkCommandComplete()
{
    if (!m_commandResultRequired)
    {
        return true;
    }

    bool result = false;
    readSolicited([this, &result](const std::vector<uint8_t> &buffer, std::size_t length) {
        result = checkCommandCompleteIntrn(buffer, length);
    });

    return result;
}

/*!
 * \brief Receive a number from the device.
 * \param number Pointer to the number to store received number in
 * \return True if receive was successful
 */
bool Nextion::receiveNumber(uint32_t &number)
{
    bool result = false;
    readSolicited([&result, &number](const std::vector<uint8_t> &buffer, std::size_t length) {
        if (length < 5)
        {
            NextionLog("Nextion::receiveNumber: Reading response timed out.\n");
            return;
        }
        if (buffer[0] == NEX_RET_NUMBER_HEAD)
        {
            number = (buffer[4] << 24) | (buffer[3] << 16) | (buffer[2] << 8) | (buffer[1]);
            NextionLog("Nextion::receiveNumber: value: %d\n", number);
            result = true;
            return;
        }

        NextionLog("Nextion::receiveNumber: Unexpected response.\n");
    });

    return result;
}

/*!
 * \brief Receive a string from the device.
 * \param buffer Pointer to buffer to store string in
 * \return Actual length of string received
 */
size_t Nextion::receiveString(String &strBuffer)
{
    size_t length = 0;
    readSolicited([&length, &strBuffer](const std::vector<uint8_t> &buffer, std::size_t length) {
        if (length == 0)
        {
            NextionLog("Nextion::receiveString: Reading response timed out.\n");
            return;
        }
        if (buffer[0] != NEX_RET_STRING_HEAD)
        {
            NextionLog("Nextion::receiveString: Unexpected response.\n");
            return;
        }
        strBuffer.reserve(length - 1);
        for (uint8_t i = 1; i < length; ++i)
        {
            strBuffer.concat((char)buffer[i]);
        }

        strBuffer.trim();
        NextionLog("Nextion::receiveString: value: '%s'\n", strBuffer.c_str());
        length = strBuffer.length();
    });

    return length;
}

bool Nextion::waitForFirmwareChunkAck() const
{
    uint64_t start = millis();
    int read = -1;
    while (read == -1 && millis() - start <= 500)
    {
        if (m_serialPort.available())
        {
            read = m_serialPort.read();
            return read == 5;
        }
    }
    return false;
}

bool Nextion::uploadFirmware(Stream &stream, size_t size, uint32_t baudrate, String &md5Out, size_t bufferSize)
{
    const size_t chunkSize = 4096;
    md5Out.clear();

    sendCommand("whmi-wri %u,%u,res0", size, baudrate);

    // Flush the serial port first, regardless since
    // updating the firmware successfully takes the highest priority.
    while (m_serialPort.available())
    {
        m_serialPort.read();
    }

    if (!waitForFirmwareChunkAck())
    {
        NextionLog("Nextion::uploadFirmware: Expected ACK for whmi-wri not received, aborting.\n");
        return false;
    }

    MD5Builder md5;
    md5.begin();

    std::vector<uint8_t> buffer(bufferSize);
    size_t read = 0;
    size_t written = 0;
    size_t totalWritten = 0;
    size_t chunkRemaining = chunkSize;
    while (true)
    {
        read = stream.readBytes(&buffer[0], std::min(chunkRemaining, buffer.size()));
        if (read > 0)
        {
            written = m_serialPort.write(&buffer[0], read);
            totalWritten += written;
            if (written != read)
            {
                NextionLog("Nextion::uploadFirmware: Failed to write all the bytes. "
                           "Written: %u\n",
                           written);
                return false;
            }
            md5.add(&buffer[0], read);
        }
        else if (read == 0)
        {
            break;
        }

        chunkRemaining -= read;
        if (chunkRemaining == 0 && totalWritten != size)
        {
            chunkRemaining = chunkSize;
            if (!waitForFirmwareChunkAck())
            {
                NextionLog("Nextion::uploadFirmware: Expected chunk ACK not received, aborting.\n");
                return false;
            }
        }
    }

    if (!waitForFirmwareChunkAck())
    {
        NextionLog("Nextion::uploadFirmware: Expected final ACK not received, aborting.\n");
        return false;
    }

    if (totalWritten == size)
    {
        NextionLog("Nextion::uploadFirmware: Stream sent. Total bytes written: %u, "
                   "expected size: %u\n",
                   totalWritten, size);

        md5.calculate();
        md5Out = md5.toString();

        NextionLog("Nextion::uploadFirmware:Waiting for NEX_RET_EVENT_LAUNCHED.\n");
        uint8_t launchedEvent[] = {NEX_RET_EVENT_LAUNCHED, 0xFF, 0xFF, 0xFF};
        uint64_t start = millis();
        while (millis() - start < 20000)
        {
            if (m_serialPort.find(launchedEvent, sizeof(launchedEvent)))
            {
                NextionLog("Nextion::uploadFirmware:Launch event detected.\n");
                return true;
            }
        }

        NextionLog("Nextion::uploadFirmware:Launch event was not detected.\n");
        return false;
    }
    else
    {
        NextionLog("Nextion::uploadFirmware:Stream terminated prematurely, aborting.\n");
        return false;
    }
}