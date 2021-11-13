#ifndef MenuScreen_h
#define MenuScreen_h

#if defined(WIRING) && WIRING >= 100
#include <Wiring.h>
#elif defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "IMenuFeature.h"

class MenuScreen : public IMenuFeature
{
public:
	MenuScreen(const char *title, int current_level)
	{
		this->current_level = current_level; //set default to

		strncpy(this->title, title, 20);
	}

	void render(LiquidCrystal_I2C *lcd) override
	{
		Serial.println("MenuScreen render()");

		//printf("===============================\n");
		//printf("%s\n", this->title);
		lcd->setCursor(0, 0);
		lcd->print(this->title);
		lcd->print(" ");
		lcd->print(this->current_selection + 1);
		lcd->print("/");
		lcd->print(this->getMenuFeatureItemCount());

		int start_idx = 0;
		int end_idx_page = 0;
		int row_cursor = 1;

		if (current_selection >= max_count_selection)
		{
			start_idx = current_selection - max_count_selection + 1;
		}
		end_idx_page = start_idx + 3 - 1;
		if (end_idx_page > this->getMenuFeatureItemCount() - 1)
		{
			end_idx_page = this->getMenuFeatureItemCount() - 1;
		}
		for (int i = start_idx; i <= end_idx_page; i++)
		{
			lcd->setCursor(2, row_cursor);
			lcd->print(String(i + 1, 10));
			lcd->print(". ");
			lcd->print(this->menuFeatureItemList[i].menu_item_title);
			if (current_selection == i)
			{
				lcd->setCursor(0, row_cursor);
				lcd->print("x");
			}
			row_cursor += 1;
		}
	}

	void down() override
	{
		//down press to next
		current_selection += 1;
		if (current_selection >= this->getMenuFeatureItemCount())
		{
			current_selection = 0;
		}
	}
	IMenuFeature *submit() override
	{
		return this->menuFeatureItemList[current_selection].menu_item_instance;
	}

private:
	int current_selection = 0;
	int max_count_selection = 3;
};
#endif //