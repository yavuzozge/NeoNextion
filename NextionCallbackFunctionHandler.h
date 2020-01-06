/*! \file */

#pragma once

#include "INextionCallback.h"
#include <functional>

/*!
 * \class NextionCallbackFunctionHandler
 * \brief Event handler for function pointers.
 */
class NextionCallbackFunctionHandler : public INextionCallback
{
public:
    /*!
   * \typedef NextionFunction
   * \brief Event handler function for display events.
   */
    typedef std::function<void(NextionEventType, INextionTouchable *)>
        NextionFunction;

    /*!
   * \brief Creates a new function pointer callback handler.
   * \param f Pointer to callback function
   */
    NextionCallbackFunctionHandler(const NextionFunction &f)
        : m_function(f)
    {
    }

    /*!
   * \copydoc INextionCallback::handleNextionEvent
   *
   * Displatches the event to the function.
   */
    void handleNextionEvent(NextionEventType type, INextionTouchable *widget)
    {
        if (m_function != NULL)
            m_function(type, widget);
    }

private:
    NextionFunction m_function; //!< Pointer to the callback function
};
