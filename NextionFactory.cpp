/*! \file */

#include "NextionFactory.h"

#include "NextionButton.h"
#include "NextionCheckbox.h"
#include "NextionCrop.h"
#include "NextionDualStateButton.h"
#include "NextionGauge.h"
#include "NextionHotspot.h"
#include "NextionNumber.h"
#include "NextionPicture.h"
#include "NextionProgressBar.h"
#include "NextionRadioButton.h"
#include "NextionSlider.h"
#include "NextionSlidingText.h"
#include "NextionText.h"
#include "NextionTimer.h"
#include "NextionVariableNumeric.h"
#include "NextionVariableString.h"
#include "NextionWaveform.h"

std::unique_ptr<INextionWidget> NextionFactory::Create(WidgetType widgetType, Nextion &nex, uint8_t page, uint8_t component, const String &name)
{
    switch (widgetType)
    {
    case WidgetType::Button:
        return std::unique_ptr<INextionWidget>(new NextionButton(nex, page, component, name));

    case WidgetType::Checkbox:
        return std::unique_ptr<INextionWidget>(new NextionCheckbox(nex, page, component, name));

    case WidgetType::Crop:
        return std::unique_ptr<INextionWidget>(new NextionCrop(nex, page, component, name));

    case WidgetType::DualStateButton:
        return std::unique_ptr<INextionWidget>(new NextionDualStateButton(nex, page, component, name));

    case WidgetType::Gauge:
        return std::unique_ptr<INextionWidget>(new NextionGauge(nex, page, component, name));

    case WidgetType::Hotspot:
        return std::unique_ptr<INextionWidget>(new NextionHotspot(nex, page, component, name));

    case WidgetType::Number:
        return std::unique_ptr<INextionWidget>(new NextionNumber(nex, page, component, name));

    case WidgetType::Picture:
        return std::unique_ptr<INextionWidget>(new NextionPicture(nex, page, component, name));

    case WidgetType::ProgressBar:
        return std::unique_ptr<INextionWidget>(new NextionProgressBar(nex, page, component, name));

    case WidgetType::RadioButton:
        return std::unique_ptr<INextionWidget>(new NextionRadioButton(nex, page, component, name));

    case WidgetType::Slider:
        return std::unique_ptr<INextionWidget>(new NextionSlider(nex, page, component, name));

    case WidgetType::SlidingText:
        return std::unique_ptr<INextionWidget>(new NextionSlidingText(nex, page, component, name));

    case WidgetType::Text:
        return std::unique_ptr<INextionWidget>(new NextionText(nex, page, component, name));

    case WidgetType::Timer:
        return std::unique_ptr<INextionWidget>(new NextionTimer(nex, page, component, name));

    case WidgetType::VariableNumeric:
        return std::unique_ptr<INextionWidget>(new NextionVariableNumeric(nex, page, component, name));

    case WidgetType::VariableString:
        return std::unique_ptr<INextionWidget>(new NextionVariableString(nex, page, component, name));

    case WidgetType::Waveform:
        return std::unique_ptr<INextionWidget>(new NextionWaveform(nex, page, component, name));

    default:
        return std::unique_ptr<INextionWidget>();
    }
}