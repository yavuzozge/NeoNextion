/*! \file */

#pragma once

#include "INextionWidget.h"
#include <memory>

enum class WidgetType
{
    Button,
    Checkbox,
    Crop,
    DualStateButton,
    Gauge,
    Hotspot,
    Number,
    Picture,
    ProgressBar,
    RadioButton,
    Slider,
    SlidingText,
    Text,
    Timer,
    VariableNumeric,
    VariableString,
    Waveform
};

class NextionFactory
{
public:
    static std::unique_ptr<INextionWidget> Create(WidgetType widgetType, Nextion &nex, uint8_t page, uint8_t component, const String &name);
};
