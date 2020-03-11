/*! \file */

#pragma once

#include "INextionColourable.h"
#include "INextionNumericalValued.h"
#include "INextionTouchable.h"
#include "Nextion.h"

/*!
 * \class NextionGauge
 * \brief Represents a gauge widget/
 */
class NextionGauge : public INextionTouchable,
                     public INextionColourable,
                     public INextionNumericalValued
{
public:
    /*!
   * \copydoc INextionWidget::INextionWidget
   */
    NextionGauge(Nextion &nex, uint8_t page, uint8_t component, const String &name)
        : INextionWidget(nex, page, component, name)
        , INextionTouchable(nex, page, component, name)
        , INextionColourable(nex, page, component, name)
        , INextionNumericalValued(nex, page, component, name)
    {
    }
};
