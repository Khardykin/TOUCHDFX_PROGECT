#include <gui/screen1_screen/Screen1View.hpp>
#include "touchgfx/Utils.hpp"

#ifndef SIMULATOR
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mb_regs_decoder.h>
#endif

#define TEST_COUNT_LOG

#include "time.h"

Screen1View::Screen1View():
//Define the viewcallback by tying it to a handler
CallbackListItemSelected(this, &Screen1View::handleListItemSelected)
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    touchgfx_printf("setupScreen");

    //----------------------------------------------------------------------
    static time_p tmp;
    static struct tm timeptr;
    read_start_stop_state_archiv(&time_start_fil, &time_stop_fil);

    //-----
    //Test data filter
//    time_stop_fil = 1735039935;
//    time_start_fil = time_stop_fil;
    //-----
    tmp = time_stop_fil;
	timeptr = *gmtime(&tmp);
	dateSelectorContainerStop.setPosition(250, 50, modalWindow1.getWidth(), modalWindow1.getHeight());
	dateSelectorContainerStop.setDate(timeptr.tm_year, timeptr.tm_mon, timeptr.tm_mday);
	modalWindow1.add(dateSelectorContainerStop);

    tmp = time_start_fil;
    timeptr = *gmtime(&tmp);
    dateSelectorContainerStart.setPosition(0, 50, modalWindow1.getWidth(), modalWindow1.getHeight());
    dateSelectorContainerStart.setDate(timeptr.tm_year, timeptr.tm_mon, timeptr.tm_mday);
    modalWindow1.add(dateSelectorContainerStart);
    functionOkFilDataTime();

    for(uint8_t i = 0; i < 10; i++){
		mas_ContainerTableLog[i]->setVisible(false);
	}
    //----------------------------------------------------------------------
    channel_num_fil = 0;
    ch_type_fil 	= 0;
    loop_state_fil 	= 0;
    units_fil 		= 0;
    thld_state_fil 	= 0;
    err_state_fil 	= 0;
    formula_fil 	= 0;

    ListFilterLog_Num.		setViewCallback(CallbackListItemSelected);
    ListFilterLog_TypeChan.	setViewCallback(CallbackListItemSelected);
    ListFilterLog_StLoop.	setViewCallback(CallbackListItemSelected);
    ListFilterLog_Unit.		setViewCallback(CallbackListItemSelected);
    ListFilterLog_StCur.	setViewCallback(CallbackListItemSelected);
    ListFilterLog_Err.		setViewCallback(CallbackListItemSelected);
    ListFilterLog_Gas.		setViewCallback(CallbackListItemSelected);
	// lists' identify
	ListFilterLog_Num.		setContainerID(ConfigListFilterLog::ListID::list_channel);
	ListFilterLog_TypeChan.	setContainerID(ConfigListFilterLog::ListID::list_type_channel);
	ListFilterLog_StLoop.	setContainerID(ConfigListFilterLog::ListID::list_st_loop);
	ListFilterLog_Unit.		setContainerID(ConfigListFilterLog::ListID::list_units);
	ListFilterLog_StCur.	setContainerID(ConfigListFilterLog::ListID::list_st_cur);
	ListFilterLog_Err.		setContainerID(ConfigListFilterLog::ListID::list_err);
	ListFilterLog_Gas.		setContainerID(ConfigListFilterLog::ListID::list_formula);

	ListFilterLog_Num.		setHighlighted(32);
	ListFilterLog_TypeChan.	setHighlighted(2);
	ListFilterLog_StLoop.	setHighlighted(0);
	ListFilterLog_Unit.		setHighlighted(0);
	ListFilterLog_StCur.	setHighlighted(0);
	ListFilterLog_Err.		setHighlighted(0);
	ListFilterLog_Gas.		setHighlighted(0);

	invalidate();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

