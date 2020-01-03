/*! \file */

#include "NextionPicture.h"
#include "INextionWidget.h"

/*!
 * \copydoc INextionWidget::INextionWidget
 */
NextionPicture::NextionPicture(Nextion &nex, uint8_t page, uint8_t component,
                               const String &name)
    : INextionWidget(nex, page, component, name)
    , INextionTouchable(nex, page, component, name)
{
}

/*!
 * \brief Gets the ID of the currently displayed picture.
 * \param id Picture ID
 * \return True if successful
 */
bool NextionPicture::getPictureID(uint16_t &id)
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
bool NextionPicture::setPictureID(uint16_t id)
{
  return setNumberProperty("pic", id);
}
