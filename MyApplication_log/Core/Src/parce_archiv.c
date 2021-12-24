/*
 * parce_archiv.c
 *
 *  Created on: Dec 10, 2021
 *      Author: Dmitriy
 */
#include "main.h"
#include "parce_archiv.h"
#include "fatfs.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h> //for va_list var arg functions
#include <time.h>

//#define DEBUG_PRINTF_SD_CARD
//========================================================================================
static void 		write_archiv_file(uint8_t *data, TYPE_LOG type_log);
static uint16_t 	read_archiv_file(uint8_t *data, uint32_t hours_log, uint16_t position, TYPE_LOG type_log);
//
static void 		writing_found_logs_to_file(uint8_t * data);
static uint8_t 		reading_found_logs_from_file(uint8_t * data, uint16_t number_log);
//
static void 		rewrite_state_file_archiv(void);
static void 		write_state_file_archiv(TYPE_STATE_FILE type_state_file, uint32_t data_time);
static uint32_t 	read_state_file_archiv(TYPE_STATE_FILE type_state_file);
//
static void 		init_log_search_by_filter_time(uint32_t time_start, uint32_t time_stop, uint16_t position);
static void 		init_file_found_logs(void);

static uint8_t 		log_search_by_filter(uint8_t * data, TYPE_LOG type_log,	uint8_t channel_num_fil,
		uint8_t loop_state_fil, uint8_t thld_state_fil, uint16_t err_state_fil,
		uint8_t ch_type_fil, uint8_t units_fil, uint8_t formula_fil);
//========================================================================================
static char 		data_hex[100];				// Вспомогательный массив для записи/чтения в/из файла
static uint16_t 	position_file = 0;			// Позиция в текущем файле при поиске логов
static uint32_t 	time_start_log = 0;			// Стартовое время при поиске логов
static uint32_t 	time_stop_log = 0;			// Конец времени при поиске логов
static TYPE_LOG 	type_founds_logs_to_file;	// Тип лога при поиске логов

//========================================================================================
// Открыть файловую систему
// Записать лог в файл
void write_archiv(uint8_t *data, TYPE_LOG type_log)
{
	uint16_t 	len = 0;
	FATFS 		FatFs; 		//Fatfs handle
	FRESULT 	fres; 		//Result after operations
	DWORD 		free_clusters, free_sectors, total_sectors;
	FATFS* 		getFreeFs;

	if(type_log == TYPE_LOG_READINGS){
		len = sizeof(TileInfoTypeDef);
	}
	else if(type_log == TYPE_LOG_PARAM_UPDATE){
		len = sizeof(ContainerInfoTypeDef);
	}
	//------------------------------------------------------------------------------
	//Open the file system
	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("f_mount write_archiv error (%i)\r\n", fres);
#endif
		goto EXIT;
	}
	//------------------------------------------------------------------------------
	//Let's get some statistics from the SD card
	FILE_FREE_SIZE:
	fres = f_getfree("", &free_clusters, &getFreeFs);
	if (fres != FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("f_getfree error (%i)\r\n", fres);
#endif
		while(1);
	}

	total_sectors = (FatFs.n_fatent - 2) * FatFs.csize;
	free_sectors = free_clusters * FatFs.csize;
#ifdef DEBUG_PRINTF_SD_CARD
	myprintf("SD card stats:\r\n%10lu KiB total drive space.\r\n%10lu KiB available.\r\n", total_sectors / 2, free_sectors / 2);
#endif
	if((free_sectors / 2) < len)
	{
		// Память заполнена, стереть самый старый файл
		rewrite_state_file_archiv();
		goto FILE_FREE_SIZE;
		//goto EXIT;
	}
	//------------------------------------------------------------------------------
	// Запись строчки(лога) в файл
	write_archiv_file(data, type_log);
	//------------------------------------------------------------------------------
	// Сохраняем последнюю дату в файл состояния архива
	write_state_file_archiv(TYPE_STATE_FILE_STOP, ((TileInfoTypeDef*)data)->working_hours_log);
	//------------------------------------------------------------------------------
	//
	EXIT:
	f_mount(NULL, "", 0);
}