//=================================================================================================
// Переключение страниц
void Screen1View::functionReadLog()
{
	current_button_table = 1;
	current_page_table = 1;
	first_page_table = 1;
	position = 0;
	time_start_back = time_start_fil;
#ifdef TEST_COUNT_LOG
	// Для теста
	search_count_log = 50;
#else
	search_count_log = recording_of_logs_found_by_the_filter_to_file(50, type_log_fil, &time_start_back, time_stop_fil,
			&position, channel_num_fil, loop_state_fil, thld_state_fil, err_state_fil, ch_type_fil,  units_fil,  formula_fil);
#endif
	if(search_count_log){
		listLayoutPageButton.setVisible(true);
		listLayoutLogTable.setVisible(true);

		flexButtonPageBack.setVisible(false);
		if(search_count_log <= 50){
			flexButtonPageForward.setVisible(false);
		}
		else{
			flexButtonPageForward.setVisible(true);
		}

		if(search_count_log <= 40){
			flexButtonPage_5.setVisible(false);
		}
		else{
			flexButtonPage_5.setVisible(true);
		}

		if(search_count_log <= 30){
			flexButtonPage_4.setVisible(false);
		}
		else{
			flexButtonPage_4.setVisible(true);
		}

		if(search_count_log <= 20){
			flexButtonPage_3.setVisible(false);
		}
		else{
			flexButtonPage_3.setVisible(true);
		}

		if(search_count_log <= 10){
			flexButtonPage_2.setVisible(false);
		}
		else{
			flexButtonPage_2.setVisible(true);
		}
		PageRefresh();
	}
	else{
		listLayoutPageButton.setVisible(false);
		listLayoutLogTable.setVisible(false);
		invalidate();
	}


}

void Screen1View::functionPageBack()
{
	if(current_page_table > 1){
		current_page_table--;
	}
	if(current_button_table > 1){
		current_button_table--;
	}
	if(first_page_table > current_page_table){
		first_page_table = current_page_table;
	}
	//
	PageRefresh();
}

void Screen1View::functionPageForward()
{
	current_page_table++;
	if(current_button_table < 5){
		current_button_table++;
	}
	if((current_page_table - first_page_table) >= 5){
		first_page_table += 1;
	}
	//
	PageRefresh();
}

void Screen1View::functionPage_1()
{
	current_button_table = 1;
	current_page_table = touchgfx::Unicode::atoi(flexButtonPage_1Buffer);
	//
	PageRefresh();
}

void Screen1View::functionPage_2()
{
	current_button_table = 2;
	current_page_table = touchgfx::Unicode::atoi(flexButtonPage_2Buffer);
	//
	PageRefresh();
}

void Screen1View::functionPage_3()
{
	current_button_table = 3;
	current_page_table = touchgfx::Unicode::atoi(flexButtonPage_3Buffer);
	//
	PageRefresh();
}

void Screen1View::functionPage_4()
{
	current_button_table = 4;
	current_page_table = touchgfx::Unicode::atoi(flexButtonPage_4Buffer);
	//
	PageRefresh();
}

void Screen1View::functionPage_5()
{
	current_button_table = 5;
	current_page_table = touchgfx::Unicode::atoi(flexButtonPage_5Buffer);
	//
	PageRefresh();
}

