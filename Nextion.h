/*! \file */

#pragma once

#if defined(SPARK) || defined(PLATFORM_ID)
#include "application.h"
extern char *itoa(int a, char *buffer, unsigned char radix);
#else
#include <Arduino.h>
#endif
#include <FS.h>

#include <WString.h>
#include <forward_list>
#include <list>
#include <vector>
#include <functional>

#include "NextionTypes.h"

class INextionTouchable;

/*!
 * \class Nextion
 * \brief Driver for a physical Nextion device.
 */
class Nextion
{
public:
    Nextion(Stream &stream, uint16_t timeout = 1000);

    bool init();
    bool requireCommandResult(bool require);
    void poll();
    bool reset();

    bool refresh();
    bool refresh(const String &objectName);

    bool sleep();
    bool wake();

    bool getBrightness(uint16_t &brightness);
    bool setBrightness(uint16_t brightness, bool persist = false);

    bool getCurrentPage(uint8_t &id);

    bool clear(uint32_t colour = NEX_COL_WHITE);
    bool drawPicture(uint16_t x, uint16_t y, uint8_t id);
    bool drawPicture(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t id);

    bool drawStr(uint16_t x,
                 uint16_t y,
                 uint16_t w,
                 uint16_t h,
                 uint8_t fontID,
                 const String &str,
                 uint32_t bgColour,
                 uint32_t fgColour,
                 uint8_t bgType,
                 NextionFontAlignment xCentre,
                 NextionFontAlignment yCentre);

    inline bool drawStr(uint16_t x,
                        uint16_t y,
                        uint16_t w,
                        uint16_t h,
                        uint8_t fontID,
                        const String &str,
                        uint32_t fgColour)
    {
        return drawStr(x, y, w, h, fontID, str, NEX_COL_BLACK, fgColour, NEX_BG_SOLIDCOLOUR, NEX_FA_LEFT_UP, NEX_FA_LEFT_UP);
    }

    inline bool drawStr(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t fontID, const String &str, uint32_t bgColour, uint32_t fgColour)
    {
        return drawStr(x, y, w, h, fontID, str, bgColour, fgColour, NEX_BG_SOLIDCOLOUR, NEX_FA_LEFT_UP, NEX_FA_LEFT_UP);
    }

    inline bool drawStrCentered(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t fontID, const String &str, uint32_t fgColour)
    {
        return drawStr(x, y, w, h, fontID, str, NEX_COL_BLACK, fgColour, NEX_BG_SOLIDCOLOUR, NEX_FA_CENTRE, NEX_FA_CENTRE);
    }

    inline bool drawStrCentered(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t fontID,
                                const String &str, uint32_t bgColour, uint32_t fgColour)
    {
        return drawStr(x, y, w, h, fontID, str, bgColour, fgColour, NEX_BG_SOLIDCOLOUR, NEX_FA_CENTRE, NEX_FA_CENTRE);
    }

    bool drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t colour);
    bool drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool filled, uint32_t colour);
    bool drawCircle(uint16_t x, uint16_t y, uint16_t r, bool filled, uint32_t colour);

    void registerTouchable(INextionTouchable *touchable);
    void unregisterTouchable(INextionTouchable *touchable);
    void sendCommand(const String &command);
    void sendCommand(const char *format, ...);
    void sendCommand(const char *format, va_list args);
    bool checkCommandComplete();
    bool receiveNumber(uint32_t &number);
    size_t receiveString(String &buffer);
    bool uploadFirmware(Stream &stream, size_t size, uint32_t baudrate,
                        String &md5Out, size_t bufferSize = 128);

private:
    Stream &m_serialPort; //!< Serial port device is attached to
    uint64_t m_timeout;
    std::forward_list<INextionTouchable *>
        m_touchableList; //!< Linked list of INextionTouchable
    std::vector<uint8_t> m_buffer;
    std::vector<uint8_t> m_solicitedBuffer;
    std::vector<uint8_t> m_unsolicitedBuffer;
    bool m_commandResultRequired;

    bool checkCommandCompleteIntrn(const std::vector<uint8_t> &buffer,
                                   std::size_t length);
    void readSolicited(const std::function<void(const std::vector<uint8_t> &buffer,
                                                std::size_t length)> &callback);
    void readMessage(bool waitForSolicited);
    void processUnsolicited();
    bool waitForFirmwareChunkAck() const;
};
