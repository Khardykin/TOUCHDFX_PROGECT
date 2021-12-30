/*
 * parce_archiv.h
 *
 *  Created on: Dec 10, 2021
 *      Author: Dmitriy
 */

#ifndef INC_PARCE_ARCHIV_H_
#define INC_PARCE_ARCHIV_H_

typedef enum{
    TYPE_LOG_READINGS = 0,
    TYPE_LOG_PARAM_UPDATE = 1,
}TYPE_LOG;

typedef enum{
	TYPE_STATE_FILE_START = 0,
	TYPE_STATE_FILE_STOP = 1,
}TYPE_STATE_FILE;
//========================================================================================
typedef struct//
{
	uint32_t            working_hours_log;              // Одна единица равна us, мото часы
	uint32_t            CurrentAddrFile;                // Текущий адресс архива
	uint8_t 			channel_num;
	float 				concentration;
	uint8_t 			units;
	uint8_t 			ch_type;
	uint8_t 			loop_state;
	uint8_t 			thld_state;
	uint8_t 			error_state;
	uint8_t 			ch_on;
	uint8_t 			formula;
}TileInfoTypeDef;

typedef struct//
{
	uint32_t            working_hours_log;              // Одна единица равна s, мото часы
	uint8_t 			type_log;
	uint32_t            CurrentAddrFile;                // Текущий адресс архива
	uint8_t 			channel_num;
	float 				concentration;
	float 				threshold_1;
	float 				threshold_2;
	float 				threshold_3;
	float 				full_scale;
	float 				hysteresis;
	uint8_t 			units;
	uint8_t 			ch_type;
	uint8_t 			loop_state;
	uint8_t 			thld_state;
	uint8_t 			error_state;
	uint8_t 			ch_on;
	uint8_t 			formula;
}ContainerInfoTypeDef;
//========================================================================================

//========================================================================================
extern void 		write_archiv(uint8_t *data, TYPE_LOG type_log);
extern uint32_t 	parce_archive(uint8_t *data, uint32_t timestart, uint32_t timestop, uint16_t *position, TYPE_LOG type_log);
//
extern void 		writing_found_logs(uint8_t *data);
extern uint8_t 		parce_found_logs(uint8_t * data, uint16_t number_log);
//
extern void 		init_write_state_file_archiv(TYPE_STATE_FILE type_state_file, uint32_t data_time);
extern uint32_t 	open_read_state_file_archiv(TYPE_STATE_FILE type_state_file);
extern void 		read_start_stop_state_archiv(uint32_t *time_start, uint32_t *time_stop);
//
extern void 		clear_file_with_found_log(void);
extern uint16_t 	recording_of_logs_found_by_the_filter_to_file(uint16_t search_count_log, TYPE_LOG type_log, uint32_t * time_start, uint32_t time_stop, uint16_t *position,
		uint32_t channel_num_fil, uint8_t loop_state_fil,uint8_t thld_state_fil,uint16_t err_state_fil,
		uint8_t ch_type_fil, uint8_t units_fil, uint8_t formula_fil);

//========================================================================================
#endif /* INC_PARCE_ARCHIV_H_ */
