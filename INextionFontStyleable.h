/*! \file */

#pragma once

#include "INextionWidget.h"
#include "Nextion.h"
#include "NextionTypes.h"

/*!
 * \class INextionFontStyleable
 * \brief Interface for widgets that can have their fonts styled.
 */
class INextionFontStyleable : public virtual INextionWidget
{
public:
    INextionFontStyleable(Nextion &nex, uint8_t page, uint8_t component,
                          const String &name);

    bool setFont(uint8_t id, bool refresh = true);
    bool getFont(uint8_t &id);

    bool setHAlignment(NextionFontAlignment align, bool refresh = true);
    bool getHAlignment(NextionFontAlignment &align);

    bool setVAlignment(NextionFontAlignment align, bool refresh = true);
    bool getVAlignment(NextionFontAlignment &align);

    bool afterSet(bool result, bool refresh);
};
