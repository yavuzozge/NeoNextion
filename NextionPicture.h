/*! \file */

#pragma once

#include "INextionTouchable.h"
#include "Nextion.h"

/*!
 * \class NextionPicture
 * \brief Represents a full size picture widget.
 */
class NextionPicture : public INextionTouchable
{
public:
  NextionPicture(Nextion &nex, uint8_t page, uint8_t component,
                 const String &name);

  bool getPictureID(uint16_t &id);
  bool setPictureID(uint16_t id);
};
