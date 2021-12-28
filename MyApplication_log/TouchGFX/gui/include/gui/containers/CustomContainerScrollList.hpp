#ifndef CUSTOMCONTAINERSCROLLLIST_HPP
#define CUSTOMCONTAINERSCROLLLIST_HPP

#include <gui_generated/containers/CustomContainerScrollListBase.hpp>

class CustomContainerScrollList : public CustomContainerScrollListBase
{
public:
    CustomContainerScrollList();
    virtual ~CustomContainerScrollList() {}

    virtual void initialize();
protected:
};

#endif // CUSTOMCONTAINERSCROLLLIST_HPP
