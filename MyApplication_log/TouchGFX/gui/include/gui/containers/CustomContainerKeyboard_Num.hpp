#ifndef CUSTOMCONTAINERKEYBOARD_NUM_HPP
#define CUSTOMCONTAINERKEYBOARD_NUM_HPP

#include <gui_generated/containers/CustomContainerKeyboard_NumBase.hpp>

class CustomContainerKeyboard_Num : public CustomContainerKeyboard_NumBase
{
public:
    CustomContainerKeyboard_Num();
    virtual ~CustomContainerKeyboard_Num() {}

    virtual void initialize();

    void keyboard_mas_from_cp1251_to_utf8(char *data_cp1251, Unicode::UnicodeChar *data_utf8, uint16_t len);
    void UpdateButtonKeyboard();
    void UpdateText();

	void ClickButtonCloseKeyboard(void);
	void ClickButtonDelPre(void);
	void ClickButtonEnter(void);
	void action1(void);

	uint8_t count_Container = 5;
protected:
	const char button_123_mas [12] = {'1','2','3','4','5','6','7','8','9','-','0','.'};
};

#endif // CUSTOMCONTAINERKEYBOARD_NUM_HPP
