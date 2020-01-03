/*! \file */

#include "NextionTimer.h"

/*!
 * \copydoc INextionWidget::INextionWidget
 */
NextionTimer::NextionTimer(Nextion &nex, uint8_t page, uint8_t component,
                           const String &name)
    : INextionWidget(nex, page, component, name)
    , INextionTouchable(nex, page, component, name)
{
}

/*!
 * \brief Gets the cycle time of the timer.
 * \param cycle Time in ms
 * \return True if successful
 */
bool NextionTimer::getCycle(uint32_t &cycle)
{
  return getNumberProperty("tim", cycle);
}

/*!
 * \brief Sets the cycle time of the timer.
 * \param cycle Time in ms
 * \return True if successful
 */
bool NextionTimer::setCycle(uint32_t cycle)
{
  if (cycle < 50)
    return false;
  return setNumberProperty("tim", cycle);
}

/*!
 * \brief Enable/start the timer.
 * \return True if successful
 */
bool NextionTimer::enable()
{
  return setNumberProperty("en", 1);
}

/*!
 * \brief Disable/stop the timer.
 * \return True if successful
 */
bool NextionTimer::disable()
{
  return setNumberProperty("en", 0);
}
