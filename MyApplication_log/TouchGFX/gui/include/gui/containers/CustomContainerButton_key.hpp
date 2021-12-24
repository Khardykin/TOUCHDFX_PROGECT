#ifndef CUSTOMCONTAINERBUTTON_KEY_HPP
#define CUSTOMCONTAINERBUTTON_KEY_HPP

#include <gui_generated/containers/CustomContainerButton_keyBase.hpp>

class CustomContainerButton_key : public CustomContainerButton_keyBase
{
public:
    CustomContainerButton_key();
    virtual ~CustomContainerButton_key() {}

    virtual void initialize();

    void functionButtonClick();
    void initialize_my(Unicode::UnicodeChar text);

protected:
};

#endif // CUSTOMCONTAINERBUTTON_KEY_HPP
