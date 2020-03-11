/*! \file */

#pragma once

#include "INextionWidget.h"
#include "Nextion.h"
#include "NextionTypes.h"

/*!
 * \class INextionColourable
 * \brief Interface for widgets that can be coloured.
 */
class INextionColourable : public virtual INextionWidget
{
public:
    INextionColourable(Nextion &nex, uint8_t page, uint8_t component, const String &name);

    bool setForegroundColour(uint32_t colour, bool refresh = true);
    bool getForegroundColour(uint32_t &colour);

    bool setEventForegroundColour(uint32_t colour, bool refresh = true);
    bool getEventForegroundColour(uint32_t &colour);

    bool setBackgroundColour(uint32_t colour, bool refresh = true);
    bool getBackgroundColour(uint32_t &colour);

    bool setEventBackgroundColour(uint32_t colour, bool refresh = true);
    bool getEventBackgroundColour(uint32_t &colour);

    bool setColour(const String &type, uint32_t colour, bool refresh);
    bool getColour(const String &type, uint32_t &colour);

    bool afterSet(bool result, bool refresh);
};