//========================================================================================
// Открыть файловую систему
// Разбор архива по дате\времени
// Если position < sizeof() 0, то файл пустой или законченный, position = 0 выход за временные ограничители
// Возвращает время считаного лога
uint32_t parce_archive(uint8_t *data, uint32_t timestart, uint32_t timestop, uint16_t *position, TYPE_LOG type_log)
{
	FATFS 		FatFs; 		//Fatfs handle
	FRESULT 	fres; 		//Result after operations
	uint32_t 	time_name_file = timestart;
	TileInfoTypeDef 		*Event_log_readings_ptr 	= (TileInfoTypeDef*)data;
	ContainerInfoTypeDef 	*Event_log_param_update_ptr = (ContainerInfoTypeDef*)data;

	//------------------------------------------------------------------------------
	//Open the file system
	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("f_mount parce_archive error (%i)\r\n", fres);
#endif
		goto EXIT;
	}
	//------------------------------------------------------------------------------
	// Чтение строчки(лога) из файла
	//
	time_t tmp = time_name_file;
	struct tm 	tm_ptr_name_file = *gmtime(&tmp);
	tmp = timestop;
	struct tm 	tm_ptr_timestop = *gmtime(&tmp);
	do{
		START_READ_ARCHIV:
		*position = read_archiv_file(data, time_name_file, *position, type_log);
		if((*position)){
			if(type_log == TYPE_LOG_READINGS){
				if((Event_log_readings_ptr->working_hours_log >= timestart) && (Event_log_readings_ptr->working_hours_log < timestop))
				{
					time_name_file = Event_log_readings_ptr->working_hours_log;
					goto EXIT;
				}
				else if((Event_log_readings_ptr->working_hours_log >= timestop))
				{
					time_name_file = timestop;
					*position = 0;
					goto EXIT;
				}
			}
			else if(type_log == TYPE_LOG_PARAM_UPDATE){
				if((Event_log_param_update_ptr->working_hours_log >= timestart) && (Event_log_param_update_ptr->working_hours_log < timestop))
				{
					time_name_file = Event_log_readings_ptr->working_hours_log;
					goto EXIT;
				}
				else if((Event_log_param_update_ptr->working_hours_log >= timestop))
				{
					time_name_file = timestop;
					*position = 0;
					goto EXIT;
				}
			}
		}
		else if(!(*position))
		{
			tm_ptr_name_file.tm_mon += 1;
			if(tm_ptr_name_file.tm_mon >= 12){
				tm_ptr_name_file.tm_mon = 0;
				tm_ptr_name_file.tm_year += 1;
			}
			if((tm_ptr_name_file.tm_year < tm_ptr_timestop.tm_year)||
					((tm_ptr_name_file.tm_year == tm_ptr_timestop.tm_year) && (tm_ptr_name_file.tm_mon <= tm_ptr_timestop.tm_mon))){
				time_name_file = (uint32_t)mktime(&tm_ptr_name_file);
				goto START_READ_ARCHIV;
			}
			else{
				time_name_file = timestop;
			}
		}
	}while(*position);
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	//
	EXIT:
	f_mount(NULL, "", 0);
	return time_name_file;
}

//========================================================================================
// Открыть файловую систему
// Записать лог в файл
void writing_found_logs(uint8_t *data)
{
	uint16_t 	len = 0;
	FATFS 		FatFs; 		//Fatfs handle
	FRESULT 	fres; 		//Result after operations
	DWORD 		free_clusters, free_sectors, total_sectors;
	FATFS* 		getFreeFs;

	if(type_founds_logs_to_file == TYPE_LOG_READINGS){
		len = sizeof(TileInfoTypeDef);
	}
	else if(type_founds_logs_to_file == TYPE_LOG_PARAM_UPDATE){
		len = sizeof(ContainerInfoTypeDef);
	}
	//------------------------------------------------------------------------------
	//Open the file system
	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("f_mount write_archiv error (%i)\r\n", fres);
#endif
		goto EXIT;
	}
	//------------------------------------------------------------------------------
	//Let's get some statistics from the SD card
	FILE_FREE_SIZE:
	fres = f_getfree("", &free_clusters, &getFreeFs);
	if (fres != FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("f_getfree error (%i)\r\n", fres);
#endif
		while(1);
	}

	total_sectors = (FatFs.n_fatent - 2) * FatFs.csize;
	free_sectors = free_clusters * FatFs.csize;
