/*! \file */

#include "NextionPage.h"

/*!
 * \copydoc INextionWidget::INextionWidget
 */
NextionPage::NextionPage(Nextion &nex, uint8_t page, uint8_t component,
                         const String &name)
    : INextionWidget(nex, page, component, name)
{
}

/*!
 * \brief Sets this page as the currently displayed page.
 * \return True if successful
 */
bool NextionPage::show()
{
  bool shown;
  if (!isShown(shown))
  {
    return false;
  }
  if(shown)
  {
    return true;
  }
  return sendCommandWithWait("page %s", m_name.c_str());
}

/*!
 * \brief Determines if this page is currently displayed.
 * \param shown Whether the page is shown
 * \return True if successful
 */
bool NextionPage::isShown(bool shown)
{
  uint8_t id;
  if(m_nextion.getCurrentPage(id))
  {
    shown = id == m_pageID;
    return true;
  }
  return false;
}
