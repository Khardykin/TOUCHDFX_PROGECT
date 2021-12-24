#include <gui/containers/CustomContainerTableLog.hpp>

#include "time.h"


static time_p tmp;
static struct tm tm_ptr;

CustomContainerTableLog::CustomContainerTableLog()
{

}

void CustomContainerTableLog::initialize()
{
    CustomContainerTableLogBase::initialize();
}

void CustomContainerTableLog::UpdateLog_1(TileInfoTypeDef * data)
{
	setVisible(true);
	tmp = data->working_hours_log;
	tm_ptr = *gmtime(&tmp);
	tm_ptr.tm_mon = 1;
	tm_ptr.tm_mday = 30;
//
	Unicode::snprintf(textAreaDataTimeBuffer, TEXTAREADATATIME_SIZE, "%.2d-%.2d-%4d %.2d:%.2d",
	tm_ptr.tm_mday, tm_ptr.tm_mon, tm_ptr.tm_year + 1900, tm_ptr.tm_hour, tm_ptr.tm_min);
//
	Unicode::snprintf(textAreaNumChanBuffer, TEXTAREANUMCHAN_SIZE, "%d", data->channel_num);
//
	Unicode::snprintf(textAreaTypeChanBuffer, TEXTAREATYPECHAN_SIZE, "%s", NamesTypeChannel[data->ch_type]);
//
//	Unicode::snprintf(textAreaStLoopBuffer, TEXTAREASTLOOP_SIZE, "%s", NamesStLoop[st_loop]);
//
//	Unicode::snprintf(textAreaConcBuffer, TEXTAREACONC_SIZE, "%.1f", conc);
//
//	Unicode::snprintf(textAreaUnitBuffer, TEXTAREAUNIT_SIZE, "%s", NamesUnit[unit]);
//
//	Unicode::snprintf(textAreaStCurBuffer, TEXTAREASTCUR_SIZE, "%s", NamesStCur[st_cur]);
//
//	Unicode::snprintf(textAreaErrBuffer, TEXTAREAERR_SIZE, "%s", NamesErr[err]);
//
//	Unicode::snprintf(textAreaGasBuffer, TEXTAREAGAS_SIZE, "%s", NamesGas[gas]);

	invalidate();
}

void CustomContainerTableLog::UpdateLog_1_clear(void)
{
	setVisible(false);
	invalidate();
}

void CustomContainerTableLog::UpdateLog_2(ContainerInfoTypeDef * data)
{
//	time_t tmp = data->working_hours_log;
//	struct tm tm_ptr = *gmtime(&tmp);
////	tm_ptr.tm_min = 33;
////
//	Unicode::snprintf(textAreaDataTimeBuffer, TEXTAREADATATIME_SIZE, "%.2d-%.2d-%4d %.2d:%.2d",
//	tm_ptr.tm_mday, tm_ptr.tm_mon, tm_ptr.tm_year + 1900, tm_ptr.tm_hour, tm_ptr.tm_min);
////
//	Unicode::snprintf(textAreaNumChanBuffer, TEXTAREANUMCHAN_SIZE, "%d", chan);
////
////	Unicode::snprintf(textAreaTypeChanBuffer, TEXTAREATYPECHAN_SIZE, "%s", NamesTypeChannel[type_chan]);
////
////	Unicode::snprintf(textAreaStLoopBuffer, TEXTAREASTLOOP_SIZE, "%s", NamesStLoop[st_loop]);
////
////	Unicode::snprintf(textAreaConcBuffer, TEXTAREACONC_SIZE, "%.1f", conc);
////
////	Unicode::snprintf(textAreaUnitBuffer, TEXTAREAUNIT_SIZE, "%s", NamesUnit[unit]);
////
////	Unicode::snprintf(textAreaStCurBuffer, TEXTAREASTCUR_SIZE, "%s", NamesStCur[st_cur]);
////
////	Unicode::snprintf(textAreaErrBuffer, TEXTAREAERR_SIZE, "%s", NamesErr[err]);
////
////	Unicode::snprintf(textAreaGasBuffer, TEXTAREAGAS_SIZE, "%s", NamesGas[gas]);

	invalidate();
}