#ifdef DEBUG_PRINTF_SD_CARD
	myprintf("SD card stats:\r\n%10lu KiB total drive space.\r\n%10lu KiB available.\r\n", total_sectors / 2, free_sectors / 2);
#endif
	if((free_sectors / 2) < len)
	{
		// Память заполнена, стереть самый старый файл
		rewrite_state_file_archiv();
		goto FILE_FREE_SIZE;
		//goto EXIT;
	}
	//------------------------------------------------------------------------------
	// Запись строчки(лога) в файл
	writing_found_logs_to_file(data);
	//------------------------------------------------------------------------------
	//
	EXIT:
	f_mount(NULL, "", 0);
}

//========================================================================================
// Открыть файловую систему
// Чтение найденного лога из заполенного файла, по его порядковому номеру
// Возвращает 1 если лог есть, 0 если нету
uint8_t parce_found_logs(uint8_t * data, uint16_t number_log)
{
	FATFS 		FatFs; 		//Fatfs handle
	FRESULT 	fres; 		//Result after operations
	uint8_t 	state_read = 0;

	//------------------------------------------------------------------------------
	//Open the file system
	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("f_mount parce_archive error (%i)\r\n", fres);
#endif
		goto EXIT;
	}
	//------------------------------------------------------------------------------
	// Чтение строчки(лога) из файла
	state_read = reading_found_logs_from_file(data, number_log);
	//------------------------------------------------------------------------------
	//
	EXIT:
	f_mount(NULL, "", 0);
	return state_read;
}

//========================================================================================
// Открыть файловую систему
// Запись начала или конца архива в файлы
void init_write_state_file_archiv(TYPE_STATE_FILE type_state_file, uint32_t data_time)
{
	FATFS 		FatFs; 		//Fatfs handle
	FRESULT 	fres; 		//Result after operations
	//------------------------------------------------------------------------------
	//Open the file system
	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("f_mount init_write_state_file_archiv error (%i)\r\n", fres);
#endif
		goto EXIT;
	}
	//------------------------------------------------------------------------------
	write_state_file_archiv(type_state_file, data_time);
	//------------------------------------------------------------------------------
	//
	EXIT:
	f_mount(NULL, "", 0);
}

//========================================================================================
// Открыть файловую систему
// Чтение времени файла конца или начала архива
uint32_t open_read_state_file_archiv(TYPE_STATE_FILE type_state_file)
{
	uint32_t 	data_time = 0;
	FATFS 		FatFs; 		//Fatfs handle
	FRESULT 	fres; 		//Result after operations
	//------------------------------------------------------------------------------
	//Open the file system
	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("f_mount open_read_state_file_archiv error (%i)\r\n", fres);
#endif
		goto EXIT;
	}
	//------------------------------------------------------------------------------
	data_time = read_state_file_archiv(type_state_file);
	//------------------------------------------------------------------------------
	//
	EXIT:
	f_mount(NULL, "", 0);
	return data_time;
}

//========================================================================================
// Чтение и начала и конца архива, содержащие время
void read_start_stop_state_archiv(uint32_t *time_start, uint32_t *time_stop)
{
	*time_start = open_read_state_file_archiv(TYPE_STATE_FILE_START);
	*time_stop = open_read_state_file_archiv(TYPE_STATE_FILE_STOP) + 1;
}

//========================================================================================
// Очистка(перезапись) файла содержащего найденные логи по фильтрам
void clear_file_with_found_log(void)
{
	init_file_found_logs();
}

