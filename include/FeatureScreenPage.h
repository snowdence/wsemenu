#ifndef FeatureScreenPage_h
#define FeatureScreenPage_h

#if defined(WIRING) && WIRING >= 100
#include <Wiring.h>
#elif defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "IMenuFeature.h"
class FeatureScreenPage : public IMenuFeature
{
public:
	FeatureScreenPage(void (*renderFunc)())
	{
		this->setHookRender(renderFunc);
	}

	void down() override
	{
		//do nothing
		IMenuFeature::executeHookDownBtnFunc();
	}

	IMenuFeature *ok() override
	{
		IMenuFeature::executeHookOkBtnFunc();

		//do nothing
		return this;
	}
	void render(LiquidCrystal_I2C *lcd) override
	{
		Serial.println("FeatureScreenPage render()");
		this->hookRenderFunc();
	}
};
#endif