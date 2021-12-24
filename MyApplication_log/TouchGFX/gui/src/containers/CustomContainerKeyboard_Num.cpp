#include <gui/containers/CustomContainerKeyboard_Num.hpp>
#include "touchgfx/Utils.hpp"
#include <string.h>

extern uint16_t count_ContainerTextArea;
extern touchgfx::Unicode::UnicodeChar data_ContainerTextArea[40];

CustomContainerKeyboard_Num::CustomContainerKeyboard_Num()
{

}

void CustomContainerKeyboard_Num::keyboard_mas_from_cp1251_to_utf8(
		char *data_cp1251, Unicode::UnicodeChar *data_utf8, uint16_t len) {
//	for (uint16_t i = 0; i < len; i++) {
//		if (data_cp1251[i] >= 0xC0) {
//			data_utf8[i] = (data_cp1251[i] - 0xC0) + 0x0410;
//		}
//		else {
//			data_utf8[i] = data_cp1251[i];
//		}
//	}
}

void CustomContainerKeyboard_Num::initialize()
{
    CustomContainerKeyboard_NumBase::initialize();

    UpdateButtonKeyboard();
}

//==================================================================================================================
void CustomContainerKeyboard_Num::UpdateButtonKeyboard() {
//	Unicode::UnicodeChar keyboard_mas[12];

//	keyboard_mas_from_cp1251_to_utf8((char*) button_123_mas,
//						&keyboard_mas[0], sizeof(button_123_mas));
//
//	customContainerButton_key1.initialize_my(keyboard_mas[0]);
//	customContainerButton_key2.initialize_my(keyboard_mas[1]);
//	customContainerButton_key3.initialize_my(keyboard_mas[2]);
//	customContainerButton_key4.initialize_my(keyboard_mas[3]);
//	customContainerButton_key5.initialize_my(keyboard_mas[4]);
//	customContainerButton_key6.initialize_my(keyboard_mas[5]);
//	customContainerButton_key7.initialize_my(keyboard_mas[6]);
//	customContainerButton_key8.initialize_my(keyboard_mas[7]);
//	customContainerButton_key9.initialize_my(keyboard_mas[8]);
//	customContainerButton_key10.initialize_my(keyboard_mas[9]);
//	customContainerButton_key11.initialize_my(keyboard_mas[10]);
//	customContainerButton_key12.initialize_my(keyboard_mas[11]);
}

//==================================================================================================================
void CustomContainerKeyboard_Num::UpdateText() {
	Unicode::snprintf(textArea1Buffer, count_ContainerTextArea + 1,
			data_ContainerTextArea);
	touchgfx_printf("action1 %s, %d\n\r", textArea1Buffer, count_ContainerTextArea);

	if(count_ContainerTextArea == 1){
		if((textArea1Buffer[1] == button_123_mas[9]) || (textArea1Buffer[1] == button_123_mas[11])){
			count_ContainerTextArea = 0;
		}
	}
	if(count_ContainerTextArea == 0){
		textArea1Buffer[0] = button_123_mas[10];
	}

	textArea1.invalidate();
}

//==================================================================================================================
//When flexButton_del_pre clicked call virtual function
void CustomContainerKeyboard_Num::ClickButtonDelPre() {
	if (count_ContainerTextArea) {
		count_ContainerTextArea -= 1;
		UpdateText();
	}
}

//==================================================================================================================
//When flexButton_enter clicked call virtual function
void CustomContainerKeyboard_Num::ClickButtonEnter() {

}

//==================================================================================================================
//When flexButton_close clicked call virtual function
void CustomContainerKeyboard_Num::ClickButtonCloseKeyboard() {
	count_ContainerTextArea = 0;
	setVisible(false);
	invalidate();
	setXY(-270, 180);
	invalidate();
}

//==================================================================================================================
void CustomContainerKeyboard_Num::action1() {
// textArea1Buffer[] = data_ContainerTextArea[];
	count_ContainerTextArea++;

	//------------------------------------------------------------------------------
	// Проверка на одну запятую
	if((data_ContainerTextArea[count_ContainerTextArea - 1] == button_123_mas[11])){
		if(count_ContainerTextArea == 1){
			data_ContainerTextArea[1] = data_ContainerTextArea[0];
			data_ContainerTextArea[0] = button_123_mas[10];
			count_ContainerTextArea += 1;
		}
		char * str_no = (char*)memchr((char*)&textArea1Buffer[0], button_123_mas[11], 10);
		if(str_no != NULL){
			count_ContainerTextArea -= 1;
			return;
		}
	}
	//------------------------------------------------------------------------------
	// Проверка на ноль в самом начале, если второй символ не запятая, то замена
	if((textArea1Buffer[0] == button_123_mas[10]) &&
			(data_ContainerTextArea[count_ContainerTextArea - 1] != button_123_mas[11]) &&
			(count_ContainerTextArea == 2)){
		// Если не запятая то меняем ноль на новое число в начале
		if(data_ContainerTextArea[count_ContainerTextArea - 1] != button_123_mas[11]){
			data_ContainerTextArea[0] = data_ContainerTextArea[1];
		}
		count_ContainerTextArea = 1;
	}
	//------------------------------------------------------------------------------
	// Проверка на знак минус, только в самом начале
	if((data_ContainerTextArea[count_ContainerTextArea - 1] == button_123_mas[9]) && (count_ContainerTextArea == 1)){
		data_ContainerTextArea[1] = button_123_mas[10];
		count_ContainerTextArea += 1;
	}
	//------------------------------------------------------------------------------
	// Проверка на знак минус, если не в начале, то игнорируем символ
	if((data_ContainerTextArea[count_ContainerTextArea - 1] == button_123_mas[9]) && (count_ContainerTextArea > 1)){
		count_ContainerTextArea -= 1;
		return;
	}
	//------------------------------------------------------------------------------
	// +2 в случае -,
	count_Container = 5;
	if (count_ContainerTextArea > 5) {
		if(data_ContainerTextArea[0] == button_123_mas[9]){
			count_Container += 1;
		}
		char * str_no = (char*)memchr((char*)&textArea1Buffer[0], button_123_mas[11], 10);
		if(str_no != NULL){
			count_Container += 1;
		}
		if(count_ContainerTextArea >= count_Container){
			count_ContainerTextArea = (count_Container);
		}
	}

	UpdateText();


}