//========================================================================================
// Чтение найденных по фильтру логов из файла
// Запись найденных по фильтру логов в файл
// Возвращает количество найденных логов
uint16_t recording_of_logs_found_by_the_filter_to_file(uint8_t * data, TYPE_LOG type_log, uint32_t time_start, uint32_t time_stop, uint16_t position,
		uint8_t channel_num_fil, uint8_t loop_state_fil,uint8_t thld_state_fil,uint16_t err_state_fil,
		uint8_t ch_type_fil, uint8_t units_fil, uint8_t formula_fil)
{
	uint16_t	count_log = 0;
	type_founds_logs_to_file = type_log;

	//------------------------------------------------------------------------------
	init_log_search_by_filter_time(time_start, time_stop, position);
	while(log_search_by_filter(data, type_log, channel_num_fil, loop_state_fil, thld_state_fil, err_state_fil, ch_type_fil, units_fil, formula_fil))
	{
		// Запись строчки(лога) в файл
		writing_found_logs(data);
		count_log++;
	}
	//------------------------------------------------------------------------------
	return count_log;
}

//========================================================================================
// Записать лог в файл
static void write_archiv_file(uint8_t *data, TYPE_LOG type_log)
{
	uint16_t 	len = 0;
	TCHAR 		time_str[30] = {0};
	TCHAR 		name_file[60] = {0};
	time_t 		tmp  = 0;
	UINT 		bytesWrote;
	FIL 		fil; 		//File handle
	FRESULT 	fres; 		//Result after operations

	if(type_log == TYPE_LOG_READINGS){
		TileInfoTypeDef *Event_log_readings_ptr = (TileInfoTypeDef*)data;
		tmp = Event_log_readings_ptr->working_hours_log;
		struct tm tm_ptr = *gmtime(&tmp);
		strftime (time_str, strlen("MM_YYYY")+1, "%m-%Y", &tm_ptr);
		snprintf(name_file, sizeof(name_file), "LOG_R_%s.txt", time_str);
		len = sizeof(TileInfoTypeDef);
	}
	else if(type_log == TYPE_LOG_PARAM_UPDATE){
		ContainerInfoTypeDef *Event_log_param_update_ptr = (ContainerInfoTypeDef*)data;
		tmp = Event_log_param_update_ptr->working_hours_log;
		struct tm tm_ptr = *gmtime(&tmp);
		strftime (time_str, strlen("MM-YYYY")+1, "%m-%Y", &tm_ptr);
		snprintf(name_file, sizeof(name_file), "LOG_P_U_%s.txt", time_str);
		len = sizeof(ContainerInfoTypeDef);
	}
	//------------------------------------------------------------------------------
	// Открываем или создаем новый файл
	fres = f_open(&fil, name_file, FA_WRITE | FA_OPEN_APPEND);
	if(fres == FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("I was able write_archiv_file to open %s for writing\r\n", name_file);
#endif
	} else {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("f_open write_archiv_file error (%i)\r\n", fres);
#endif
	}
	//------------------------------------------------------------------------------
	// Запись строчки
	for(uint16_t i=0; i < len; ++i){
		snprintf(&data_hex[i*2], 3, "%02X", data[i]);
	}
	snprintf(&data_hex[len*2], 3, "\r\n");
	fres = f_write(&fil, data_hex, (len+1)*2, &bytesWrote);
	if(fres == FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("Wrote %i bytes to %s, size file %i\r\n", bytesWrote, name_file, f_size(&fil));
#endif
	} else {
#ifdef DEBUG_PRINTF_SD_CARD
	  	myprintf("f_write error (%i)\r\n", fres);
#endif
	}
	f_close(&fil);
}

