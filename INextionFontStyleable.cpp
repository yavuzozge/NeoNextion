/*! \file */

#include "INextionFontStyleable.h"

/*!
 * \copydoc INextionWidget::INextionWidget
 */
INextionFontStyleable::INextionFontStyleable(Nextion &nex, uint8_t page,
                                             uint8_t component,
                                             const String &name)
    : INextionWidget(nex, page, component, name)
{
}

/*!
 * \brief Sets the active font for the text.
 * \param id Font ID
 * \param refresh If the widget should be refreshed
 * \return True if successful
 * \see INextionFontStyleable::getFont
 */
bool INextionFontStyleable::setFont(uint8_t id, bool refresh)
{
    return afterSet(setNumberProperty("font", id), refresh);
}

/*!
 * \brief Gets the active font for the text.
 * \param id Font ID
 * \return True if successful
 * \see INextionFontStyleable::setFont
 */
bool INextionFontStyleable::getFont(uint8_t &id)
{
    uint32_t value;
    if (getNumberProperty("font", value))
    {
        id = value;
        return true;
    }
    return false;
}

/*!
 * \brief Sets the horizontal alignment of the text.
 * \param align Alignment
 * \param refresh If the widget should be refreshed
 * \return True if successful
 * \see INextionFontStyleable::getHAlignment
 */
bool INextionFontStyleable::setHAlignment(NextionFontAlignment align,
                                          bool refresh)
{
    return afterSet(setNumberProperty("xcen", align), refresh);
}

/*!
 * \brief Gets the horizontal alignment of the text.
 * \param align Alignment
 * \return True if successful
 * \see INextionFontStyleable::setHAlignment
 */
bool INextionFontStyleable::getHAlignment(NextionFontAlignment &align)
{
    uint32_t value;
    if (getNumberProperty("xcen", value))
    {
        align = static_cast<NextionFontAlignment>(value);
        return true;
    }
    return false;
}

/*!
 * \brief Sets the vertical alignment of the text.
 * \param align Alignment
 * \param refresh If the widget should be refreshed
 * \return True if successful
 * \see INextionFontStyleable::getVAlignment
 */
bool INextionFontStyleable::setVAlignment(NextionFontAlignment align,
                                          bool refresh)
{
    return afterSet(setNumberProperty("ycen", align), refresh);
}

/*!
 * \brief Gets the vertical alignment of the text.
 * \param align Alignment
 * \return True if successful
 * \see INextionFontStyleable::setVAlignment
 */
bool INextionFontStyleable::getVAlignment(NextionFontAlignment &align)
{
    uint32_t value;
    if (getNumberProperty("ycen", value))
    {
        align = static_cast<NextionFontAlignment>(value);
        return true;
    }
    return false;
}

/*!
 * \brief Handles refreshing the page after a style has been changed.
 * \param result Success of style change
 * \param refresh If the widget should be refreshed
 * \return True if successful
 */
bool INextionFontStyleable::afterSet(bool result, bool refresh)
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
