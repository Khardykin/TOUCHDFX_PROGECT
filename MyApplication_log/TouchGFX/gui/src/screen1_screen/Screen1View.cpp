#include <gui/screen1_screen/Screen1View.hpp>
#include "touchgfx/Utils.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "time.h"

static time_p tmp;
static struct tm timeptr;

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    touchgfx_printf("setupScreen");

    read_start_stop_state_archiv(&time_start_fil, &time_stop_fil);

    time_stop_fil = 1735039935;
    time_start_fil = time_stop_fil;
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


}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::functionReadLog()
{
	current_button_table = 1;
	current_page_table = 1;
	first_page_table = 1;
	position = 0;
	time_start_back = time_start_fil;

	search_count_log = 50;
//	search_count_log = recording_of_logs_found_by_the_filter_to_file(50, type_log_fil, &time_start_back, time_stop_fil,
//			&position, channel_num_fil, loop_state_fil, thld_state_fil, err_state_fil, ch_type_fil,  units_fil,  formula_fil);
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

	if((current_page_table*10) > search_count_log){
		search_count_log += 10;
		//	search_count_log += recording_of_logs_found_by_the_filter_to_file(10, type_log_fil, &time_start_back, time_stop_fil,
		//			&position, channel_num_fil, loop_state_fil, thld_state_fil, err_state_fil, ch_type_fil,  units_fil,  formula_fil);
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

	for(uint8_t i = 0; i < 10; i++){
		if(parce_found_logs(data_log, ((current_page_table - 1)*10) + i)){
			if(type_log_fil == TYPE_LOG_READINGS){
				mas_ContainerTableLog[i]->UpdateLog_1(Event_log_readings_ptr);
			}
			else if(type_log_fil == TYPE_LOG_PARAM_UPDATE){
				//customContainerTableLog_0.UpdateLog_2(Event_log_param_update_ptr);
			}
		}
		else{
			if(type_log_fil == TYPE_LOG_READINGS){
				mas_ContainerTableLog[i]->setVisible(false);
			}
		}
	}
	invalidate();
}

void Screen1View::functionOkFilDataTime(void)
{
	static struct tm timeptr1;
	static struct tm timeptr2;
	timeptr1.tm_year = dateSelectorContainerStart.getYear();
	timeptr1.tm_mon 	= dateSelectorContainerStart.getMonth();
	timeptr1.tm_mday = dateSelectorContainerStart.getDay();
	time_start_fil 	= (uint32_t)mktime(&timeptr1);
	timeptr2.tm_year = dateSelectorContainerStop.getYear();
	timeptr2.tm_mon 	= dateSelectorContainerStop.getMonth();
	timeptr2.tm_mday = dateSelectorContainerStop.getDay();
	time_stop_fil 	= (uint32_t)mktime(&timeptr2);

	modalWindow1.setVisible(false);
	modalWindow1.invalidate();
}

void Screen1View::functionFilterData(void)
{
	tmp = time_stop_fil;
	timeptr = *gmtime(&tmp);
	dateSelectorContainerStop.setDate(timeptr.tm_year, timeptr.tm_mon, timeptr.tm_mday);

	tmp = time_start_fil;
	timeptr = *gmtime(&tmp);
	dateSelectorContainerStart.setDate(timeptr.tm_year, timeptr.tm_mon, timeptr.tm_mday);


	modalWindow1.setVisible(true);
	modalWindow1.invalidate();
}
