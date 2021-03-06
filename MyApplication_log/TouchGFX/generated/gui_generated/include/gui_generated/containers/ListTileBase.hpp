/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef LISTTILEBASE_HPP
#define LISTTILEBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class ListTileBase : public touchgfx::Container
{
public:
    ListTileBase();
    virtual ~ListTileBase() {}
    virtual void initialize();

    /*
     * Custom Trigger Callback Setters
     */
    void setTrigger1Callback(touchgfx::GenericCallback<>& callback)
    {
        this->trigger1Callback = &callback;
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Custom Trigger Emitters
     */
    virtual void emitTrigger1Callback()
    {
        if (trigger1Callback && trigger1Callback->isValid())
        {
            this->trigger1Callback->execute();
        }
    }

    /*
     * Member Declarations
     */
    touchgfx::Box boxBg_1;
    touchgfx::Box boxBg;
    touchgfx::TextAreaWithOneWildcard text;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXT_SIZE = 16;
    touchgfx::Unicode::UnicodeChar textBuffer[TEXT_SIZE];

private:

    /*
     * Custom Trigger Callback Declarations
     */
    touchgfx::GenericCallback<>* trigger1Callback;

};

#endif // LISTTILEBASE_HPP
