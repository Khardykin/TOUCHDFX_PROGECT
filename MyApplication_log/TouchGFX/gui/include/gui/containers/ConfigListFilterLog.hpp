#ifndef CONFIGLISTFILTERLOG_HPP
#define CONFIGLISTFILTERLOG_HPP

#include <gui_generated/containers/ConfigListFilterLogBase.hpp>

class ScreenConfigView;

class ConfigListFilterLog : public ConfigListFilterLogBase
{
public:
    ConfigListFilterLog();
    virtual ~ConfigListFilterLog()
    {
    }

    virtual void initialize();

    void setHighlighted(int16_t itemIndex);
    virtual void scrollListUpdateItem(ListTile& item, int16_t itemIndex);
    void scrollListItemSelectedHandler(int16_t itemSelected);

    void resizeXY(int x, int y);
    int16_t getHeightNeeded();
    //Method to set the view callback
    void setViewCallback(GenericCallback<uint8_t, ConfigListFilterLog*>& callback);

    enum class ListID
    {
        list_unknown = 0,
        list_channel,
		list_type_channel,
        list_st_loop,
		list_units,
		list_st_cur,
		list_err,
        list_formula,
    };

    void setContainerID(ListID id);

protected:

    GenericCallback<uint8_t, ConfigListFilterLog*>* viewCallback;

    // Callback which is executed when a item in the scroll list is selected.
    Callback<ConfigListFilterLog, int16_t> scrollListItemSelectedCallback;

private:
    uint8_t previousIndex;
    uint64_t currentIndex;
    int highlighted_box_width;

    ListID list_id = ListID::list_channel;
};

#endif // CONFIGLISTFILTERLOG_HPP
