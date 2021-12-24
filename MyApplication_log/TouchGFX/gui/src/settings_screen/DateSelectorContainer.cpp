#include <gui/settings_screen/DateSelectorContainer.hpp>

DateSelectorContainer::DateSelectorContainer()
{
    datePicker.setXY(0, 0);
    add(datePicker);
}

DateSelectorContainer::~DateSelectorContainer()
{
}

void DateSelectorContainer::setDate(uint16_t year, uint8_t month, uint8_t day)
{
    datePicker.setDay((day - 1), 16, EasingEquations::backEaseOut);
    datePicker.setMonth(month, 16, EasingEquations::backEaseOut);
    if(year >= 120){
    	datePicker.setYear(year - 120, 16, EasingEquations::backEaseOut);
    }
    else{
    	datePicker.setYear(0, 16, EasingEquations::backEaseOut);
    }
}

uint16_t DateSelectorContainer::getYear()
{
    return (datePicker.getYear() + 120);
}

uint8_t DateSelectorContainer::getMonth()
{
    return datePicker.getMonth();
}

uint8_t DateSelectorContainer::getDay()
{
    return (datePicker.getDay() + 1);
}