//========================================================================================
// Чтение лога из файла
static uint16_t read_archiv_file(uint8_t *data, uint32_t hours_log, uint16_t position, TYPE_LOG type_log)
{
	uint8_t		data_hex_dec;
	uint16_t 	len = 0;
	TCHAR 		time_str[30] = {0};
	TCHAR 		name_file[60] = {0};
	time_t		tmp = 0;
	UINT 		bytesWrote;
	FIL 		fil; 		//File handle
	FRESULT 	fres; 		//Result after operations

	tmp = hours_log;
	struct tm tm_ptr = *gmtime(&tmp);
	strftime (time_str, strlen("MM_YYYY")+1, "%m-%Y", &tm_ptr);
	if(type_log == TYPE_LOG_READINGS){
		snprintf(name_file, sizeof(name_file), "LOG_R_%s.txt", time_str);
		len = sizeof(TileInfoTypeDef);
	}
	else if(type_log == TYPE_LOG_PARAM_UPDATE){
		snprintf(name_file, sizeof(name_file), "LOG_P_U_%s.txt", time_str);
		len = sizeof(ContainerInfoTypeDef);
	}
	//------------------------------------------------------------------------------
	// Открываем или создаем новый файл
	fres = f_open(&fil, name_file, FA_READ);
	if(fres == FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("I was able read_archiv_file to open %s for writing\r\n", name_file);
#endif
	} else {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("f_open read_archiv_file error (%i)\r\n", fres);
#endif
	}
	//------------------------------------------------------------------------------
	// Запись строчки
	fres = f_lseek (&fil, position);
	fres |= f_read(&fil, data_hex, len*2, &bytesWrote);
	for(uint16_t i=0; i < len; i++){
		if(data_hex[i*2] >= 'A'){
			data_hex_dec = ((data_hex[i*2] - 'A' + 10) << 4);
		}
		else{
			data_hex_dec = ((data_hex[i*2] - 0x30) << 4);
		}
		if(data_hex[i*2+1] >= 'A'){
			data_hex_dec |= ((data_hex[i*2+1] - 'A' + 10));
		}
		else{
			data_hex_dec |= ((data_hex[i*2+1] - 0x30));
		}

		((uint8_t*)data)[i] = data_hex_dec;
	}
	if(fres == FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("Read %i bytes to %s, size file %i\r\n", position, name_file, f_size(&fil));
#endif
	} else {
#ifdef DEBUG_PRINTF_SD_CARD
	  	myprintf("f_read error (%i)\r\n", fres);
#endif
	}
	f_close(&fil);
	//------------------------------------------------------------------------------
	if(bytesWrote == len*2)
	{
		return (position + bytesWrote + 2);
	}
	else
	{
		return 0;
	}
}

//========================================================================================
// Записать лог в файл
static void writing_found_logs_to_file(uint8_t * data)
{
	uint16_t 	len = 0;
	TCHAR 		name_file[60] = {0};
	UINT 		bytesWrote;
	FIL 		fil; 		//File handle
	FRESULT 	fres; 		//Result after operations

	snprintf(name_file, sizeof(name_file), "FOUND_LOGS.txt");
	if(type_founds_logs_to_file == TYPE_LOG_READINGS){
		len = sizeof(TileInfoTypeDef);
	}
	else if(type_founds_logs_to_file == TYPE_LOG_PARAM_UPDATE){
		len = sizeof(ContainerInfoTypeDef);
	}
	//------------------------------------------------------------------------------
	// Открываем или создаем новый файл
	fres = f_open(&fil, name_file, FA_WRITE | FA_OPEN_APPEND);
	if(fres == FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("I was able to open %s for writing\r\n", name_file);
#endif
	} else {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("f_open error (%i)\r\n", fres);
#endif
	}
	//------------------------------------------------------------------------------
	// Запись строчки
	for(uint16_t i=0; i < len; ++i){
		snprintf(&data_hex[i*2], 3, "%02X", data[i]);
	}
	snprintf(&data_hex[len*2], 3, "\r\n");
	fres = f_write(&fil, data_hex, (len+1)*2, &bytesWrote);
	if(fres == FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("Wrote %i bytes to %s, size file %i\r\n", bytesWrote, name_file, f_size(&fil));
#endif
	} else {
#ifdef DEBUG_PRINTF_SD_CARD
	  	myprintf("f_write error (%i)\r\n", fres);
#endif
	}
	f_close(&fil);

}

