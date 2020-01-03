/*! \file */

#pragma once

#include "INextionTouchable.h"
#include "Nextion.h"

/*!
 * \class NextionCrop
 * \brief Represents a cropped picture widget.
 */
class NextionCrop : public INextionTouchable
{
public:
  NextionCrop(Nextion &nex, uint8_t page, uint8_t component,
              const String &name);

  bool getPictureID(uint16_t &id);
  bool setPictureID(uint16_t id);
};
