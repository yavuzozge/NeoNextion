/*! \file */

#pragma once

#include "INextionWidget.h"
#include "Nextion.h"
#include "NextionTypes.h"

/*!
 * \class INextionNumericalValued
 * \brief Interface for widgets that store a numerical value.
 *
 * Assumes that the numerical value is a property named "val".
 */
class INextionNumericalValued : public virtual INextionWidget
{
public:
    /*!
   * \copydoc INextionWidget::INextionWidget
   */
    INextionNumericalValued(Nextion &nex, uint8_t page, uint8_t component, const String &name)
        : INextionWidget(nex, page, component, name)
    {
    }

    /*!
   * \brief Gets the numerical value.
   * \param value Resulting value
   * \return True if successful
   * \see INextionNumericalValued::getValue
   */
    bool getValue(uint32_t &value)
    {
        return getNumberProperty("val", value);
    }

    /*!
   * \brief Sets the numerical value.
   * \param value Value
   * \return True if successful
   * \see INextionNumericalValued::setValue
   */
    bool setValue(uint32_t value)
    {
        return setNumberProperty("val", value);
    }
};
