#include <gui/containers/ListTile.hpp>

ListTile::ListTile() :
    index(0), selected(false)
{

}

void ListTile::initialize()
{
    ListTileBase::initialize();
}

void ListTile::updateText(Unicode::UnicodeChar* buf)
{
    Unicode::snprintf(textBuffer, TEXT_SIZE, buf);
    text.invalidate();
}

void ListTile::setIndex(uint8_t ind)
{
    index = ind;
}

uint8_t ListTile::getIndex()
{
    return index;
}

void ListTile::setSelected(int x)
{
    boxBg.setWidth(x);
    boxBg.setVisible(true);
    invalidate();
    selected = true;
}

void ListTile::setUnselected()
{
    boxBg.setVisible(false);
    invalidate();
    selected = false;
}

bool ListTile::isSelected()
{
    return selected;
}