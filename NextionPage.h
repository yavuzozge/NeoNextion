/*! \file */

#pragma once

#include "INextionWidget.h"
#include "Nextion.h"

/*!
 * \class NextionPage
 * \brief Represents a page of widgets.
 */
class NextionPage : public INextionWidget
{
public:
    NextionPage(Nextion &nex, uint8_t page, uint8_t component,
                const String &name);

    bool show();
    bool isShown(bool currentlyShown);
};
