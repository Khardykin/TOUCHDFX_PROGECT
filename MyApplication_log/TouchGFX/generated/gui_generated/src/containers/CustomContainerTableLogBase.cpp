/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/CustomContainerTableLogBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

CustomContainerTableLogBase::CustomContainerTableLogBase()
{
    setWidth(750);
    setHeight(20);
    boxWithBorderDataTime.setPosition(0, 0, 150, 20);
    boxWithBorderDataTime.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    boxWithBorderDataTime.setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    boxWithBorderDataTime.setBorderSize(1);

    boxWithBorderChan.setPosition(150, 0, 50, 20);
    boxWithBorderChan.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    boxWithBorderChan.setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    boxWithBorderChan.setBorderSize(1);

    boxWithBorderTypeChan.setPosition(200, 0, 100, 20);
    boxWithBorderTypeChan.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    boxWithBorderTypeChan.setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    boxWithBorderTypeChan.setBorderSize(1);

    boxWithBorderStLoop.setPosition(300, 0, 100, 20);
    boxWithBorderStLoop.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    boxWithBorderStLoop.setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    boxWithBorderStLoop.setBorderSize(1);

    boxWithBorderConc.setPosition(400, 0, 50, 20);
    boxWithBorderConc.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    boxWithBorderConc.setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    boxWithBorderConc.setBorderSize(1);

    boxWithBorderUnit.setPosition(450, 0, 70, 20);
    boxWithBorderUnit.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    boxWithBorderUnit.setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    boxWithBorderUnit.setBorderSize(1);

    boxWithBorderStCur.setPosition(520, 0, 80, 20);
    boxWithBorderStCur.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    boxWithBorderStCur.setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    boxWithBorderStCur.setBorderSize(1);

    boxWithBorderErr.setPosition(600, 0, 50, 20);
    boxWithBorderErr.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    boxWithBorderErr.setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    boxWithBorderErr.setBorderSize(1);

    boxWithBorderGas.setPosition(650, 0, 100, 20);
    boxWithBorderGas.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    boxWithBorderGas.setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    boxWithBorderGas.setBorderSize(1);

    textAreaDataTime.setPosition(0, 0, 150, 19);
    textAreaDataTime.setColor(touchgfx::Color::getColorFromRGB(3, 2, 2));
    textAreaDataTime.setLinespacing(1);
    Unicode::snprintf(textAreaDataTimeBuffer, TEXTAREADATATIME_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_WIXH).getText());
    textAreaDataTime.setWildcard(textAreaDataTimeBuffer);
    textAreaDataTime.setTypedText(touchgfx::TypedText(T___SINGLEUSE_LBEI));

    textAreaNumChan.setPosition(150, 0, 50, 19);
    textAreaNumChan.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textAreaNumChan.setLinespacing(0);
    Unicode::snprintf(textAreaNumChanBuffer, TEXTAREANUMCHAN_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_53KN).getText());
    textAreaNumChan.setWildcard(textAreaNumChanBuffer);
    textAreaNumChan.setTypedText(touchgfx::TypedText(T___SINGLEUSE_L982));

    textAreaTypeChan.setPosition(200, 0, 100, 19);
    textAreaTypeChan.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textAreaTypeChan.setLinespacing(0);
    Unicode::snprintf(textAreaTypeChanBuffer, TEXTAREATYPECHAN_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_P13T).getText());
    textAreaTypeChan.setWildcard(textAreaTypeChanBuffer);
    textAreaTypeChan.setTypedText(touchgfx::TypedText(T___SINGLEUSE_DOAO));

    textAreaStLoop.setPosition(300, 0, 100, 19);
    textAreaStLoop.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textAreaStLoop.setLinespacing(0);
    Unicode::snprintf(textAreaStLoopBuffer, TEXTAREASTLOOP_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_A188).getText());
    textAreaStLoop.setWildcard(textAreaStLoopBuffer);
    textAreaStLoop.setTypedText(touchgfx::TypedText(T___SINGLEUSE_I04R));

    textAreaConc.setPosition(400, 0, 50, 19);
    textAreaConc.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textAreaConc.setLinespacing(0);
    Unicode::snprintf(textAreaConcBuffer, TEXTAREACONC_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_QS1C).getText());
    textAreaConc.setWildcard(textAreaConcBuffer);
    textAreaConc.setTypedText(touchgfx::TypedText(T___SINGLEUSE_Q6FU));

    textAreaUnit.setPosition(450, 0, 70, 19);
    textAreaUnit.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textAreaUnit.setLinespacing(0);
    Unicode::snprintf(textAreaUnitBuffer, TEXTAREAUNIT_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_LNEH).getText());
    textAreaUnit.setWildcard(textAreaUnitBuffer);
    textAreaUnit.setTypedText(touchgfx::TypedText(T___SINGLEUSE_YDSR));

    textAreaStCur.setPosition(520, 0, 80, 19);
    textAreaStCur.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textAreaStCur.setLinespacing(0);
    Unicode::snprintf(textAreaStCurBuffer, TEXTAREASTCUR_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_83ZL).getText());
    textAreaStCur.setWildcard(textAreaStCurBuffer);
    textAreaStCur.setTypedText(touchgfx::TypedText(T___SINGLEUSE_IJ1U));

    textAreaErr.setPosition(600, 0, 50, 19);
    textAreaErr.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textAreaErr.setLinespacing(0);
    Unicode::snprintf(textAreaErrBuffer, TEXTAREAERR_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_60JG).getText());
    textAreaErr.setWildcard(textAreaErrBuffer);
    textAreaErr.setTypedText(touchgfx::TypedText(T___SINGLEUSE_PXKK));

    textAreaGas.setPosition(650, 0, 100, 19);
    textAreaGas.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textAreaGas.setLinespacing(0);
    Unicode::snprintf(textAreaGasBuffer, TEXTAREAGAS_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_A04E).getText());
    textAreaGas.setWildcard(textAreaGasBuffer);
    textAreaGas.setTypedText(touchgfx::TypedText(T___SINGLEUSE_JQ77));

    add(boxWithBorderDataTime);
    add(boxWithBorderChan);
    add(boxWithBorderTypeChan);
    add(boxWithBorderStLoop);
    add(boxWithBorderConc);
    add(boxWithBorderUnit);
    add(boxWithBorderStCur);
    add(boxWithBorderErr);
    add(boxWithBorderGas);
    add(textAreaDataTime);
    add(textAreaNumChan);
    add(textAreaTypeChan);
    add(textAreaStLoop);
    add(textAreaConc);
    add(textAreaUnit);
    add(textAreaStCur);
    add(textAreaErr);
    add(textAreaGas);
}

void CustomContainerTableLogBase::initialize()
{

}

