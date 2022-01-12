#include <gui/containers/CustomContainerTableLog.hpp>

#include "time.h"

#ifndef SIMULATOR
#include <mb_regs_decoder.h>
#endif

static time_p tmp;
static struct tm tm_ptr;

CustomContainerTableLog::CustomContainerTableLog()
{

}

void CustomContainerTableLog::initialize()
{
    CustomContainerTableLogBase::initialize();
}

void CustomContainerTableLog::UpdateLog(TileInfoTypeDef * data)
{
	setVisible(true);
	tmp = data->working_hours_log;
	tm_ptr = *gmtime(&tmp);
	tm_ptr.tm_mon = 1;
	tm_ptr.tm_mday = 30;

	Unicode::snprintf(textAreaDataTimeBuffer, TEXTAREADATATIME_SIZE, "%.2d-%.2d-%4d %.2d:%.2d",
	tm_ptr.tm_mday, tm_ptr.tm_mon, tm_ptr.tm_year + 1900, tm_ptr.tm_hour, tm_ptr.tm_min);

	Unicode::snprintf(textAreaNumChanBuffer, TEXTAREANUMCHAN_SIZE, "%d", data->channel_num);

	Unicode::snprintf(textAreaTypeChanBuffer, TEXTAREATYPECHAN_SIZE, "%s", NamesTypeChannel[data->ch_type]);

//	Unicode::snprintf(textAreaStLoopBuffer, TEXTAREASTLOOP_SIZE, NamesStLoop[data->loop_state]);

	Unicode::snprintfFloat(textAreaConcBuffer, TEXTAREACONC_SIZE, "%.1f", data->concentration);

	Unicode::snprintf(textAreaUnitBuffer, TEXTAREAUNIT_SIZE, units_list[data->units]);

//	Unicode::snprintf(textAreaStCurBuffer, TEXTAREASTCUR_SIZE, NamesStCur[data->thld_state]);
//
//	Unicode::snprintf(textAreaErrBuffer, TEXTAREAERR_SIZE, NamesErr[data->error_state]);
//
	Unicode::snprintf(textAreaGasBuffer, TEXTAREAGAS_SIZE, gas_formulas_list[data->formula]);

	invalidate();
}

void CustomContainerTableLog::UpdateLog_clear(void)
{
	setVisible(false);
	invalidate();
}

