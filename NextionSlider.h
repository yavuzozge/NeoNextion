/*! \file */

#pragma once

#include "INextionColourable.h"
#include "INextionNumericalValued.h"
#include "INextionTouchable.h"
#include "Nextion.h"

/*!
 * \class NextionSlider
 * \brief Represents a slider widget.
 */
class NextionSlider : public INextionTouchable,
                      public INextionColourable,
                      public INextionNumericalValued
{
public:
  NextionSlider(Nextion &nex, uint8_t page, uint8_t component,
                const String &name);

  bool getMinValue(uint32_t &value);
  bool setMinValue(uint32_t value);
  bool getMaxValue(uint32_t &value);
  bool setMaxValue(uint32_t value);
};
