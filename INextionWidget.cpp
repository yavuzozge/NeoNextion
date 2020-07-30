/*! \file */

#include "INextionWidget.h"

/*!
 * \brief Create a new widget adapter.
 * \param nex Reference to the Nextion driver
 * \param page ID of page this widget is on
 * \param component Component ID of this widget
 * \param name Name of this widget
 */
INextionWidget::INextionWidget(Nextion &nex, uint8_t page, uint8_t component, const String &name)
    : m_nextion(nex)
    , m_pageID(page)
    , m_componentID(component)
    , m_name(name)
    , m_visible(true)
{
}

/*!
 * dtor
 */
INextionWidget::~INextionWidget()
{
}

/*!
 * \brief Sets the initial visibility of the control. Sometimes a control can be
 * hidden when the page is getting initialized. To be able to track visibility
 * correctly, such controls would need to be initialized using this method
 * \param visible initial visibility
 */
void INextionWidget::setInitialVisibility(bool visible)
{
    m_visible = visible;
}

/*!
 * \brief Gets the ID of the page this widget resides on.
 * \return Page ID
 */
uint8_t INextionWidget::getPageID()
{
    return m_pageID;
}

/*!
 * \brief Gets the component ID of this widget.
 * \return Component ID
 */
uint8_t INextionWidget::getComponentID()
{
    return m_componentID;
}

/*!
 * \brief Gets the name of this widget.
 * \return Name
 */
const String &INextionWidget::getName() const
{
    return m_name;
}

/*!
 * \brief Sets the value of a numerical property of this widget.
 * \param propertyName Name of the property
 * \param value Value
 * \return True if successful
 */
bool INextionWidget::setNumberProperty(const String &propertyName, uint32_t value)
{
    return sendCommandWithWait("%s.%s=%d", m_name.c_str(), propertyName.c_str(), value);
}

/*!
 * \brief Gets the value of a numerical property of this widget.
 * \param propertyName Name of the property
 * \param value Reference to variable to store result in
 * \return True if successful
 */
bool INextionWidget::getNumberProperty(const String &propertyName, uint32_t &value)
{
    sendCommand("get %s.%s", m_name.c_str(), propertyName.c_str());
    return m_nextion.receiveNumber(value);
}

/*!
 * \brief Sets the value of a string property of this widget.
 * \param propertyName Name of the property
 * \param value Value
 * \return True if successful
 */
bool INextionWidget::setStringProperty(const String &propertyName, const String &value)
{
    return sendCommandWithWait("%s.%s=\"%s\"", m_name.c_str(), propertyName.c_str(), value.c_str());
}

/*!
 * \brief Gets the value of a string property of this widget.
 * \param propertyName Name of the property
 * \param value Reference to String to store result in
 * \return Actual length of value
 */
size_t INextionWidget::getStringProperty(const String &propertyName, String &buffer)
{
    sendCommand("get %s.%s", m_name.c_str(), propertyName.c_str());
    return m_nextion.receiveString(buffer);
}

void INextionWidget::sendCommand(const String &format, ...)
{
    va_list args;
    va_start(args, format);
    m_nextion.sendCommand(format.c_str(), args);
    va_end(args);
}

bool INextionWidget::sendCommandWithWait(const String &format, ...)
{
    va_list args;
    va_start(args, format);
    m_nextion.sendCommand(format.c_str(), args);
    va_end(args);

    return m_nextion.checkCommandComplete();
}

bool INextionWidget::setPropertyCommand(const String &command, uint32_t value)
{
    m_nextion.sendCommand("%s %s,%d", command.c_str(), m_name.c_str(), value);
    return m_nextion.checkCommandComplete();
}

bool INextionWidget::setVisible(bool visible)
{
    if (visible == m_visible)
    {
        return true;
    }

    if (setPropertyCommand("vis", visible ? 1 : 0))
    {
        m_visible = visible;
        return true;
    }
    return false;
}

bool INextionWidget::enable(bool enable)
{
    return setPropertyCommand("tsw", enable ? 1 : 0);
}
