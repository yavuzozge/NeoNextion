/*! \file */

#pragma once

#include "NextionTypes.h"
#include "INextionTouchable.h"

/*!
 * \class INextionCallback
 * \brief Interface for classes that handle callbacks from a display device.
 */
class INextionCallback
{
public:
  INextionCallback()
  {
  }

  /*!
   * \brief Handle a callback.
   * \param type Event type
   * \param widget Pointer to the widget that fired the event
   */
  virtual void handleNextionEvent(NextionEventType type,
                                  INextionTouchable *widget) = 0;
};
