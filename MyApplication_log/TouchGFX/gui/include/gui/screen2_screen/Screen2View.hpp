#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();


    void function2();
    void function3();
    void functionSaveSettings();
    void functionSaveModalWindow();
    void CallbackcustomContainerKeyboard();
    void CallbackcustomContainerKeyboard_Num();

    void keyboard_mas_from_utf8_to_cp1251(Unicode::UnicodeChar *data_utf8, char *data_cp1251, uint16_t len) ;

    uint16_t count_flexButton_text_outBuffer = 0;
    uint16_t count_flexButton_text_outBuffer_num = 0;
    protected:
};

#endif // SCREEN2VIEW_HPP
