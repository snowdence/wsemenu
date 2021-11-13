#ifndef WSEMenu_h
#define WSEMenu_h

#if defined(WIRING) && WIRING >= 100
#include <Wiring.h>
#elif defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "IMenuFeature.h"
typedef void (*fp)();

class WSEMenu
{
public:
	WSEMenu(LiquidCrystal_I2C *lcd) : needReRender(true)
	{
		this->lcd = lcd;
	}
	void addRoot(IMenuFeature *root)
	{
		this->root = root;
		this->current_item = this->root;
	}
	void hookInput()
	{
		this->current_item->executeHookInputFunc();
		// fp inputFun = (fp)this->current_item->getHookInputFunc();
		// if (inputFun != nullptr)
		// {
		// 	inputFun();
		// }
	}

	void hookBeforeRender()
	{
		this->current_item->executeHookBeforeRenderFunc();
	}
	void hookAfterRender()
	{
		this->current_item->executeHookAfterRenderFunc();
	}

	void down()
	{
		this->current_item->down();
		needReRender = true;
	}
	void home()
	{
		if (this->current_item != root)
		{
			needReRender = true;
		}
		this->current_item = root;
	}
	void submit()
	{

		this->current_item = this->current_item->submit();
		needReRender = true;
	}

	void preRender()
	{
		if (needReRender == true)
		{
			lcd->clear();
			lcd->setCursor(0, 0);
		}
	}
	void render(LiquidCrystal_I2C *lcd)
	{
		this->preRender();
		if (needReRender == true)
		{
			needReRender = false;

			this->current_item->render(lcd);
		}
	}
	void executeDefaultLicyleHook(LiquidCrystal_I2C *lcd)
	{
		this->hookInput();
		this->hookBeforeRender();
		this->render(lcd);
		this->hookAfterRender();
	}

private:
	bool needReRender = false;
	IMenuFeature *root;
	LiquidCrystal_I2C *lcd;
	IMenuFeature *current_item;
};
#endif //