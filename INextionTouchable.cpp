/*! \file */

#include "INextionTouchable.h"

/*!
 * \copydoc INextionWidget::INextionWidget
 */
INextionTouchable::INextionTouchable(Nextion &nex, uint8_t page, uint8_t component, const String &name)
    : INextionWidget(nex, page, component, name)
{
    m_nextion.registerTouchable(this);
}

/*!
 * \brief dtor
 */
INextionTouchable::~INextionTouchable()
{
    m_nextion.unregisterTouchable(this);
}

/*!
 * \brief Processes a touch event.
 * \param pageID Page ID of touch event
 * \param componentID Component ID of touch event
 * \param eventType Type of touch event
 * \return True if the event effects this widget
 */
bool INextionTouchable::processEvent(uint8_t pageID, uint8_t componentID, uint8_t eventType)
{
    if (pageID != m_pageID)
    {
        return false;
    }

    if (componentID != m_componentID)
    {
        return false;
    }

    switch (eventType)
    {
    case NEX_EVENT_PUSH:
    case NEX_EVENT_POP:
        if (m_callback)
        {
            m_callback((NextionEventType)eventType, this);
        }
        return true;

    default:
        return false;
    }
}

/*!
 * \brief Attaches a callback function to this widget.
 * \param callback Callback function
 * \return True if successful
 * \see INextionTouchable::detachCallback
 */
bool INextionTouchable::attachCallback(const NextionCallback &callback)
{
    if (!callback)
    {
        return false;
    }

    m_callback = callback;
    return true;
}

/*!
 * \brief Removes the callback handler from this widget
 */
void INextionTouchable::detachCallback()
{
    m_callback = nullptr;
}
