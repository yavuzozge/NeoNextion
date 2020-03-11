/*! \file */

#include "INextionColourable.h"

/*!
 * \copydoc INextionWidget::INextionWidget
 */
INextionColourable::INextionColourable(Nextion &nex,
                                       uint8_t page,
                                       uint8_t component,
                                       const String &name)
    : INextionWidget(nex, page, component, name)
{
}

/*!
 * \brief Sets the normal foreground colour.
 * \param colour Colour
 * \param refresh If the widget should be refreshed
 * \return True if successful
 * \see INextionColourable::getForegroundColour
 */
bool INextionColourable::setForegroundColour(uint32_t colour, bool refresh)
{
    return setColour("pco", colour, refresh);
}

/*!
 * \brief Gets the normal foreground colour.
 * \param colour Colour
 * \return True if successful
 * \see INextionColourable::setForegroundColour
 */
bool INextionColourable::getForegroundColour(uint32_t &colour)
{
    return getColour("pco", colour);
}

/*!
 * \brief Sets the foreground colour when a touch event is active.
 * \param colour Colour
 * \param refresh If the widget should be refreshed
 * \return True if successful
 * \see INextionColourable::getEventForegroundColour
 */
bool INextionColourable::setEventForegroundColour(uint32_t colour, bool refresh)
{
    return setColour("pco2", colour, refresh);
}

/*!
 * \brief Gets the foreground colour when a touch event is active.
 * \param colour Colour
 * \return True if successful
 * \see INextionColourable::setEventForegroundColour
 */
bool INextionColourable::getEventForegroundColour(uint32_t &colour)
{
    return getColour("pco2", colour);
}

/*!
 * \brief Sets the normal background colour.
 * \param colour Colour
 * \param refresh If the widget should be refreshed
 * \return True if successful
 * \see INextionColourable::getBackgroundColour
 */
bool INextionColourable::setBackgroundColour(uint32_t colour, bool refresh)
{
    return setColour("bco", colour, refresh);
}

/*!
 * \brief Gets the normal background colour.
 * \param colour Colour
 * \return True if successful
 * \see INextionColourable::setBackgroundColour
 */
bool INextionColourable::getBackgroundColour(uint32_t &colour)
{
    return getColour("bco", colour);
}

/*!
 * \brief Sets the background colour when a touch event is active.
 * \param colour Colour
 * \param refresh If the widget should be refreshed
 * \return True if successful
 * \see INextionColourable::getEventBackgroundColour
 */
bool INextionColourable::setEventBackgroundColour(uint32_t colour, bool refresh)
{
    return setColour("bco2", colour, refresh);
}

/*!
 * \brief Sets the background colour when a touch event is active.
 * \param colour Colour
 * \return True if successful
 * \see INextionColourable::setEventBackgroundColour
 */
bool INextionColourable::getEventBackgroundColour(uint32_t &colour)
{
    return getColour("bco2", colour);
}

/*!
 * \brief Sets a colour by its property name.
 * \param type Property name
 * \param colour Colour
 * \param refresh If the widget should be refreshed
 * \return True if successful
 */
bool INextionColourable::setColour(const String &type, uint32_t colour,
                                   bool refresh)
{
    return afterSet(setNumberProperty(type, colour), refresh);
}

/*!
 * \brief Gets a colour by its property name.
 * \param type Property name
 * \param colour Colour
 * \return True if successful
 * \see INextionColourable::setColour
 */
bool INextionColourable::getColour(const String &type, uint32_t &colour)
{
    return getNumberProperty(type, colour);
}

/*!
 * \brief Handles refreshing the page after a colour has been changed.
 * \param result Success of colour set
 * \param refresh If the widget should be refreshed
 * \return True if successful
 * \see INextionColourable::getColour
 */
bool INextionColourable::afterSet(bool result, bool refresh)
{
    if (result)
    {
        if (refresh)
        {
            m_nextion.refresh(m_name);
            return m_nextion.checkCommandComplete();
        }
        else
            return true;
    }
    else
        return false;
}
