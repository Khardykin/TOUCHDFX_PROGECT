#include <gui/containers/CustomContainerTableLog_Type2.hpp>

#include "time.h"

#ifndef SIMULATOR
#include <mb_regs_decoder.h>
#endif

static time_p tmp;
static struct tm tm_ptr;

CustomContainerTableLog_Type2::CustomContainerTableLog_Type2()
{

}

void CustomContainerTableLog_Type2::initialize()
{
    CustomContainerTableLog_Type2Base::initialize();
}

void CustomContainerTableLog_Type2::UpdateLog_clear(void)
{
	setVisible(false);
	invalidate();
}

void CustomContainerTableLog_Type2::UpdateLog(ContainerInfoTypeDef * data)
{
	char buf[16] = { 0 };
	setVisible(true);
	tmp = data->working_hours_log;
	tm_ptr = *gmtime(&tmp);
	tm_ptr.tm_mon = 1;
	tm_ptr.tm_mday = 30;

	Unicode::snprintf(textAreaDataTimeBuffer, TEXTAREADATATIME_SIZE, "%.2d-%.2d-%4d %.2d:%.2d",
	tm_ptr.tm_mday, tm_ptr.tm_mon, tm_ptr.tm_year + 1900, tm_ptr.tm_hour, tm_ptr.tm_min);

	Unicode::snprintf(textAreaNumChanBuffer, TEXTAREANUMCHAN_SIZE, "%d", data->channel_num);

	Unicode::snprintfFloat(textAreaThreshold_1Buffer, TEXTAREATHRESHOLD_1_SIZE, "%.1f", data->threshold_1);

	Unicode::snprintfFloat(textAreaThreshold_2Buffer, TEXTAREATHRESHOLD_2_SIZE, "%.1f", data->threshold_2);

	Unicode::snprintfFloat(textAreaThreshold_3Buffer, TEXTAREATHRESHOLD_3_SIZE, "%.1f", data->threshold_3);

	Unicode::snprintfFloat(textAreaFullScaleBuffer, TEXTAREAFULLSCALE_SIZE, "%.1f", data->full_scale);

	Unicode::snprintfFloat(textAreaFullHysteresisBuffer, TEXTAREAFULLHYSTERESIS_SIZE, "%.1f", data->hysteresis);

	Unicode::snprintf(textAreaUnitBuffer, TEXTAREAUNIT_SIZE, units_list[data->units]);

	Unicode::snprintf(textAreaGasBuffer, TEXTAREAGAS_SIZE, gas_formulas_list[data->formula]);

	Unicode::snprintf(textAreaTagBuffer, TEXTAREATAG_SIZE, data->buf_tag);

	invalidate();
}
