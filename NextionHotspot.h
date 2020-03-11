/*! \file */

#pragma once

#include "INextionTouchable.h"
#include "INextionWidget.h"
#include "Nextion.h"

/*!
 * \class NextionHotspot
 * \brief Represents a hotspot widget.
 */
class NextionHotspot : public INextionTouchable
{
public:
    /*!
   * \copydoc INextionWidget::INextionWidget
   */
    NextionHotspot(Nextion &nex, uint8_t page, uint8_t component, const String &name)
        : INextionWidget(nex, page, component, name)
        , INextionTouchable(nex, page, component, name)
    {
    }
};
