/*! \file */

#pragma once

#include "INextionColourable.h"
#include "INextionFontStyleable.h"
#include "INextionStringValued.h"
#include "INextionTouchable.h"
#include "Nextion.h"

/*!
 * \class NextionText
 * \brief Represents a text widget.
 */
class NextionText : public INextionTouchable,
                    public INextionColourable,
                    public INextionStringValued,
                    public INextionFontStyleable
{
public:
  /*!
   * \copydoc INextionWidget::INextionWidget
   */
  NextionText(Nextion &nex, uint8_t page, uint8_t component, const String &name)
      : INextionWidget(nex, page, component, name)
      , INextionTouchable(nex, page, component, name)
      , INextionColourable(nex, page, component, name)
      , INextionStringValued(nex, page, component, name)
      , INextionFontStyleable(nex, page, component, name)
  {
  }
};
