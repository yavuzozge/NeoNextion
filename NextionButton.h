/*! \file */

#pragma once

#include "INextionColourable.h"
#include "INextionFontStyleable.h"
#include "INextionStringValued.h"
#include "INextionTouchable.h"
#include "Nextion.h"

/*!
 * \class NextionButton
 * \brief Represents a basic button widget.
 */
class NextionButton : public INextionTouchable,
                      public INextionColourable,
                      public INextionStringValued,
                      public INextionFontStyleable
{
public:
    /*!
   * \copydoc INextionWidget::INextionWidget
   */
    NextionButton(Nextion &nex, uint8_t page, uint8_t component,
                  const String &name)
        : INextionWidget(nex, page, component, name)
        , INextionTouchable(nex, page, component, name)
        , INextionColourable(nex, page, component, name)
        , INextionStringValued(nex, page, component, name)
        , INextionFontStyleable(nex, page, component, name)
    {
    }

    /*!
   * \brief Gets the ID of the currently displayed picture.
   * \param id Picture ID returned
   * \return True if successful
   */
    bool getPictureID(uint16_t &id)
    {
        uint32_t value;
        if (getNumberProperty("pic", value))
        {
            id = value;
            return true;
        }
        return false;
    }

    /*!
   * \brief Sets the picture to be displayed.
   * \param id Picture ID
   * \return True if successful
   */
    bool setPictureID(uint16_t id)
    {
        return setNumberProperty("pic", id);
    }
};
