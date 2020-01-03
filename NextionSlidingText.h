/*! \file */

#pragma once

#include "INextionColourable.h"
#include "INextionFontStyleable.h"
#include "INextionStringValued.h"
#include "INextionTouchable.h"
#include "Nextion.h"

/*!
 * \class NextionSlidingText
 * \brief Represents a sliding text widget.
 */
class NextionSlidingText : public INextionTouchable,
                           public INextionColourable,
                           public INextionStringValued,
                           public INextionFontStyleable
{
public:
  /*!
   * \copydoc INextionWidget::INextionWidget
   */
  NextionSlidingText(Nextion &nex, uint8_t page, uint8_t component,
                     const String &name);

  bool setScrolling(bool scroll);
  bool isScrolling(bool &scroll);

  bool setScrollDirection(NextionScrollDirection direction);
  bool getScrollDirection(NextionScrollDirection &direction);

  bool setScrollDistance(uint32_t distance);
  bool getScrollDistance(uint32_t &distance);

  bool setScrollDelay(uint32_t delay);
  bool getScrollDelay(uint32_t &delay);
};
