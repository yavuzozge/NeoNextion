/*! \file */

#pragma once

#include "INextionColourable.h"
#include "INextionTouchable.h"
#include "Nextion.h"

/*!
 * \class NextionWaveform
 * \brief Represents a waveform widget.
 */
class NextionWaveform : public INextionTouchable, public INextionColourable
{
public:
    NextionWaveform(Nextion &nex, uint8_t page, uint8_t component,
                    const String &name);

    bool addValue(uint8_t channel, uint8_t value);

    bool setChannelColour(uint8_t channel, uint32_t colour, bool refresh = true);
    bool getChannelColour(uint8_t channel, uint32_t &colour);

    bool setGridColour(uint32_t colour, bool refresh = true);
    bool getGridColour(uint32_t &colour);

    bool setGridWidth(uint16_t width);
    bool getGridWidth(uint16_t &width);

    bool setGridHeight(uint16_t height);
    bool getGridHeight(uint16_t &height);
};
