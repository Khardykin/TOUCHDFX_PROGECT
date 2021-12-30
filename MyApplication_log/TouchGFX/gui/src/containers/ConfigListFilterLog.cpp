#include <gui/containers/ConfigListFilterLog.hpp>
#include <touchgfx/Utils.hpp>

#include <gui/common/UserUtils.hpp>
#include <gui/common/ChannelInfo.hpp>

#ifndef SIMULATOR
#include <mb_regs_decoder.h>
#endif

ConfigListFilterLog::ConfigListFilterLog() :
	scrollListItemSelectedCallback(this, &ConfigListFilterLog::scrollListItemSelectedHandler), previousIndex(100), currentIndex(0), highlighted_box_width(0)
{

}

void ConfigListFilterLog::initialize()
{
	ConfigListFilterLogBase::initialize();

	scrollList.setItemSelectedCallback(scrollListItemSelectedCallback);
	if (list_id == ListID::list_channel)
		scrollList.setNumberOfItems(32);
	else if (list_id == ListID::list_units)
		scrollList.setNumberOfItems(UNITS_SIZE);
	else if (list_id == ListID::list_formula)
		scrollList.setNumberOfItems(GAS_SIZE);
}

void ConfigListFilterLog::setHighlighted(int16_t itemIndex)
{
	currentIndex = (1<<itemIndex);
}

void ConfigListFilterLog::scrollListUpdateItem(ListTile& item, int16_t itemIndex)
{
	Unicode::UnicodeChar item_text[16] = { 0 };
	item.setIndex((uint8_t)itemIndex);

	for (int i = 0; i < scrollListListItems.getNumberOfDrawables(); i++)
	{
		if (currentIndex & (1<<item.getIndex()))
		{
			item.setSelected(scrollList.getWidth());
		}
		else
		{
			item.setUnselected();
		}
	}

	if (list_id == ListID::list_channel)
	{
		if((itemIndex + 1) <= 32){
			Unicode::snprintf(item_text, 16, "%d", itemIndex + 1);
		}
		else{
			Unicode::snprintf(item_text, 16, "All");
		}
		item.updateText(item_text);
		scrollList.setNumberOfItems(33);
		scrollList.setCircular(true);
	}
//	else if(list_id == ListID::list_type_channel)
//	{
//		UserUtils utils;
//		char buf[16] = { 0 };
//
//		strcpy(buf, &());
//		Unicode::snprintf(item_text, 16, buf);
//
//		item.updateText(item_text);
//		scrollList.setNumberOfItems();
//		scrollList.setCircular(false);
//	}
//	else if(list_id == ListID::list_st_loop)
//	{
//		UserUtils utils;
//		char buf[16] = { 0 };
//
//		strcpy(buf, &());
//		Unicode::snprintf(item_text, 16, buf);
//
//		item.updateText(item_text);
//		scrollList.setNumberOfItems();
//		scrollList.setCircular(false);
//	}
//	else if (list_id == ListID::list_units)
//	{
//		UserUtils utils;
//		char buf[16] = { 0 };
//
//		strcpy(buf, &(units_list[Texts::getLanguage()][itemIndex + 1]));
//		Unicode::snprintf(item_text, 16, buf);
//
//		item.updateText(item_text);
//		scrollList.setNumberOfItems(4);
//		scrollList.setCircular(false);
//	}
//	else if(list_id == ListID::list_st_cur)
//	{
//		UserUtils utils;
//		char buf[16] = { 0 };
//
//		strcpy(buf, &());
//		Unicode::snprintf(item_text, 16, buf);
//
//		item.updateText(item_text);
//		scrollList.setNumberOfItems();
//		scrollList.setCircular(false);
//	}
//	else if(list_id == ListID::list_err)
//	{
//		UserUtils utils;
//		char buf[16] = { 0 };
//
//		strcpy(buf, &());
//		Unicode::snprintf(item_text, 16, buf);
//
//		item.updateText(item_text);
//		scrollList.setNumberOfItems();
//		scrollList.setCircular(false);
//	}
//	else if (list_id == ListID::list_formula)
//	{
//		UserUtils utils;
//		char buf[16] = { 0 };
//
//		strcpy(buf, gas_formulas_list[itemIndex + 1]);
//		Unicode::snprintf(item_text, 16, buf);
//
//		item.updateText(item_text);
//		scrollList.setNumberOfItems(GAS_SIZE);
//		scrollList.setCircular(false);
//	}
}

int16_t ConfigListFilterLog::getHeightNeeded()
{
	return 32 * scrollList.getNumberOfItems();
}

void ConfigListFilterLog::resizeXY(int x, int y)
{
//	highlighted_box_width = x;
	boxBg.setWidthHeight(x, y);
	scrollList.setWidthHeight(x, y);
}

void ConfigListFilterLog::setContainerID(ListID id)
{
	list_id = static_cast<ListID>(id);
}

void ConfigListFilterLog::scrollListItemSelectedHandler(int16_t itemSelected)
{
	if(list_id == ListID::list_channel){
		if(itemSelected <= 31){
			if(TESTBIT(currentIndex, itemSelected)){
				CLRBIT(currentIndex, itemSelected);
			}
			else{
				SETBIT(currentIndex, itemSelected);
			}
		}
		else{
			currentIndex = 0;
		}
	}
	else{
		if(itemSelected){
			if(TESTBIT(currentIndex, itemSelected)){
				CLRBIT(currentIndex, itemSelected);
			}
			else{
				SETBIT(currentIndex, itemSelected);
			}
		}
		else{
			currentIndex = 0;
			SETBIT(currentIndex, itemSelected);
		}
	}

	for (int i = 0; i < scrollListListItems.getNumberOfDrawables(); i++)
	{
		if((currentIndex & (1 << scrollListListItems[i].getIndex()))){
			scrollListListItems[i].setSelected(scrollList.getWidth());
		}
		else{
			scrollListListItems[i].setUnselected();
		}

		if((currentIndex == 0) && (itemSelected == scrollListListItems[i].getIndex())){
				scrollListListItems[i].setSelected(scrollList.getWidth());
		}
	}


	//Send signal to view
	if (viewCallback && viewCallback->isValid())
	{
		viewCallback->execute((uint8_t)itemSelected, this);
	}
}

void ConfigListFilterLog::setViewCallback(GenericCallback<uint8_t, ConfigListFilterLog *>& callback)
{
	viewCallback = &callback;
}
