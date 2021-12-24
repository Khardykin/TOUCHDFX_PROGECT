#ifndef CUSTOMCONTAINERKEYBOARD_HPP
#define CUSTOMCONTAINERKEYBOARD_HPP

#include <gui_generated/containers/CustomContainerKeyboardBase.hpp>

class CustomContainerKeyboard : public CustomContainerKeyboardBase
{
public:
    CustomContainerKeyboard();
    virtual ~CustomContainerKeyboard() {}

    virtual void initialize();

    void keyboard_mas_from_cp1251_to_utf8(char *data_cp1251, Unicode::UnicodeChar *data_utf8, uint16_t len);
    void UpdateButtonKeyboard();
    void UpdateText();

    void ClickButtonDelPre(void);
    void ClickButtonDelAll(void);
    void ClickButtonShift(void);
    void ClickButtonCloseKeyboard(void);
    void ClickButtonLanguage(void);
    void ClickButtonSpace(void);
    void ClickButtonEnter(void);
    void ClickButtonABC123(void);
    void action1(void);

    uint8_t count_Container = 30;
protected:
    #define LANG_EN 	(0)
	#define LANG_RUS	(1)

	#define TYPE_123	(0)
	#define TYPE_ABC 	(1)
    uint8_t language_type = LANG_EN;
    uint8_t keyboard_type = TYPE_ABC;
    uint8_t capital_letters = 1;

    int keyboard_mas_utf8[2][33];
#if 0//#ifndef SIMULATOR
	const char button_lang_mas [2][3] = {
			{'E','N',' '},
			{'Р','У','С'}
	};

	const char button_ABC_mas [2][3] = {
			{'A','B','C'},
			{'А','Б','В'}
	};

	const char keyboard_mas_capital_cp1251 [2][33] = 	{
													{'Q','W','E','R','T','Y','U','I','O','P','[',']',
													 'A','S','D','F','G','H','J','K','L',';',' ',
													 'Z','X','C','V','B','N','M',',','.',' '},
													{'Й','Ц','У','К','Е','Н','Г','Ш','Щ','З','Х','Ъ',
													 'Ф','Ы','В','А','П','Р','О','Л','Д','Ж','Э',
													 'Я','Ч','С','М','И','Т','Ь','Б','Ю','.'}
													};
	const char keyboard_mas_upper_cp1251 [2][33] = {
													{'q','w','e','r','t','y','u','i','o','p','[',']',
													'a','s','d','f','g','h','j','k','l',';',' ',
													'z','x','c','v','b','n','m',',','.',' '},
													{'й','ц','у','к','е','н','г','ш','щ','з','х','ъ',
													 'ф','ы','в','а','п','р','о','л','д','ж','э',
													 'я','ч','с','м','и','т','ь','б','ю','.'}
													};
	const char keyboard_mas_123_cp1251 [1][33] = {
													{' ','1','2','3','4','5','6','7','8','9','0','=',
													' ','!','@','#','$','%',':','&','*','(',')',
													'-','+','_',';','"','/','|',',','.','?'}
													};
#else
	char button_lang_mas [2][3] = {0};
	char button_ABC_mas [2][3] = {0};
	char keyboard_mas_capital_cp1251 [2][33] = {0};
	char keyboard_mas_upper_cp1251 [2][33] = {0};
	char keyboard_mas_123_cp1251 [1][33] = {0};
#endif
};

#endif // CUSTOMCONTAINERKEYBOARD_HPP
