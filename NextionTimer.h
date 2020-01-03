/*! \file */

#pragma once

#include "INextionTouchable.h"
#include "Nextion.h"

/*!
 * \class NextionTimer
 * \brief Represents a timer.
 */
class NextionTimer : public INextionTouchable
{
public:
  NextionTimer(Nextion &nex, uint8_t page, uint8_t component,
               const String &name);

  bool getCycle(uint32_t &cycle);
  bool setCycle(uint32_t cycle);

  bool enable();
  bool disable();
};
