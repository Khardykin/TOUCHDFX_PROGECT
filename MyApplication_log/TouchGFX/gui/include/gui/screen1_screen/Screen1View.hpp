#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <gui/settings_screen/DateSelectorContainer.hpp>

extern "C"{
#include "parce_archiv.h"
}

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void PageRefresh(void);

    void functionReadLog(void);
	void functionPageBack(void);
	void functionPageForward(void);
	void functionPage_1(void);
	void functionPage_2(void);
	void functionPage_3(void);
	void functionPage_4(void);
	void functionPage_5(void);


	void functionOkFilDataTime(void);

	void functionFilterData(void);


protected:

	DateSelectorContainer dateSelectorContainerStart;
	DateSelectorContainer dateSelectorContainerStop;


	uint8_t data_log[100];
	uint16_t current_button_table = 1;
	uint16_t first_page_table = 1;
	uint16_t current_page_table = 1;

	uint16_t search_count_log;
	TYPE_LOG type_log_fil;
	uint32_t time_start_back;
	uint32_t time_start_fil;
	uint32_t time_stop_fil;
	uint16_t position;

	uint8_t channel_num_fil;
	uint8_t loop_state_fil;
	uint8_t thld_state_fil;
	uint16_t err_state_fil;
	uint8_t ch_type_fil;
	uint8_t units_fil;
	uint8_t formula_fil;

	TileInfoTypeDef 		*Event_log_readings_ptr 	= (TileInfoTypeDef*)data_log;
	ContainerInfoTypeDef 	*Event_log_param_update_ptr = (ContainerInfoTypeDef*)data_log;



	CustomContainerTableLog *mas_ContainerTableLog[10] = {
			&customContainerTableLog_0,
			&customContainerTableLog_1,
			&customContainerTableLog_2,
			&customContainerTableLog_3,
			&customContainerTableLog_4,
			&customContainerTableLog_5,
			&customContainerTableLog_6,
			&customContainerTableLog_7,
			&customContainerTableLog_8,
			&customContainerTableLog_9,
	};


};

#endif // SCREEN1VIEW_HPP