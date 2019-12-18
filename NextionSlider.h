/*! \file */

#ifndef __NEONEXTION_NEXTIONSLIDER
#define __NEONEXTION_NEXTIONSLIDER

#include "Nextion.h"
#include "INextionTouchable.h"
#include "INextionColourable.h"
#include "INextionNumericalValued.h"

/*!
 * \class NextionSlider
 * \brief Represents a slider widget.
 */
class NextionSlider : public INextionTouchable,
                      public INextionColourable,
                      public INextionNumericalValued
{
public:
  NextionSlider(Nextion &nex, uint8_t page, uint8_t component, const String &name);

  uint32_t getMinValue();
  bool setMinValue(uint32_t value);
  uint32_t getMaxValue();
  bool setMaxValue(uint32_t value);
};

#endif
