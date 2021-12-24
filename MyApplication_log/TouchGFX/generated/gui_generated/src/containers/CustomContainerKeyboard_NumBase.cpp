/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/CustomContainerKeyboard_NumBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

CustomContainerKeyboard_NumBase::CustomContainerKeyboard_NumBase() :
    flexButtonCallback(this, &CustomContainerKeyboard_NumBase::flexButtonCallbackHandler),
    customContainerButton_key1TriggerButton_keyCallback(this, &CustomContainerKeyboard_NumBase::customContainerButton_key1TriggerButton_keyCallbackHandler),
    customContainerButton_key2TriggerButton_keyCallback(this, &CustomContainerKeyboard_NumBase::customContainerButton_key2TriggerButton_keyCallbackHandler),
    customContainerButton_key3TriggerButton_keyCallback(this, &CustomContainerKeyboard_NumBase::customContainerButton_key3TriggerButton_keyCallbackHandler),
    customContainerButton_key4TriggerButton_keyCallback(this, &CustomContainerKeyboard_NumBase::customContainerButton_key4TriggerButton_keyCallbackHandler),
    customContainerButton_key5TriggerButton_keyCallback(this, &CustomContainerKeyboard_NumBase::customContainerButton_key5TriggerButton_keyCallbackHandler),
    customContainerButton_key6TriggerButton_keyCallback(this, &CustomContainerKeyboard_NumBase::customContainerButton_key6TriggerButton_keyCallbackHandler),
    customContainerButton_key7TriggerButton_keyCallback(this, &CustomContainerKeyboard_NumBase::customContainerButton_key7TriggerButton_keyCallbackHandler),
    customContainerButton_key8TriggerButton_keyCallback(this, &CustomContainerKeyboard_NumBase::customContainerButton_key8TriggerButton_keyCallbackHandler),
    customContainerButton_key9TriggerButton_keyCallback(this, &CustomContainerKeyboard_NumBase::customContainerButton_key9TriggerButton_keyCallbackHandler),
    customContainerButton_key10TriggerButton_keyCallback(this, &CustomContainerKeyboard_NumBase::customContainerButton_key10TriggerButton_keyCallbackHandler),
    customContainerButton_key11TriggerButton_keyCallback(this, &CustomContainerKeyboard_NumBase::customContainerButton_key11TriggerButton_keyCallbackHandler),
    customContainerButton_key12TriggerButton_keyCallback(this, &CustomContainerKeyboard_NumBase::customContainerButton_key12TriggerButton_keyCallbackHandler),
    triggerKeyboard_NumCallback(0)
{
    setWidth(270);
    setHeight(300);
    boxWithBorder1.setPosition(0, 0, 270, 300);
    boxWithBorder1.setColor(touchgfx::Color::getColorFromRGB(135, 135, 135));
    boxWithBorder1.setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    boxWithBorder1.setBorderSize(5);

    flexButtonEnter.setBoxWithBorderPosition(0, 0, 60, 121);
    flexButtonEnter.setBorderSize(1);
    flexButtonEnter.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    flexButtonEnter.setText(TypedText(T___SINGLEUSE_O6I9));
    flexButtonEnter.setTextPosition(0, 50, 60, 121);
    flexButtonEnter.setTextColors(touchgfx::Color::getColorFromRGB(10, 10, 10), touchgfx::Color::getColorFromRGB(10, 10, 10));
    flexButtonEnter.setPosition(196, 106, 60, 121);
    flexButtonEnter.setAction(flexButtonCallback);

    flexButtonClose.setBoxWithBorderPosition(0, 0, 60, 60);
    flexButtonClose.setBorderSize(1);
    flexButtonClose.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    flexButtonClose.setText(TypedText(T___SINGLEUSE_66SU));
    flexButtonClose.setTextPosition(0, 20, 60, 60);
    flexButtonClose.setTextColors(touchgfx::Color::getColorFromRGB(10, 10, 10), touchgfx::Color::getColorFromRGB(10, 10, 10));
    flexButtonClose.setPosition(196, 228, 60, 60);
    flexButtonClose.setAction(flexButtonCallback);

    textArea1.setPosition(13, 14, 200, 25);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea1.setLinespacing(0);
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_4UB8).getText());
    textArea1.setWildcard(textArea1Buffer);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_Z4JY));

    customContainerButton_key1.setXY(13, 45);
    customContainerButton_key1.setTriggerButton_keyCallback(customContainerButton_key1TriggerButton_keyCallback);

    customContainerButton_key2.setXY(74, 45);
    customContainerButton_key2.setTriggerButton_keyCallback(customContainerButton_key2TriggerButton_keyCallback);

    customContainerButton_key3.setXY(135, 45);
    customContainerButton_key3.setTriggerButton_keyCallback(customContainerButton_key3TriggerButton_keyCallback);

    customContainerButton_key4.setXY(13, 106);
    customContainerButton_key4.setTriggerButton_keyCallback(customContainerButton_key4TriggerButton_keyCallback);

    customContainerButton_key5.setXY(74, 106);
    customContainerButton_key5.setTriggerButton_keyCallback(customContainerButton_key5TriggerButton_keyCallback);

    customContainerButton_key6.setXY(135, 106);
    customContainerButton_key6.setTriggerButton_keyCallback(customContainerButton_key6TriggerButton_keyCallback);

    customContainerButton_key7.setXY(13, 167);
    customContainerButton_key7.setTriggerButton_keyCallback(customContainerButton_key7TriggerButton_keyCallback);

    customContainerButton_key8.setXY(74, 167);
    customContainerButton_key8.setTriggerButton_keyCallback(customContainerButton_key8TriggerButton_keyCallback);

    customContainerButton_key9.setXY(135, 167);
    customContainerButton_key9.setTriggerButton_keyCallback(customContainerButton_key9TriggerButton_keyCallback);

    customContainerButton_key10.setXY(13, 228);
    customContainerButton_key10.setTriggerButton_keyCallback(customContainerButton_key10TriggerButton_keyCallback);

    customContainerButton_key11.setXY(74, 228);
    customContainerButton_key11.setTriggerButton_keyCallback(customContainerButton_key11TriggerButton_keyCallback);

    customContainerButton_key12.setXY(135, 228);
    customContainerButton_key12.setTriggerButton_keyCallback(customContainerButton_key12TriggerButton_keyCallback);

    flexButton_del_pre.setBoxWithBorderPosition(0, 0, 60, 60);
    flexButton_del_pre.setBorderSize(1);
    flexButton_del_pre.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    flexButton_del_pre.setText(TypedText(T___SINGLEUSE_TS12));
    flexButton_del_pre.setTextPosition(0, 20, 60, 60);
    flexButton_del_pre.setTextColors(touchgfx::Color::getColorFromRGB(10, 10, 10), touchgfx::Color::getColorFromRGB(10, 10, 10));
    flexButton_del_pre.setPosition(196, 45, 60, 60);
    flexButton_del_pre.setAction(flexButtonCallback);

    add(boxWithBorder1);
    add(flexButtonEnter);
    add(flexButtonClose);
    add(textArea1);
    add(customContainerButton_key1);
    add(customContainerButton_key2);
    add(customContainerButton_key3);
    add(customContainerButton_key4);
    add(customContainerButton_key5);
    add(customContainerButton_key6);
    add(customContainerButton_key7);
    add(customContainerButton_key8);
    add(customContainerButton_key9);
    add(customContainerButton_key10);
    add(customContainerButton_key11);
    add(customContainerButton_key12);
    add(flexButton_del_pre);
}

