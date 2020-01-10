/*! \file */

#pragma once

#include "Nextion.h"

/*!
 * \class INextionWidget
 * \brief Abstract class for all UI widgets.
 *
 * Widget objects act as a adapter/API for the widgets defined in the Nextion
 * Editor software.
 */
class INextionWidget
{
public:
    INextionWidget(Nextion &nex, uint8_t page, uint8_t component,
                   const String &name);
    virtual ~INextionWidget();

    void setInitialVisibility(bool visible);
    uint8_t getPageID();
    uint8_t getComponentID();
    const String& getName() const;

    bool setNumberProperty(const String &propertyName, uint32_t value);
    bool getNumberProperty(const String &propertyName, uint32_t &value);
    bool setPropertyCommand(const String &command, uint32_t value);
    bool setStringProperty(const String &propertyName, const String &value);
    size_t getStringProperty(const String &propertyName, String &buffer);

    bool setVisible(bool visible);
    bool enable(bool enable);

protected:
    void sendCommand(const String &format, ...);
    bool sendCommandWithWait(const String &format, ...);

protected:
    Nextion &m_nextion;    //!< Reference to the Nextion driver
    uint8_t m_pageID;      //!< ID of page this widget is on
    uint8_t m_componentID; //!< Component ID of this widget
    const String m_name;   //!< Name of this widget
    bool m_visible;
};
