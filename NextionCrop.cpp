/*! \file */

#include "NextionCrop.h"
#include "INextionWidget.h"

/*!
 * \copydoc INextionWidget::INextionWidget
 */
NextionCrop::NextionCrop(Nextion &nex, uint8_t page, uint8_t component, const String &name)
    : INextionWidget(nex, page, component, name)
    , INextionTouchable(nex, page, component, name)
{
}

/*!
 * \copydoc NextionPicture::getPictureID
 */
bool NextionCrop::getPictureID(uint16_t &id)
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
 * \copydoc NextionPicture::setPictureID
 */
bool NextionCrop::setPictureID(uint16_t id)
{
    return setNumberProperty("pic", id);
}
