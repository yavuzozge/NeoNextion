/*! \file */

#include "NextionSlider.h"

/*!
 * \copydoc INextionWidget::INextionWidget
 */
NextionSlider::NextionSlider(Nextion &nex, uint8_t page, uint8_t component,
                             const String &name)
    : INextionWidget(nex, page, component, name)
    , INextionTouchable(nex, page, component, name)
    , INextionColourable(nex, page, component, name)
    , INextionNumericalValued(nex, page, component, name)
{
}

/*!
 * \brief Gets the minimum value.
 * \param value Value
 * \return True if successful
 */
bool NextionSlider::getMinValue(uint32_t &value)
{
    return getNumberProperty("minval", value);
}

/*!
 * \brief Sets the minimum value.
 * \param value Value
 * \return True if successful
 */
bool NextionSlider::setMinValue(uint32_t value)
{
    return setNumberProperty("minval", value);
}

/*!
 * \brief Gets the maximum value.
 * \param value Value
 * \return True if successful
 */
bool NextionSlider::getMaxValue(uint32_t &value)
{
    return getNumberProperty("maxval", value);
}

/*!
 * \brief Sets the maximum value.
 * \param value Value
 * \return True if successful
 */
bool NextionSlider::setMaxValue(uint32_t value)
{
    return setNumberProperty("maxval", value);
}
