#ifndef CUSTOMCONTAINERTABLELOG_HPP
#define CUSTOMCONTAINERTABLELOG_HPP

#include <gui_generated/containers/CustomContainerTableLogBase.hpp>


extern "C"{
#include "parce_archiv.h"
}

class CustomContainerTableLog : public CustomContainerTableLogBase
{
public:
    CustomContainerTableLog();
    virtual ~CustomContainerTableLog() {}

    virtual void initialize();

    void UpdateLog(TileInfoTypeDef * data);
    void UpdateLog_clear(void);

protected:
    touchgfx::Unicode::UnicodeChar NamesTypeChannel[2][10] = {
    		{0x041F, 0x0435, 0x0442, 0x043B, 0x044F},//Петля
			{}
    };

    touchgfx::Unicode::UnicodeChar NamesStLoop[2][10] = {
    		{0x004F, 0x004B},			//OK
			{0x041E, 0x0431, 0x0440, 0x044B, 0x0432}//Обрыв
    };

    touchgfx::Unicode::UnicodeChar NamesUnit[2][10] = {
    		{0x004C, 0x0045, 0x004C},	//LEL
			{0x0056, 0x004F, 0x004C}	//VOL
    };

    touchgfx::Unicode::UnicodeChar NamesStCur[1][5] = {
    		{0x004E, 0x004F}			//NO
    };

    touchgfx::Unicode::UnicodeChar NamesErr[2][10] = {
    		{},
			{}
    };
    touchgfx::Unicode::UnicodeChar NamesGas[2][10] = {
			{},
			{}
	};


};

#endif // CUSTOMCONTAINERTABLELOG_HPP