void Screen1View::PageRefresh()
{
	touchgfx::Unicode::itoa((first_page_table), 		flexButtonPage_1Buffer, FLEXBUTTONPAGE_1_SIZE, 10);
	touchgfx::Unicode::itoa((first_page_table + 1), 	flexButtonPage_2Buffer, FLEXBUTTONPAGE_2_SIZE, 10);
	touchgfx::Unicode::itoa((first_page_table + 2), 	flexButtonPage_3Buffer, FLEXBUTTONPAGE_3_SIZE, 10);
	touchgfx::Unicode::itoa((first_page_table + 3), 	flexButtonPage_4Buffer, FLEXBUTTONPAGE_4_SIZE, 10);
	touchgfx::Unicode::itoa((first_page_table + 4), 	flexButtonPage_5Buffer, FLEXBUTTONPAGE_5_SIZE, 10);

	if(current_page_table == 1){
		flexButtonPageBack.setVisible(false);
	}
	else{
		flexButtonPageBack.setVisible(true);
	}

	// Докачивание архива если количество запрашиваемых логов больше, чем считано
	if((current_page_table*10) > search_count_log){
#ifdef TEST_COUNT_LOG
		//Для теста
		search_count_log += 10;
#else
		search_count_log += recording_of_logs_found_by_the_filter_to_file(10, type_log_fil, &time_start_back, time_stop_fil,
				&position, channel_num_fil, loop_state_fil, thld_state_fil, err_state_fil, ch_type_fil,  units_fil,  formula_fil);
#endif
		if((current_page_table*10) != search_count_log){
			flexButtonPageForward.setVisible(false);
		}
		else{
			flexButtonPageForward.setVisible(true);
		}

	}
	else{
		flexButtonPageForward.setVisible(true);
	}


	// Смена цвета кнопок обозначения страницы текущей и др
	flexButtonPage_1.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204),
				touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
	flexButtonPage_2.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204),
				touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
	flexButtonPage_3.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204),
				touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
	flexButtonPage_4.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204),
				touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
	flexButtonPage_5.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204),
				touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));


	switch(current_button_table){
	case 1:
		flexButtonPage_1.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(153, 0, 0), touchgfx::Color::getColorFromRGB(204, 0, 0),
				touchgfx::Color::getColorFromRGB(102, 0, 0), touchgfx::Color::getColorFromRGB(153, 53, 53));
	break;
	case 2:
		flexButtonPage_2.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(153, 0, 0), touchgfx::Color::getColorFromRGB(204, 0, 0),
				touchgfx::Color::getColorFromRGB(102, 0, 0), touchgfx::Color::getColorFromRGB(153, 53, 53));
	break;
	case 3:
		flexButtonPage_3.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(153, 0, 0), touchgfx::Color::getColorFromRGB(204, 0, 0),
				touchgfx::Color::getColorFromRGB(102, 0, 0), touchgfx::Color::getColorFromRGB(153, 53, 53));
	break;
	case 4:
		flexButtonPage_4.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(153, 0, 0), touchgfx::Color::getColorFromRGB(204, 0, 0),
				touchgfx::Color::getColorFromRGB(102, 0, 0), touchgfx::Color::getColorFromRGB(153, 53, 53));
	break;
	case 5:
		flexButtonPage_5.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(153, 0, 0), touchgfx::Color::getColorFromRGB(204, 0, 0),
				touchgfx::Color::getColorFromRGB(102, 0, 0), touchgfx::Color::getColorFromRGB(153, 53, 53));
	break;
	default:
		break;
	}

	// Обновление контейнеров содержащие логи
	for(uint8_t i = 0; i < 10; i++){
		if(parce_found_logs(data_log, ((current_page_table - 1)*10) + i)){
			if(type_log_fil == TYPE_LOG_READINGS){
				mas_ContainerTableLog[i]->UpdateLog(Event_log_readings_ptr);
			}
			else if(type_log_fil == TYPE_LOG_PARAM_UPDATE){
				mas_ContainerTableLog_Type2[i]->UpdateLog(Event_log_param_update_ptr);
			}
		}
		else{
			if(type_log_fil == TYPE_LOG_READINGS){
				mas_ContainerTableLog[i]->setVisible(false);
			}
			else if(type_log_fil == TYPE_LOG_PARAM_UPDATE){
				mas_ContainerTableLog_Type2[i]->setVisible(false);
			}
		}
	}
	invalidate();
}
//=================================================================================================
//LOG TYPE 1
//=================================================================================================
// Фильтр по дате
void Screen1View::functionOkFilDataTime(void)
{
	static struct tm timeptrStart;
	static struct tm timeptrStop;
	timeptrStart.tm_year = dateSelectorContainerStart.getYear();
	timeptrStart.tm_mon = dateSelectorContainerStart.getMonth();
	timeptrStart.tm_mday = dateSelectorContainerStart.getDay();
	time_start_fil 	= (uint32_t)mktime(&timeptrStart);
	timeptrStop.tm_year = dateSelectorContainerStop.getYear();
	timeptrStop.tm_mon 	= dateSelectorContainerStop.getMonth();
	timeptrStop.tm_mday = dateSelectorContainerStop.getDay();
	time_stop_fil 	= (uint32_t)mktime(&timeptrStop);

	if(time_stop_fil < time_start_fil){
		timeptrStop = timeptrStart;
	}

	Unicode::snprintf(textAreaStartDateBuffer, TEXTAREASTARTDATE_SIZE, "%.2d-%.2d-%4d", timeptrStart.tm_mday, timeptrStart.tm_mon + 1, timeptrStart.tm_year + 1900);
	Unicode::snprintf(textAreaStopDateBuffer, TEXTAREASTOPDATE_SIZE, "%.2d-%.2d-%4d", timeptrStop.tm_mday, timeptrStop.tm_mon + 1, timeptrStop.tm_year + 1900);
	modalWindow1.setVisible(false);
	invalidate();
}