void CustomContainerKeyboard_NumBase::initialize()
{
    customContainerButton_key1.initialize();
    customContainerButton_key2.initialize();
    customContainerButton_key3.initialize();
    customContainerButton_key4.initialize();
    customContainerButton_key5.initialize();
    customContainerButton_key6.initialize();
    customContainerButton_key7.initialize();
    customContainerButton_key8.initialize();
    customContainerButton_key9.initialize();
    customContainerButton_key10.initialize();
    customContainerButton_key11.initialize();
    customContainerButton_key12.initialize();
}

void CustomContainerKeyboard_NumBase::customContainerButton_key1TriggerButton_keyCallbackHandler()
{
    //Interaction3
    //When customContainerButton_key1 triggerButton_key call action1 on CustomContainerKeyboard_Num
    //Call action1
    action1();
}

void CustomContainerKeyboard_NumBase::customContainerButton_key2TriggerButton_keyCallbackHandler()
{
    //Interaction4
    //When customContainerButton_key2 triggerButton_key call action1 on CustomContainerKeyboard_Num
    //Call action1
    action1();
}

void CustomContainerKeyboard_NumBase::customContainerButton_key3TriggerButton_keyCallbackHandler()
{
    //Interaction5
    //When customContainerButton_key3 triggerButton_key call action1 on CustomContainerKeyboard_Num
    //Call action1
    action1();
}

