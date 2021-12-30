#ifndef LISTTILE_HPP
#define LISTTILE_HPP

#include <gui_generated/containers/ListTileBase.hpp>

class ListTile : public ListTileBase
{
public:
    ListTile();
    virtual ~ListTile() {}

    virtual void initialize();

    void updateText(Unicode::UnicodeChar* buf);
    void setIndex(uint8_t ind);
    uint8_t getIndex();
    void setSelected(int x);
    void setUnselected();
    bool isSelected();

protected:
    uint8_t index;
    bool selected;

protected:
};

#endif // LISTTILE_HPP
