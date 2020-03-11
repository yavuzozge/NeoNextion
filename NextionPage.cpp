/*! \file */

#include "NextionPage.h"

/*!
 * \copydoc INextionWidget::INextionWidget
 */
NextionPage::NextionPage(Nextion &nex, uint8_t page, uint8_t component, const String &name)
    : INextionWidget(nex, page, component, name)
{
}

/*!
 * \brief Sets this page as the currently displayed page.
 * \return True if successful
 */
bool NextionPage::show()
{
    return sendCommandWithWait("page %s", m_name.c_str());
}

/*!
 * \brief Determines if this page is currently displayed.
 * \param currentlyShown Whether the page is shown
 * \return True if successful
 */
bool NextionPage::isShown(bool &currentlyShown)
{
    uint8_t id;
    if (m_nextion.getCurrentPage(id))
    {
        currentlyShown = id == m_pageID;
        return true;
    }
    return false;
}