void Screen1View::functionFilterDate(void)
{
	static time_p tmp;
	static struct tm timeptr;
	tmp = time_stop_fil;
	timeptr = *gmtime(&tmp);
	dateSelectorContainerStop.setDate(timeptr.tm_year, timeptr.tm_mon, timeptr.tm_mday);

	tmp = time_start_fil;
	timeptr = *gmtime(&tmp);
	dateSelectorContainerStart.setDate(timeptr.tm_year, timeptr.tm_mon, timeptr.tm_mday);


	modalWindow1.setVisible(true);
	invalidate();
}

//=================================================================================================
void Screen1View::functionFilterNum(void)
{
	touchgfx::TwoWildcardTextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger > > *button = &flexButtonFilterNum;
	touchgfx::ListLayout *listButton = &listLayoutButtonFilter;
	touchgfx::ListLayout *listTable = &listLayoutLogTable;
	ConfigListFilterLog *list = &ListFilterLog_Num;
	if(list->isVisible() == false)
	{
		list->moveTo(listButton->getX() + button->getX(), listButton->getY() + listButton->getHeight());
		list->resizeXY(button->getWidth(), listTable->getHeight());
		list->setVisible(true);
	}
	else{
		list->moveTo(800, 0);
		list->setVisible(false);
	}
	list->invalidate();
	if(channel_num_fil){
		Unicode::snprintf(flexButtonFilterNumBuffer2, FLEXBUTTONFILTERNUMBUFFER2_SIZE, "+");
	}
	else{
		Unicode::snprintf(flexButtonFilterNumBuffer2, FLEXBUTTONFILTERNUMBUFFER2_SIZE, " ");
	}

}

void Screen1View::functionFilterNum_Type2(void)
{
	touchgfx::TwoWildcardTextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger > > *button = &flexButtonFilterNum_Type2;
	touchgfx::ListLayout *listButton = &listLayoutButtonFilter_Type2;
	touchgfx::ListLayout *listTable = &listLayoutLogTable_Type2;
	ConfigListFilterLog *list = &ListFilterLog_Num;
	if(list->isVisible() == false)
	{
		list->moveTo(listButton->getX() + button->getX(), listButton->getY() + listButton->getHeight());
		list->resizeXY(button->getWidth(), listTable->getHeight());
		list->setVisible(true);
	}
	else{
		list->moveTo(800, 0);
		list->setVisible(false);
	}
	list->invalidate();
	if(channel_num_fil){
		Unicode::snprintf(flexButtonFilterNum_Type2Buffer2, FLEXBUTTONFILTERNUM_TYPE2BUFFER2_SIZE, "+");
	}
	else{
		Unicode::snprintf(flexButtonFilterNum_Type2Buffer2, FLEXBUTTONFILTERNUM_TYPE2BUFFER2_SIZE, " ");
	}

}

void Screen1View::functionFilterTypeChannel(void)
{
	touchgfx::TwoWildcardTextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger > > *button = &flexButtonFilterTypeChannel;
	touchgfx::ListLayout *listButton = &listLayoutButtonFilter;
	touchgfx::ListLayout *listTable = &listLayoutLogTable;
	ConfigListFilterLog *list = &ListFilterLog_TypeChan;
	if(list->isVisible() == false)
	{
		list->moveTo(listButton->getX() + button->getX(), listButton->getY() + listButton->getHeight());
		list->resizeXY(button->getWidth(), listTable->getHeight());
		list->setVisible(true);
	}
	else{
		list->moveTo(800, 0);
		list->setVisible(false);
	}
	list->invalidate();
	if(ch_type_fil){
		Unicode::snprintf(flexButtonFilterTypeChannelBuffer2, FLEXBUTTONFILTERTYPECHANNELBUFFER2_SIZE, "+");
	}
	else{
		Unicode::snprintf(flexButtonFilterTypeChannelBuffer2, FLEXBUTTONFILTERTYPECHANNELBUFFER2_SIZE, " ");
	}
}

