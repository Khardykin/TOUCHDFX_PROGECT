#include <gui/screen2_screen/Screen2View.hpp>
#include <stdlib.h>


extern uint16_t count_ContainerTextArea;
extern touchgfx::Unicode::UnicodeChar data_ContainerTextArea[40];


Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();

    customContainerKeyboard1.initialize();
    customContainerKeyboard1.setVisible(false);
    customContainerKeyboard1.invalidate();

    customContainerKeyboard_Num1.initialize();
    customContainerKeyboard_Num1.setVisible(false);
    customContainerKeyboard_Num1.invalidate();

    modalWindow1.setVisible(false);
    modalWindow1.invalidate();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}


void Screen2View::keyboard_mas_from_utf8_to_cp1251(
		Unicode::UnicodeChar *data_utf8, char *data_cp1251, uint16_t len) {
	for (uint16_t i = 0; i < len; i++) {
		if (data_utf8[i] >= 0x0410) {
			data_cp1251[i] = (char)((data_utf8[i] - 0x0410) + 0xC0);
		}
		else {
			data_cp1251[i] = (char)(data_utf8[i]);
		}
	}
}

//==================================================================================================================
// callback по нажатию кнопки enter на конетейнере CustomContainerKeyboard
void Screen2View::CallbackcustomContainerKeyboard()
{
	// Обновление значений в элементе экрана через контейнере CustomContainerKeyboard
	count_flexButton_text_outBuffer = count_ContainerTextArea;
	Unicode::snprintf(flexButton_text_outBuffer, count_ContainerTextArea+1, data_ContainerTextArea);
	flexButton_text_out.invalidate();
}

//==================================================================================================================
// Открыть клавиатуру по нажатию на поле
void Screen2View::function2()
{
	customContainerKeyboard1.initialize();

	// Заполнение буфера обмена контейнера CustomContainerKeyboard, текущим значением элемента экрана
	Unicode::snprintf(data_ContainerTextArea, count_flexButton_text_outBuffer+1, flexButton_text_outBuffer);
	customContainerKeyboard1.count_Container = 30;				// Установка максимальной длины контейнера
	count_ContainerTextArea = count_flexButton_text_outBuffer; 	// Установка длины буффера обмена элемента экрана
	customContainerKeyboard1.UpdateText();						// Обновление текста в контейнере CustomContainerKeyboard

	customContainerKeyboard1.setVisible(true);
	customContainerKeyboard1.setXY(0, 180);
	customContainerKeyboard1.invalidate();
	// Закрываем другую клавиатуру, если она открыта
	if(customContainerKeyboard_Num1.isVisible()){
		customContainerKeyboard_Num1.setVisible(false);
		customContainerKeyboard_Num1.invalidate();
	}
}

//==================================================================================================================
// callback по нажатию кнопки enter на конетейнере customContainerKeyboard_Num
float data_float = 0.0;
float data_float_max = 100.0;
void Screen2View::CallbackcustomContainerKeyboard_Num()
{
	// Обновление значений в элементе экрана через контейнере customContainerKeyboard_Num
	// Если последний символ запятая то инкрементируем длину(удаляем символ)
	if(data_ContainerTextArea[count_ContainerTextArea - 1] == '.'){
		count_ContainerTextArea -= 1;
	}

//	char mas_cp1251[count_ContainerTextArea];
//	keyboard_mas_from_utf8_to_cp1251(data_ContainerTextArea, mas_cp1251, count_ContainerTextArea);
//	data_float = atof((char*)mas_cp1251);
//	if(data_float > data_float_max)
//	{
//		Unicode::snprintfFloat(data_ContainerTextArea, 40,  "%.2f", data_float_max);
//		count_ContainerTextArea = Unicode::strlen(data_ContainerTextArea);
//		customContainerKeyboard_Num1.UpdateText();
//	}


	count_flexButton_text_outBuffer_num = count_ContainerTextArea;
	Unicode::snprintf(flexButton_text_out_NumBuffer, count_ContainerTextArea+1, data_ContainerTextArea);
	flexButton_text_out_Num.invalidate();


}

//==================================================================================================================
// Открыть клавиатуру по нажатию на поле
void Screen2View::function3()
{
	customContainerKeyboard_Num1.initialize();

	// Заполнение буфера обмена контейнера CustomContainerKeyboard, текущим значением элемента экрана
	Unicode::snprintf(data_ContainerTextArea, count_flexButton_text_outBuffer_num+1, flexButton_text_out_NumBuffer);
	customContainerKeyboard_Num1.count_Container = 5;				// Установка максимальной длины контейнера
	count_ContainerTextArea = count_flexButton_text_outBuffer_num; 	// Установка длины буффера обмена элемента экрана
	customContainerKeyboard_Num1.UpdateText();						// Обновление текста в контейнере CustomContainerKeyboard

	customContainerKeyboard_Num1.setVisible(true);
	customContainerKeyboard_Num1.setXY(260, 180);
	customContainerKeyboard_Num1.invalidate();
	// Закрываем другую клавиатуру, если она открыта
	if(customContainerKeyboard1.isVisible()){
		customContainerKeyboard1.setVisible(false);
		customContainerKeyboard1.invalidate();
	}
}

//==================================================================================================================
// Кнопка сохранить
void Screen2View::functionSaveSettings()
{
	modalWindow1.setVisible(true);
	modalWindow1.invalidate();
}

//==================================================================================================================
// Кнопка сохранить (да\нет)
void Screen2View::functionSaveModalWindow()
{
	modalWindow1.setVisible(false);
	modalWindow1.invalidate();
}
