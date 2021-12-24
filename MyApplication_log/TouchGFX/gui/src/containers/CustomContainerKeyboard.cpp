#include <gui/containers/CustomContainerKeyboard.hpp>
#include "touchgfx/Utils.hpp"

extern uint16_t count_ContainerTextArea;
extern touchgfx::Unicode::UnicodeChar data_ContainerTextArea[40];

CustomContainerKeyboard::CustomContainerKeyboard() {

}

void CustomContainerKeyboard::keyboard_mas_from_cp1251_to_utf8(
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

void CustomContainerKeyboard::initialize() {
	CustomContainerKeyboardBase::initialize();

	count_ContainerTextArea = 0; // Очистка буфера обмена элемента контейнера CustomContainerKeyboard
	capital_letters = 1;			// Включение заглавных букв

	UpdateText();
	UpdateButtonKeyboard();
}

//==================================================================================================================
void CustomContainerKeyboard::UpdateButtonKeyboard() {
//	Unicode::UnicodeChar keyboard_mas[2][33];
//	if (keyboard_type == TYPE_ABC) {
//		if (capital_letters) {
//			keyboard_mas_from_cp1251_to_utf8(
//					(char*) keyboard_mas_capital_cp1251, &keyboard_mas[0][0],
//					sizeof(keyboard_mas_capital_cp1251));
//		}
//		else {
//			keyboard_mas_from_cp1251_to_utf8((char*) keyboard_mas_upper_cp1251,
//					&keyboard_mas[0][0], sizeof(keyboard_mas_upper_cp1251));
//		}
//	}
//	else {
//		keyboard_mas_from_cp1251_to_utf8((char*) keyboard_mas_123_cp1251,
//				&keyboard_mas[language_type][0],
//				sizeof(keyboard_mas_123_cp1251));
//	}
//	customContainer1.initialize_my(keyboard_mas[language_type][0]);
//	customContainer2.initialize_my(keyboard_mas[language_type][1]);
//	customContainer3.initialize_my(keyboard_mas[language_type][2]);
//	customContainer4.initialize_my(keyboard_mas[language_type][3]);
//	customContainer5.initialize_my(keyboard_mas[language_type][4]);
//	customContainer6.initialize_my(keyboard_mas[language_type][5]);
//	customContainer7.initialize_my(keyboard_mas[language_type][6]);
//	customContainer8.initialize_my(keyboard_mas[language_type][7]);
//	customContainer9.initialize_my(keyboard_mas[language_type][8]);
//	customContainer10.initialize_my(keyboard_mas[language_type][9]);
//	customContainer11.initialize_my(keyboard_mas[language_type][10]);
//	customContainer12.initialize_my(keyboard_mas[language_type][11]);
//	customContainer1_1.initialize_my(keyboard_mas[language_type][12]);
//	customContainer2_1.initialize_my(keyboard_mas[language_type][13]);
//	customContainer3_1.initialize_my(keyboard_mas[language_type][14]);
//	customContainer4_1.initialize_my(keyboard_mas[language_type][15]);
//	customContainer5_1.initialize_my(keyboard_mas[language_type][16]);
//	customContainer6_1.initialize_my(keyboard_mas[language_type][17]);
//	customContainer7_1.initialize_my(keyboard_mas[language_type][18]);
//	customContainer8_1.initialize_my(keyboard_mas[language_type][19]);
//	customContainer9_1.initialize_my(keyboard_mas[language_type][20]);
//	customContainer10_1.initialize_my(keyboard_mas[language_type][21]);
//	customContainer11_1.initialize_my(keyboard_mas[language_type][22]);
//	customContainer1_2.initialize_my(keyboard_mas[language_type][23]);
//	customContainer2_2.initialize_my(keyboard_mas[language_type][24]);
//	customContainer3_2.initialize_my(keyboard_mas[language_type][25]);
//	customContainer4_2.initialize_my(keyboard_mas[language_type][26]);
//	customContainer5_2.initialize_my(keyboard_mas[language_type][27]);
//	customContainer6_2.initialize_my(keyboard_mas[language_type][28]);
//	customContainer7_2.initialize_my(keyboard_mas[language_type][29]);
//	customContainer8_2.initialize_my(keyboard_mas[language_type][30]);
//	customContainer9_2.initialize_my(keyboard_mas[language_type][31]);
//	customContainer10_2.initialize_my(keyboard_mas[language_type][32]);
}

//==================================================================================================================
void CustomContainerKeyboard::UpdateText() {
	Unicode::snprintf(textArea1Buffer, count_ContainerTextArea + 1,
			data_ContainerTextArea);
	touchgfx_printf("action1 %s, %d\n\r", textArea1Buffer, count_ContainerTextArea);
	textArea1.invalidate();
}

//==================================================================================================================
//When flexButton_del_pre clicked call virtual function
void CustomContainerKeyboard::ClickButtonDelPre() {
	if (count_ContainerTextArea) {
		count_ContainerTextArea -= 1;
		UpdateText();
	}
	if ((count_ContainerTextArea == 0) && (capital_letters == 0)) {
		capital_letters = 1;
		UpdateButtonKeyboard();
	}
}

//==================================================================================================================
//When flexButton_del_all clicked call virtual function
void CustomContainerKeyboard::ClickButtonDelAll() {
	count_ContainerTextArea = 0;
	capital_letters = 1;
	UpdateText();
	UpdateButtonKeyboard();
}

//==================================================================================================================
//When flexButton_shift clicked call virtual function
void CustomContainerKeyboard::ClickButtonShift() {
	if (capital_letters) {
		capital_letters = 0;
	}
	else {
		capital_letters = 1;
	}
	UpdateButtonKeyboard();
}

//==================================================================================================================
//When flexButton_close clicked call virtual function
void CustomContainerKeyboard::ClickButtonCloseKeyboard() {
	count_ContainerTextArea = 0;
	setVisible(false);
	invalidate();
	setXY(0, 480);
	invalidate();
}

//==================================================================================================================
//When flexButton_language clicked call virtual function
void CustomContainerKeyboard::ClickButtonLanguage() {
	if (language_type == LANG_RUS) {
		language_type = LANG_EN;
	}
	else {
		language_type = LANG_RUS;
	}
	keyboard_mas_from_cp1251_to_utf8((char*) button_lang_mas[language_type], &flexButton_languageBuffer[0], sizeof(button_lang_mas)/2);
	flexButton_language.invalidate();
	UpdateButtonKeyboard();
}

//==================================================================================================================
//When flexButton_space clicked call virtual function
void CustomContainerKeyboard::ClickButtonSpace() {
	data_ContainerTextArea[count_ContainerTextArea] = flexButton_spaceBuffer[0];
	action1();
}

//==================================================================================================================
//When flexButton_enter clicked call virtual function
void CustomContainerKeyboard::ClickButtonEnter() {

}

//==================================================================================================================
//When flexButton_ABC_123 clicked call virtual function button_ABC_mas
void CustomContainerKeyboard::ClickButtonABC123() {
	if (keyboard_type == TYPE_ABC) {
		keyboard_type = TYPE_123;
		Unicode::snprintf(flexButton_ABC_123Buffer, FLEXBUTTON_ABC_123_SIZE, "123");
	}
	else {
		keyboard_type = TYPE_ABC;
		keyboard_mas_from_cp1251_to_utf8((char*) button_ABC_mas[language_type], &flexButton_ABC_123Buffer[0], sizeof(button_ABC_mas)/2);
	}
	flexButton_ABC_123.invalidate();
	UpdateButtonKeyboard();
}

//==================================================================================================================
void CustomContainerKeyboard::action1() {
//	textArea1Buffer[] = data_ContainerTextArea[];
	count_ContainerTextArea++;
	if (count_ContainerTextArea == 1) {
		capital_letters = 0;
		UpdateButtonKeyboard();
	}
	//-----------------------------------------------------------
	if (count_ContainerTextArea == count_Container) {
		count_ContainerTextArea = (count_Container);
	}
	//-----------------------------------------------------------

	UpdateText();

}
