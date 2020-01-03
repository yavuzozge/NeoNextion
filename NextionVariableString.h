/*! \file */

#pragma once

#include "INextionStringValued.h"
#include "INextionWidget.h"
#include "Nextion.h"

/*!
 * \class NextionVariableString
 * \brief Represents a string variable.
 */
class NextionVariableString : public INextionStringValued
{
public:
  /*!
   * \copydoc INextionWidget::INextionWidget
   */
  NextionVariableString(Nextion &nex, uint8_t page, uint8_t component,
                        const String &name)
      : INextionWidget(nex, page, component, name)
      , INextionStringValued(nex, page, component, name)
  {
  }
};
