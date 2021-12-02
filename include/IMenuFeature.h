#ifndef IMenuFeature_h
#define IMenuFeature_h

#if defined(WIRING) && WIRING >= 100
#include <Wiring.h>
#elif defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <LiquidCrystal_I2C.h>
#define MAX_RO
class IMenuFeature
{
public:
	virtual ~IMenuFeature() = default;

	void setTitle(char *title)
	{
		strncpy(this->title, title, 20);
	}

	virtual void home()
	{
		this->executeHookHomeBtnFunc();
	};
	virtual void down()
	{
		this->executeHookDownBtnFunc();
	};
	virtual IMenuFeature *ok()
	{
		this->executeHookOkBtnFunc();
		return this;
	};

	IMenuFeature *addMenuItem(const char *title, IMenuFeature *menu_item)
	{
		menuFeatureItemList = (MenuFeatureItem *)realloc(menuFeatureItemList, (menu_feature_item_count + 1) * sizeof(MenuFeatureItem));
		strncpy(menuFeatureItemList[menu_feature_item_count].menu_item_title, title, 18);
		menuFeatureItemList[menu_feature_item_count].menu_item_instance = menu_item;
		menu_feature_item_count += 1;
		return this;
	}

	IMenuFeature *addFeaturePage(const char *title, IMenuFeature *menu_item)
	{
		menuFeatureItemList = (MenuFeatureItem *)realloc(menuFeatureItemList, (menu_feature_item_count + 1) * sizeof(MenuFeatureItem));
		strncpy(menuFeatureItemList[menu_feature_item_count].menu_item_title, title, 18);
		menuFeatureItemList[menu_feature_item_count].menu_item_instance = menu_item;
		menu_feature_item_count += 1;
		return this;
	}

	virtual void render(LiquidCrystal_I2C *lcd) = 0;

	int getLevel()
	{
		return this->current_level;
	}
	char *getTitle()
	{
		return this->title;
	}
	int getMenuFeatureItemCount()
	{
		return menu_feature_item_count;
	}

	//execute licyle  hook
	virtual void executeHookInputFunc()
	{
		if (hookInputFunc != nullptr)
		{
			hookInputFunc();
		}
	}
	virtual void executeHookBeforeRenderFunc()
	{
		if (hookBeforeRenderFunc != nullptr)
		{
			hookBeforeRenderFunc();
		}
	}
	virtual void executeHookRenderFunc()
	{
		if (hookRenderFunc != nullptr)
		{
			hookRenderFunc();
		}
	}
	virtual void executeHookAfterRenderFunc()
	{
		if (hookAfterRenderFunc != nullptr)
		{
			hookAfterRenderFunc();
		}
	}
	virtual void hookDefaultFunc()
	{
		//donothing
	}
	virtual void executeHookHomeBtnFunc()
	{

		(hookHomeBtnFunc != nullptr) ? hookHomeBtnFunc() : hookDefaultFunc();
	}
	virtual void executeHookOkBtnFunc()
	{
		(hookOkBtnFunc != nullptr) ? hookOkBtnFunc() : hookDefaultFunc();
	}

	virtual void executeHookDownBtnFunc()
	{

		(hookDownBtnFunc != nullptr) ? hookHomeBtnFunc() : hookDefaultFunc();
	}
	//end execute licyle  hook
	// set licyle hook
	IMenuFeature *setHookInputFunc(void (*function)())
	{
		hookInputFunc = function;
		return this;
	}

	IMenuFeature *setHookBeforeRenderFunc(void (*function)())
	{
		hookBeforeRenderFunc = function;
		return this;
	}
	IMenuFeature *setHookRender(void (*function)())
	{
		hookRenderFunc = function;
		return this;
	}
	IMenuFeature *setHookAfterRenderFunc(void (*function)())
	{
		hookAfterRenderFunc = function;
		return this;
	}

	IMenuFeature *setHookHomeBtnFunc(void (*function)())
	{
		hookHomeBtnFunc = function;
		return this;
	}

	IMenuFeature *setHookDownBtnFunc(void (*function)())
	{
		hookDownBtnFunc = function;
		return this;
	}

	IMenuFeature *setHookOkBtnFunc(void (*function)())
	{
		hookOkBtnFunc = function;
		return this;
	}

	// end set licyle hook

protected:
	uint8_t current_level = 0; //init level
	LiquidCrystal_I2C *_lcd;
	char title[20];
	bool is_menu;
	void (*hookInputFunc)() = nullptr;
	void (*hookBeforeRenderFunc)() = nullptr;
	void (*hookRenderFunc)() = nullptr;
	void (*hookAfterRenderFunc)() = nullptr;

	void (*hookHomeBtnFunc)() = nullptr;
	void (*hookDownBtnFunc)() = nullptr;
	void (*hookOkBtnFunc)() = nullptr;
	struct MenuFeatureItem
	{
		char menu_item_title[18];
		IMenuFeature *menu_item_instance;
	};
	int menu_feature_item_count = 0;
	MenuFeatureItem *menuFeatureItemList = nullptr;
};
#endif