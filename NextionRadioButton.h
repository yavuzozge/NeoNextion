/*! \file */

#pragma once

#include "INextionBooleanValued.h"
#include "INextionColourable.h"
#include "INextionTouchable.h"
#include "Nextion.h"

/*!
 * \class NextionRadioButton
 * \brief Represents a basic button widget.
 */
class NextionRadioButton : public INextionTouchable,
                           public INextionColourable,
                           public INextionBooleanValued
{
public:
    /*!
   * \copydoc INextionWidget::INextionWidget
   */
    NextionRadioButton(Nextion &nex, uint8_t page, uint8_t component,
                       const String &name)
        : INextionWidget(nex, page, component, name)
        , INextionTouchable(nex, page, component, name)
        , INextionColourable(nex, page, component, name)
        , INextionBooleanValued(nex, page, component, name)
    {
    }
};