void Screen1View::functionFilterStLoop(void)
{
	touchgfx::TwoWildcardTextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger > > *button = &flexButtonFilterStLoop;
	touchgfx::ListLayout *listButton = &listLayoutButtonFilter;
	touchgfx::ListLayout *listTable = &listLayoutLogTable;
	ConfigListFilterLog *list = &ListFilterLog_StLoop;
	if(list->isVisible() == false)
	{
		list->moveTo(listButton->getX() + button->getX(), listButton->getY() + listButton->getHeight());
		list->resizeXY(button->getWidth(), listTable->getHeight());
		list->setVisible(true);
	}
	else{
		list->moveTo(800, 0);
		list->setVisible(false);
	}
	list->invalidate();
	if(loop_state_fil){
		Unicode::snprintf(flexButtonFilterStLoopBuffer2, FLEXBUTTONFILTERSTLOOPBUFFER2_SIZE, "+");
	}
	else{
		Unicode::snprintf(flexButtonFilterStLoopBuffer2, FLEXBUTTONFILTERSTLOOPBUFFER2_SIZE, " ");
	}
}

void Screen1View::functionFilterUnit(void)
{
	touchgfx::TwoWildcardTextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger > > *button = &flexButtonFilterUnit;
	touchgfx::ListLayout *listButton = &listLayoutButtonFilter;
	touchgfx::ListLayout *listTable = &listLayoutLogTable;
	ConfigListFilterLog *list = &ListFilterLog_Unit;
	if(list->isVisible() == false)
	{
		list->moveTo(listButton->getX() + button->getX(), listButton->getY() + listButton->getHeight());
		list->resizeXY(button->getWidth(), listTable->getHeight());
		list->setVisible(true);
	}
	else{
		list->moveTo(800, 0);
		list->setVisible(false);
	}
	list->invalidate();
	if(units_fil){
		Unicode::snprintf(flexButtonFilterUnitBuffer2, FLEXBUTTONFILTERUNITBUFFER2_SIZE, "+");
	}
	else{
		Unicode::snprintf(flexButtonFilterUnitBuffer2, FLEXBUTTONFILTERUNITBUFFER2_SIZE, " ");
	}
}

void Screen1View::functionFilterUnit_Type2(void)
{
	touchgfx::TwoWildcardTextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger > > *button = &flexButtonFilterUnit_Type2;
	touchgfx::ListLayout *listButton = &listLayoutButtonFilter_Type2;
	touchgfx::ListLayout *listTable = &listLayoutLogTable_Type2;
	ConfigListFilterLog *list = &ListFilterLog_Unit;
	if(list->isVisible() == false)
	{
		list->moveTo(listButton->getX() + button->getX(), listButton->getY() + listButton->getHeight());
		list->resizeXY(button->getWidth(), listTable->getHeight());
		list->setVisible(true);
	}
	else{
		list->moveTo(800, 0);
		list->setVisible(false);
	}
	list->invalidate();
	if(units_fil){
		Unicode::snprintf(flexButtonFilterUnit_Type2Buffer2, FLEXBUTTONFILTERUNIT_TYPE2BUFFER2_SIZE, "+");
	}
	else{
		Unicode::snprintf(flexButtonFilterUnit_Type2Buffer2, FLEXBUTTONFILTERUNIT_TYPE2BUFFER2_SIZE, " ");
	}
}

void Screen1View::functionFilterThreshold(void)
{
	touchgfx::TwoWildcardTextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger > > *button = &flexButtonFilterThreshold;
	touchgfx::ListLayout *listButton = &listLayoutButtonFilter;
	touchgfx::ListLayout *listTable = &listLayoutLogTable;
	ConfigListFilterLog *list = &ListFilterLog_StCur;
	if(list->isVisible() == false)
	{
		list->moveTo(listButton->getX() + button->getX(), listButton->getY() + listButton->getHeight());
		list->resizeXY(button->getWidth(), listTable->getHeight());
		list->setVisible(true);
	}
	else{
		list->moveTo(800, 0);
		list->setVisible(false);
	}
	list->invalidate();
	if(thld_state_fil){
		Unicode::snprintf(flexButtonFilterThresholdBuffer2, FLEXBUTTONFILTERTHRESHOLDBUFFER2_SIZE, "+");
	}
	else{
		Unicode::snprintf(flexButtonFilterThresholdBuffer2, FLEXBUTTONFILTERTHRESHOLDBUFFER2_SIZE, " ");
	}
}

