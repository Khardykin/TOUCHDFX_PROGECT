#ifndef CUSTOMCONTAINERTABLELOG_TYPE2_HPP
#define CUSTOMCONTAINERTABLELOG_TYPE2_HPP

#include <gui_generated/containers/CustomContainerTableLog_Type2Base.hpp>

extern "C"{
#include "parce_archiv.h"
}

class CustomContainerTableLog_Type2 : public CustomContainerTableLog_Type2Base
{
public:
    CustomContainerTableLog_Type2();
    virtual ~CustomContainerTableLog_Type2() {}

    virtual void initialize();

    void UpdateLog(ContainerInfoTypeDef * data);
    void UpdateLog_clear(void);
protected:
};

#endif // CUSTOMCONTAINERTABLELOG_TYPE2_HPP
