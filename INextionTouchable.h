/*! \file */

#pragma once

#include "Nextion.h"
#include "INextionWidget.h"
#include "INextionCallback.h"
#include "NextionCallbackFunctionHandler.h"

/*!
 * \class INextionTouchable
 * \brief Interface for widgets that can be touched.
 */
class INextionTouchable : public virtual INextionWidget
{
public:
    INextionTouchable(Nextion &nex, uint8_t page, uint8_t component,
                      const String &name);
    ~INextionTouchable();

    bool processEvent(uint8_t pageID, uint8_t componentID, uint8_t eventType);

    bool attachCallback(const NextionCallbackFunctionHandler::NextionFunction &cb);
    bool attachCallback(INextionCallback *obj);
    void detachCallback();

private:
    INextionCallback *m_callback;
};