void Screen1View::functionFilterErr(void)
{
	touchgfx::TwoWildcardTextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger > > *button = &flexButtonFilterErr;
	touchgfx::ListLayout *listButton = &listLayoutButtonFilter;
	touchgfx::ListLayout *listTable = &listLayoutLogTable;
	ConfigListFilterLog *list = &ListFilterLog_Err;
	if(list->isVisible() == false)
	{
		list->moveTo(listButton->getX() + button->getX(), listButton->getY() + listButton->getHeight());
		list->resizeXY(button->getWidth(), listTable->getHeight());
		list->setVisible(true);
	}
	else{
		list->moveTo(800, 0);
		list->setVisible(false);
	}
	list->invalidate();
	if(err_state_fil){
		Unicode::snprintf(flexButtonFilterErrBuffer2, FLEXBUTTONFILTERERRBUFFER2_SIZE, "+");
	}
	else{
		Unicode::snprintf(flexButtonFilterErrBuffer2, FLEXBUTTONFILTERERRBUFFER2_SIZE, " ");
	}
}

void Screen1View::functionFilterGas(void)
{
	touchgfx::TwoWildcardTextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger > > *button = &flexButtonFilterGas;
	touchgfx::ListLayout *listButton = &listLayoutButtonFilter;
	touchgfx::ListLayout *listTable = &listLayoutLogTable;
	ConfigListFilterLog *list = &ListFilterLog_Gas;
	if(list->isVisible() == false)
	{
		list->moveTo(listButton->getX() + button->getX(), listButton->getY() + listButton->getHeight());
		list->resizeXY(button->getWidth(), listTable->getHeight());
		list->setVisible(true);
	}
	else{
		list->moveTo(800, 0);
		list->setVisible(false);
	}
	list->invalidate();
	if(formula_fil){
		Unicode::snprintf(flexButtonFilterGasBuffer2, FLEXBUTTONFILTERGASBUFFER2_SIZE, "+");
	}
	else{
		Unicode::snprintf(flexButtonFilterGasBuffer2, FLEXBUTTONFILTERGASBUFFER2_SIZE, " ");
	}
}

void Screen1View::functionFilterGas_Type2(void)
{
	touchgfx::TwoWildcardTextButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger > > *button = &flexButtonFilterGas_Type2;
	touchgfx::ListLayout *listButton = &listLayoutButtonFilter_Type2;
	touchgfx::ListLayout *listTable = &listLayoutLogTable_Type2;
	ConfigListFilterLog *list = &ListFilterLog_Gas;
	if(list->isVisible() == false)
	{
		list->moveTo(listButton->getX() + button->getX(), listButton->getY() + listButton->getHeight());
		list->resizeXY(button->getWidth(), listTable->getHeight());
		list->setVisible(true);
	}
	else{
		list->moveTo(800, 0);
		list->setVisible(false);
	}
	list->invalidate();
	if(formula_fil){
		Unicode::snprintf(flexButtonFilterGas_Type2Buffer2, FLEXBUTTONFILTERGAS_TYPE2BUFFER2_SIZE, "+");
	}
	else{
		Unicode::snprintf(flexButtonFilterGas_Type2Buffer2, FLEXBUTTONFILTERGAS_TYPE2BUFFER2_SIZE, " ");
	}
}

//=================================================================================================
//Фильтр по типу логов
void Screen1View::functionTurnLog1(void)
{
	type_log_fil = TYPE_LOG_READINGS;
	flexButtonTurnLog1			.setVisible(false);
	flexButtonTurnLog2			.setVisible(true);
	listLayoutButtonFilter		.moveTo(32, 141);
	listLayoutLogTable			.moveTo(32, 200);
	listLayoutButtonFilter		.setVisible(true);
	listLayoutLogTable			.setVisible(true);

	listLayoutButtonFilter_Type2.moveTo(32, 480);
	listLayoutLogTable_Type2	.moveTo(32, 540);
	listLayoutButtonFilter_Type2.setVisible(false);
	listLayoutLogTable_Type2	.setVisible(false);

	ListFilterLog_Num			.moveTo(800, 0);
	ListFilterLog_TypeChan		.moveTo(800, 0);
	ListFilterLog_StLoop		.moveTo(800, 0);
	ListFilterLog_Unit			.moveTo(800, 0);
	ListFilterLog_StCur			.moveTo(800, 0);
	ListFilterLog_Err			.moveTo(800, 0);
	ListFilterLog_Gas			.moveTo(800, 0);

	ListFilterLog_Num			.setVisible(false);
	ListFilterLog_TypeChan		.setVisible(false);
	ListFilterLog_StLoop		.setVisible(false);
	ListFilterLog_Unit			.setVisible(false);
	ListFilterLog_StCur			.setVisible(false);
	ListFilterLog_Err			.setVisible(false);
	ListFilterLog_Gas			.setVisible(false);

	for(uint8_t i = 0; i < 10; i++){
		mas_ContainerTableLog[i]->setVisible(false);
	}

	invalidate();

//	functionReadLog();
}

