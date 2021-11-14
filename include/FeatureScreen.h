#ifndef FeatureScreen_h
#define FeatureScreen_h
#if defined(WIRING) && WIRING >= 100
#include <Wiring.h>
#elif defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "IMenuFeature.h"
#include "FeatureScreenPage.h"
class FeatureScreen : public IMenuFeature
{
public:
	FeatureScreen(const char *title, int current_level)
	{
		this->current_level = current_level; //set default to 1
		strncpy(this->title, title, 20);
	}
	void down() override
	{
		current_page += 1;
		if (current_page >= this->getMenuFeatureItemCount())
		{
			current_page = 0;
		}
	}

	IMenuFeature *ok() override
	{
		((this->menuFeatureItemList[current_page].menu_item_instance))->executeHookOkBtnFunc();

		return this;
	}

	void executeHookInputFunc() override
	{
		((this->menuFeatureItemList[current_page].menu_item_instance))->executeHookInputFunc();
	}
	void executeHookBeforeRenderFunc() override
	{
		((this->menuFeatureItemList[current_page].menu_item_instance))->executeHookBeforeRenderFunc();
	}

	void executeHookAfterRenderFunc() override
	{
		((this->menuFeatureItemList[current_page].menu_item_instance))->executeHookAfterRenderFunc();
	}

	void render(LiquidCrystal_I2C *lcd) override
	{
		//render hook
		/*if(this->hookRenderFunc != nullptr)
		{
			this->hookRenderFunc();
		}*/
		Serial.println("FeatureScreen render()");

		lcd->print(this->menuFeatureItemList[current_page].menu_item_title);
		//lcd->setCursor(0, 1);
		((this->menuFeatureItemList[current_page].menu_item_instance))->render(lcd);
	}

private:
	int current_page = 0;
};
#endif