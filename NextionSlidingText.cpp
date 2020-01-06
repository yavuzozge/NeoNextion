/*! \file */

#include "NextionSlidingText.h"

/*!
 * \copydoc INextionWidget::INextionWidget
 */
NextionSlidingText::NextionSlidingText(Nextion &nex, uint8_t page,
                                       uint8_t component, const String &name)
    : INextionWidget(nex, page, component, name)
    , INextionTouchable(nex, page, component, name)
    , INextionColourable(nex, page, component, name)
    , INextionStringValued(nex, page, component, name)
    , INextionFontStyleable(nex, page, component, name)
{
}

bool NextionSlidingText::setScrolling(bool scroll)
{
    return setNumberProperty("en", scroll);
}

bool NextionSlidingText::isScrolling(bool &scroll)
{
    uint32_t value;
    if (getNumberProperty("en", value))
    {
        scroll = value;
        return true;
    }
    return false;
}

bool NextionSlidingText::setScrollDirection(NextionScrollDirection direction)
{
    return setNumberProperty("dir", direction);
}

bool NextionSlidingText::getScrollDirection(NextionScrollDirection &direction)
{
    uint32_t value;
    if (getNumberProperty("dir", value))
    {
        direction = static_cast<NextionScrollDirection>(value);
        return true;
    }
    return false;
}

bool NextionSlidingText::setScrollDistance(uint32_t distance)
{
    return setNumberProperty("dis", distance);
}

bool NextionSlidingText::getScrollDistance(uint32_t &distance)
{
    return getNumberProperty("dis", distance);
}

bool NextionSlidingText::setScrollDelay(uint32_t delay)
{
    return setNumberProperty("tim", delay);
}

bool NextionSlidingText::getScrollDelay(uint32_t &delay)
{
    return getNumberProperty("tim", delay);
}