//========================================================================================
// Чтение найденного лога из файла, по его порядковому номеру
static uint8_t reading_found_logs_from_file(uint8_t * data, uint16_t number_log)
{
	uint8_t		data_hex_dec;
	uint16_t 	len = 0;
	TCHAR 		name_file[60] = {0};
	UINT 		bytesWrote;
	FIL 		fil; 		//File handle
	FRESULT 	fres; 		//Result after operations

	snprintf(name_file, sizeof(name_file), "FOUND_LOGS.txt");
	if(type_founds_logs_to_file == TYPE_LOG_READINGS){
		len = sizeof(TileInfoTypeDef);
	}
	else if(type_founds_logs_to_file == TYPE_LOG_PARAM_UPDATE){
		len = sizeof(ContainerInfoTypeDef);
	}
	//------------------------------------------------------------------------------
	// Открываем или создаем новый файл
	fres = f_open(&fil, name_file, FA_READ);
	if(fres == FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("I was able to open %s for writing\r\n", name_file);
#endif
	} else {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("f_open error (%i)\r\n", fres);
#endif
	}
	//------------------------------------------------------------------------------
	// Запись строчки
	fres = f_lseek (&fil, number_log*(len*2 + 2));
	fres |= f_read(&fil, data_hex, len*2, &bytesWrote);
	for(uint16_t i=0; i < len; i++){
		if(data_hex[i*2] >= 'A'){
			data_hex_dec = ((data_hex[i*2] - 'A' + 10) << 4);
		}
		else{
			data_hex_dec = ((data_hex[i*2] - 0x30) << 4);
		}
		if(data_hex[i*2+1] >= 'A'){
			data_hex_dec |= ((data_hex[i*2+1] - 'A' + 10));
		}
		else{
			data_hex_dec |= ((data_hex[i*2+1] - 0x30));
		}

		((uint8_t*)data)[i] = data_hex_dec;
	}
	if(fres == FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("Read %i bytes to %s, size file %i\r\n", number_log*(len*2 + 2), name_file, f_size(&fil));
#endif
	} else {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("f_read error (%i)\r\n", fres);
#endif
	}
	f_close(&fil);
	//------------------------------------------------------------------------------
	if(bytesWrote == len*2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//========================================================================================
// Перезапись начала архива и удаление старого файла из за нехватки памяти
static void rewrite_state_file_archiv(void)
{
	TCHAR 			time_str[30] = {0};
	TCHAR 			name_file[60] = {0};
	time_t			tmp = 0;
	FIL 			fil; 		//File handle
	FRESULT 		fres; 		//Result after operations
	uint32_t 		data_time = read_state_file_archiv(TYPE_STATE_FILE_START);

	tmp = data_time;
	struct tm tm_ptr = *gmtime(&tmp);
	strftime (time_str, strlen("MM_YYYY")+1, "%m-%Y", &tm_ptr);

	snprintf(name_file, sizeof(name_file), "LOG_R_%s.txt", time_str);
	fres = f_open(&fil, name_file, FA_WRITE | FA_OPEN_ALWAYS);
	if(fres == FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("I was able rewrite to open %s for writing\r\n", name_file);
		f_close(&fil);
		fres = f_unlink(name_file);
		if (fres != FR_OK) {
	#ifdef DEBUG_PRINTF_SD_CARD
			myprintf("rewrite1 error (%i)\r\n", fres);
	#endif
		}
#endif
	} else {
#ifdef DEBUG_PRINTF_SD_CARD
		f_close(&fil);
		myprintf("f_open rewrite1 error (%i)\r\n", fres);
#endif
	}

	snprintf(name_file, sizeof(name_file), "LOG_P_U_%s.txt", time_str);
	fres = f_open(&fil, name_file, FA_WRITE | FA_OPEN_ALWAYS);
	if(fres == FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("I was able rewrite to open %s for writing\r\n", name_file);
		f_close(&fil);
		fres = f_unlink(name_file);
		if (fres != FR_OK) {
	#ifdef DEBUG_PRINTF_SD_CARD
			myprintf("rewrite2 error (%i)\r\n", fres);
	#endif
		}
#endif
	} else {
#ifdef DEBUG_PRINTF_SD_CARD
		f_close(&fil);
		myprintf("f_open rewrite2 error (%i)\r\n", fres);
#endif
	}

	tm_ptr.tm_mon += 1;
	if(tm_ptr.tm_mon >= 12){
		tm_ptr.tm_mon = 0;
		tm_ptr.tm_year += 1;
	}
	data_time = (uint32_t)mktime(&tm_ptr);
	write_state_file_archiv(TYPE_STATE_FILE_START, data_time);
}

//========================================================================================
// Запись времени начала или конца архива в файлы
static void write_state_file_archiv(TYPE_STATE_FILE type_state_file, uint32_t data_time)
{
	TCHAR 		name_file[60] = {0};
	UINT 		bytesWrote;
	FIL 		fil; 		//File handle
	FRESULT 	fres; 		//Result after operations

	if(type_state_file == TYPE_STATE_FILE_START){
		snprintf(name_file, sizeof(name_file), "start_archiv_data.txt");
	}
	else if(type_state_file == TYPE_STATE_FILE_STOP){
		snprintf(name_file, sizeof(name_file), "stop_archiv_data.txt");
	}
	//------------------------------------------------------------------------------
	// Открываем или создаем новый файл
	fres = f_open(&fil, name_file, FA_WRITE | FA_OPEN_ALWAYS);
	if(fres == FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("I was able to open %s for writing\r\n", name_file);
#endif
	} else {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("f_open error (%i)\r\n", fres);
#endif
	}
	//------------------------------------------------------------------------------
	// Запись строчки
	for(uint16_t i=0; i < 4; ++i){
		snprintf(&data_hex[i*2], 3, "%02X", ((uint8_t*)&data_time)[i]);
	}
	fres = f_write(&fil, data_hex, 4*2, &bytesWrote);
	if(fres == FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("Wrote %i bytes to %s, size file %i\r\n", bytesWrote, name_file, f_size(&fil));
#endif
	} else {
#ifdef DEBUG_PRINTF_SD_CARD
	  	myprintf("f_write error (%i)\r\n", fres);
#endif
	}
	f_close(&fil);
	//------------------------------------------------------------------------------
}

//========================================================================================
// Чтение времени начала или конца архива из файлы
static uint32_t read_state_file_archiv(TYPE_STATE_FILE type_state_file)
{
	uint32_t 	data_time;
	TCHAR 		name_file[60] = {0};
	UINT 		bytesWrote;
	FIL 		fil; 		//File handle
	FRESULT 	fres; 		//Result after operations

	if(type_state_file == TYPE_STATE_FILE_START){
		snprintf(name_file, sizeof(name_file), "start_archiv_data.txt");
	}
	else if(type_state_file == TYPE_STATE_FILE_STOP){
		snprintf(name_file, sizeof(name_file), "stop_archiv_data.txt");
	}
	//------------------------------------------------------------------------------
	// Открываем или создаем новый файл
	fres = f_open(&fil, name_file, FA_READ);
	if(fres == FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("I was able to open %s for reading\r\n", name_file);
#endif
	} else {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("f_open error (%i)\r\n", fres);
#endif
	}
	//------------------------------------------------------------------------------
	// Запись строчки
	fres = f_read(&fil, data_hex, 8, &bytesWrote);
	for(uint16_t i=0; i < 4; ++i){
		((uint8_t*)&data_time)[i] = ((data_hex[i*2] - 0x30) << 4) | (data_hex[i*2+1] - 0x30);
	}

	if(fres == FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("Read %i bytes to %s, size file %i\r\n", bytesWrote, name_file, f_size(&fil));
#endif
	} else {
#ifdef DEBUG_PRINTF_SD_CARD
	  	myprintf("f_read error (%i)\r\n", fres);
#endif
	}
	f_close(&fil);
	//------------------------------------------------------------------------------
	return data_time;
}

//========================================================================================
// Инициализация поиска по времени и Очистка(перезапись) файла содержащего найденные логи по фильтрам
static void init_log_search_by_filter_time(uint32_t time_start, uint32_t time_stop, uint16_t position)
{
	time_start_log = time_start;
	time_stop_log = time_stop;
	position_file = position;

	init_file_found_logs();
}

//========================================================================================
// Очистка(перезапись) файла содержащего найденные логи по фильтрам
static void init_file_found_logs(void)
{
	TCHAR 		name_file[60] = {0};
	FIL 		fil; 		//File handle
	FRESULT 	fres; 		//Result after operations

	snprintf(name_file, sizeof(name_file), "FOUND_LOGS.txt");
	//------------------------------------------------------------------------------
	// Создаем новый файл или перезаписываем старый
	fres = f_open(&fil, name_file, FA_WRITE | FA_CREATE_ALWAYS);
	if(fres == FR_OK) {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("I was able to open %s for writing\r\n", name_file);
#endif
	} else {
#ifdef DEBUG_PRINTF_SD_CARD
		myprintf("f_open error (%i)\r\n", fres);
#endif
	}
	f_close(&fil);

}

//========================================================================================
// Чтение найденных по фильтру логов из файла
static uint8_t log_search_by_filter(uint8_t * data, TYPE_LOG type_log,
		uint8_t channel_num_fil, uint8_t loop_state_fil,uint8_t thld_state_fil,uint16_t err_state_fil,
		uint8_t ch_type_fil, uint8_t units_fil, uint8_t formula_fil)
{
	uint8_t state_search_log = 0;
	TileInfoTypeDef 		*Event_log_readings_ptr 	= (TileInfoTypeDef*)data;
	ContainerInfoTypeDef 	*Event_log_param_update_ptr = (ContainerInfoTypeDef*)data;
	while(!state_search_log){
		time_start_log = parce_archive(data, time_start_log, time_stop_log, &position_file, type_log);
		if(time_start_log == time_stop_log){
#ifdef DEBUG_PRINTF_SD_CARD
			myprintf("Stop read file\r\n");
#endif
			return state_search_log;
		}
		else{
			if(type_log == TYPE_LOG_READINGS){
				if(((loop_state_fil)?((1 << Event_log_readings_ptr->loop_state) | loop_state_fil):(1)) &&
						((thld_state_fil)?((1 << Event_log_readings_ptr->thld_state) | thld_state_fil):(1)) &&
						((err_state_fil)?((1 << Event_log_readings_ptr->error_state) | err_state_fil):(1)) &&
						((ch_type_fil)?((1 << Event_log_readings_ptr->ch_type) | ch_type_fil):(1)) &&
						((units_fil)?((1 << Event_log_readings_ptr->units) | units_fil):(1)) &&
						((formula_fil)?((1 << Event_log_readings_ptr->formula) | formula_fil):(1)) &&
						((channel_num_fil <= 32)?(Event_log_readings_ptr->channel_num == channel_num_fil):(1))
						)
				{
					state_search_log = 1;
				}
			}
			else if(type_log == TYPE_LOG_PARAM_UPDATE){
				if(((loop_state_fil)?((1 << Event_log_param_update_ptr->loop_state) | loop_state_fil):(1)) &&
						((thld_state_fil)?((1 << Event_log_param_update_ptr->thld_state) | thld_state_fil):(1)) &&
						((err_state_fil)?((1 << Event_log_param_update_ptr->error_state) | err_state_fil):(1)) &&
						((ch_type_fil)?((1 << Event_log_param_update_ptr->ch_type) | ch_type_fil):(1)) &&
						((units_fil)?((1 << Event_log_param_update_ptr->units) | units_fil):(1)) &&
						((formula_fil)?((1 << Event_log_param_update_ptr->formula) | formula_fil):(1)) &&
						((channel_num_fil <= 32)?(Event_log_param_update_ptr->channel_num == channel_num_fil):(1))
						)
				{
					state_search_log = 1;
				}
			}
		}
	}
	return state_search_log;
}

