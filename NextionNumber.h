/*! \file */

#pragma once

#include "INextionColourable.h"
#include "INextionFontStyleable.h"
#include "INextionNumericalValued.h"
#include "INextionTouchable.h"
#include "Nextion.h"

/*!
 * \class NextionNumber
 * \brief Represents a number widget.
 */
class NextionNumber : public INextionTouchable,
                      public INextionColourable,
                      public INextionNumericalValued,
                      public INextionFontStyleable
{
public:
    /*!
   * \copydoc INextionWidget::INextionWidget
   */
    NextionNumber(Nextion &nex, uint8_t page, uint8_t component, const String &name)
        : INextionWidget(nex, page, component, name)
        , INextionTouchable(nex, page, component, name)
        , INextionColourable(nex, page, component, name)
        , INextionNumericalValued(nex, page, component, name)
        , INextionFontStyleable(nex, page, component, name)
    {
    }
};
