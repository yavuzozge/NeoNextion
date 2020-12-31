/*! \file */

#pragma once

#include "INextionWidget.h"
#include "Nextion.h"
#include "NextionTypes.h"

/*!
 * \class INextionStringValued
 * \brief Interface for widgets that hold a string value.
 *
 * Assumes that the string value is a property named "txt".
 */
class INextionStringValued : public virtual INextionWidget
{
public:
    /*!
   * \copydoc INextionWidget::INextionWidget
   */
    INextionStringValued(Nextion &nex, uint8_t page, uint8_t component, const String &name)
        : INextionWidget(nex, page, component, name)
    {
    }

    /*!
   * \brief Gets the value of the string.
   * \param buffer Pointer to storage to strore string in
   * \return Actual length of string
   * \see INextionStringValued::setText
   */
    size_t getText(String &buffer)
    {
        return getStringProperty("txt", buffer);
    }

    /*!
   * \brief Sets the value of the string.
   * \param buffer Value
   * \return True if successful
   * \see INextionStringValued::getText
   */
    bool setText(const String &buffer)
    {
        return setStringProperty("txt", buffer);
    }

    /*!
   * \brief Sets the text by a numercal value.
   * \param value Numerical value
   * \return True if successful
   * \see INextionStringValued::getTextAsNumber
   */
    bool setTextAsNumber(uint32_t value)
    {
        return setStringProperty("txt", String(value));
    }

    /*!
   * \brief Gets the text parsed as a number.
   * \param value Numerical value
   * \return True if successful
   * \see INextionStringValued::setTextAsNumber
   */
    bool getTextAsNumber(uint32_t& value)
    {
        String buffer;
        if (getStringProperty("txt", buffer))
        {
            value = buffer.toInt();
            return true;
        }
        return false;
    }
};
