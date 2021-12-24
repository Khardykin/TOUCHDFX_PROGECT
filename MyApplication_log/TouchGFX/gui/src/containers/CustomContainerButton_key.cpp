#include <gui/containers/CustomContainerButton_key.hpp>
#include "touchgfx/Utils.hpp"

uint16_t count_ContainerTextArea = 0;
touchgfx::Unicode::UnicodeChar data_ContainerTextArea[40];

CustomContainerButton_key::CustomContainerButton_key()
{

}

void CustomContainerButton_key::initialize()
{
    CustomContainerButton_keyBase::initialize();
}

void CustomContainerButton_key::functionButtonClick()
{
	touchgfx_printf("function1 %s\n\r", flexButton_keyboardBuffer);
	data_ContainerTextArea[count_ContainerTextArea] = flexButton_keyboardBuffer[0];
}

void CustomContainerButton_key::initialize_my(Unicode::UnicodeChar text)
{
	flexButton_keyboardBuffer[0] = text;
	flexButton_keyboard.invalidate();
}