void Screen1View::functionTurnLog2(void)
{
	type_log_fil = TYPE_LOG_PARAM_UPDATE;
	flexButtonTurnLog1			.setVisible(true);
	flexButtonTurnLog2			.setVisible(false);
	listLayoutButtonFilter_Type2.moveTo(32, 141);
	listLayoutLogTable_Type2	.moveTo(32, 200);
	listLayoutButtonFilter_Type2.setVisible(true);
	listLayoutLogTable_Type2	.setVisible(true);

	listLayoutButtonFilter		.moveTo(32, 480);
	listLayoutLogTable			.moveTo(32, 540);
	listLayoutButtonFilter		.setVisible(false);
	listLayoutLogTable			.setVisible(false);

	ListFilterLog_Num			.moveTo(800, 0);
	ListFilterLog_TypeChan		.moveTo(800, 0);
	ListFilterLog_StLoop		.moveTo(800, 0);
	ListFilterLog_Unit			.moveTo(800, 0);
	ListFilterLog_StCur			.moveTo(800, 0);
	ListFilterLog_Err			.moveTo(800, 0);
	ListFilterLog_Gas			.moveTo(800, 0);

	ListFilterLog_Num			.setVisible(false);
	ListFilterLog_TypeChan		.setVisible(false);
	ListFilterLog_StLoop		.setVisible(false);
	ListFilterLog_Unit			.setVisible(false);
	ListFilterLog_StCur			.setVisible(false);
	ListFilterLog_Err			.setVisible(false);
	ListFilterLog_Gas			.setVisible(false);

	for(uint8_t i = 0; i < 10; i++){
		mas_ContainerTableLog_Type2[i]->setVisible(false);
	}

	invalidate();

//	functionReadLog();
}
//=================================================================================================
void Screen1View::handleListItemSelected(uint8_t list_item, ConfigListFilterLog* list)
{
	if(list == &ListFilterLog_Num){
		if(list_item <= 31){
			if(TESTBIT(channel_num_fil, list_item)){
				CLRBIT(channel_num_fil, list_item);
			}
			else{
				SETBIT(channel_num_fil, list_item);
			}
		}
		else{
			channel_num_fil = 0;
		}
	}
	else if(list == &ListFilterLog_TypeChan){
		if(list_item){
			if(TESTBIT(ch_type_fil, list_item)){
				CLRBIT(ch_type_fil, list_item);
			}
			else{
				SETBIT(ch_type_fil, list_item);
			}
		}
		else{
			ch_type_fil = list_item;
		}
	}
	else if(list == &ListFilterLog_StLoop){
		if(list_item){
			if(TESTBIT(loop_state_fil, list_item)){
				CLRBIT(loop_state_fil, list_item);
			}
			else{
				SETBIT(loop_state_fil, list_item);
			}
		}
		else{
			loop_state_fil = list_item;
		}
	}
	else if(list == &ListFilterLog_Unit){
		if(list_item){
			if(TESTBIT(units_fil, list_item)){
				CLRBIT(units_fil, list_item);
			}
			else{
				SETBIT(units_fil, list_item);
			}
		}
		else{
			units_fil = list_item;
		}
	}
	else if(list == &ListFilterLog_StCur){
		if(list_item){
			if(TESTBIT(thld_state_fil, list_item)){
				CLRBIT(thld_state_fil, list_item);
			}
			else{
				SETBIT(thld_state_fil, list_item);
			}
		}
		else{
			thld_state_fil = list_item;
		}
	}
	else if(list == &ListFilterLog_Err){
		if(list_item){
			if(TESTBIT(err_state_fil, list_item)){
				CLRBIT(err_state_fil, list_item);
			}
			else{
				SETBIT(err_state_fil, list_item);
			}
		}
		else{
			err_state_fil = list_item;
		}
	}
	else if(list == &ListFilterLog_Gas){
		if(list_item){
			if(TESTBIT(formula_fil, list_item)){
				CLRBIT(formula_fil, list_item);
			}
			else{
				SETBIT(formula_fil, list_item);
			}
		}
		else{
			formula_fil = list_item;
		}
	}
//	list->moveTo(800, 0);
//	list->invalidate();
}
