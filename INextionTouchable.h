/*! \file */

#pragma once

#include <functional>
#include "Nextion.h"
#include "INextionWidget.h"

/*!
 * \class INextionTouchable
 * \brief Interface for widgets that can be touched.
 */
class INextionTouchable : public virtual INextionWidget
{
public:
    /*!
   * \typedef NextionCallback
   * \brief Event handler function for display events.
   */
    typedef std::function<void(NextionEventType, INextionTouchable *)> NextionCallback;

    INextionTouchable(Nextion &nex, uint8_t page, uint8_t component,
                      const String &name);
    ~INextionTouchable();

    bool processEvent(uint8_t pageID, uint8_t componentID, uint8_t eventType);

    bool attachCallback(const NextionCallback &cb);
    void detachCallback();

private:
    NextionCallback m_callback;
};