void CustomContainerKeyboard_NumBase::customContainerButton_key4TriggerButton_keyCallbackHandler()
{
    //Interaction6
    //When customContainerButton_key4 triggerButton_key call action1 on CustomContainerKeyboard_Num
    //Call action1
    action1();
}

void CustomContainerKeyboard_NumBase::customContainerButton_key5TriggerButton_keyCallbackHandler()
{
    //Interaction7
    //When customContainerButton_key5 triggerButton_key call action1 on CustomContainerKeyboard_Num
    //Call action1
    action1();
}

void CustomContainerKeyboard_NumBase::customContainerButton_key6TriggerButton_keyCallbackHandler()
{
    //Interaction8
    //When customContainerButton_key6 triggerButton_key call action1 on CustomContainerKeyboard_Num
    //Call action1
    action1();
}

void CustomContainerKeyboard_NumBase::customContainerButton_key7TriggerButton_keyCallbackHandler()
{
    //Interaction9
    //When customContainerButton_key7 triggerButton_key call action1 on CustomContainerKeyboard_Num
    //Call action1
    action1();
}

void CustomContainerKeyboard_NumBase::customContainerButton_key8TriggerButton_keyCallbackHandler()
{
    //Interaction10
    //When customContainerButton_key8 triggerButton_key call action1 on CustomContainerKeyboard_Num
    //Call action1
    action1();
}

void CustomContainerKeyboard_NumBase::customContainerButton_key9TriggerButton_keyCallbackHandler()
{
    //Interaction11
    //When customContainerButton_key9 triggerButton_key call action1 on CustomContainerKeyboard_Num
    //Call action1
    action1();
}

void CustomContainerKeyboard_NumBase::customContainerButton_key10TriggerButton_keyCallbackHandler()
{
    //Interaction12
    //When customContainerButton_key10 triggerButton_key call action1 on CustomContainerKeyboard_Num
    //Call action1
    action1();
}

void CustomContainerKeyboard_NumBase::customContainerButton_key11TriggerButton_keyCallbackHandler()
{
    //Interaction13
    //When customContainerButton_key11 triggerButton_key call action1 on CustomContainerKeyboard_Num
    //Call action1
    action1();
}

void CustomContainerKeyboard_NumBase::customContainerButton_key12TriggerButton_keyCallbackHandler()
{
    //Interaction14
    //When customContainerButton_key12 triggerButton_key call action1 on CustomContainerKeyboard_Num
    //Call action1
    action1();
}

void CustomContainerKeyboard_NumBase::action1()
{

}

void CustomContainerKeyboard_NumBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &flexButtonEnter)
    {
        //Interaction1
        //When flexButtonEnter clicked call virtual function
        //Call ClickButtonEnter
        ClickButtonEnter();

        //Interaction15
        //When flexButtonEnter clicked emit triggerKeyboard_Num callback
        //Emit callback
        emitTriggerKeyboard_NumCallback();
    }
    else if (&src == &flexButtonClose)
    {
        //Interaction2
        //When flexButtonClose clicked call virtual function
        //Call ClickButtonCloseKeyboard
        ClickButtonCloseKeyboard();
    }
    else if (&src == &flexButton_del_pre)
    {
        //Interaction16
        //When flexButton_del_pre clicked call virtual function
        //Call ClickButtonDelPre
        ClickButtonDelPre();
    }
}

