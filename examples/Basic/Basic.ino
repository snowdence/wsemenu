#include <Arduino.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "WSEMenu.h"
#include "MenuScreen.h"
#include "FeatureScreen.h"
#include "FeatureScreenPage.h"

int pin_home = 10;
int pin_updown = 11;
int pin_select = 12;

int current_state_pin_home = HIGH;
int current_state_pin_updown = HIGH;
int current_state_pin_select = HIGH;

int prev_state_pin_home = HIGH;
int prev_state_pin_updown = HIGH;
int prev_state_pin_select = HIGH;

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
WSEMenu wsem(&lcd);

void initMenu();
void setup()
{

  Serial.begin(9600);

  // put your setup code here, to run once:
  lcd.init(); // initialize the lcd
  lcd.backlight();

  initMenu();

  pinMode(pin_home, INPUT_PULLUP);
  pinMode(pin_updown, INPUT_PULLUP);
  pinMode(pin_select, INPUT_PULLUP);
}

void print_cam_bien_1()
{
  lcd.setCursor(0, 1);
  lcd.print("Do am dat la 30");
}
void print_cam_bien_2()
{
  lcd.setCursor(0, 1);
  lcd.print("Nhiet do la 50");
}

void inputFunc()
{
  Serial.println("Read Input func");
}
void afterRenderFunc()
{
  Serial.println("sau khi render");
}
void initMenu()
{
  IMenuFeature *builder;

  MenuScreen menu_level_1 = MenuScreen("ROOT MENU", 1);

  //level2
  builder = &menu_level_1;

  builder
      ->addMenuItem("Cam bien",
                    (new FeatureScreen("Cam bien", 2))
                        ->addMenuItem("Cam1",
                                      (new FeatureScreenPage(&print_cam_bien_1))
                                          ->setHookInputFunc(&inputFunc)
                                          ->setHookAfterRenderFunc(&afterRenderFunc))
                        ->addMenuItem("Cam2", new FeatureScreenPage(&print_cam_bien_2)))
      ->addMenuItem("Cai dat",
                    (new MenuScreen("Cai dat", 2))
                        ->addMenuItem("CD thong so",
                                      (new MenuScreen("CD thong so", 3))
                                          ->addMenuItem("Sub 1", nullptr)
                                          ->addMenuItem("Sub 2", nullptr))
                        ->addMenuItem("CD do am", nullptr)
                        ->addMenuItem("CD nhiet do", nullptr))
      ->addMenuItem("Dieu khien",
                    (new MenuScreen("Dieu khien", 2))
                        ->addMenuItem("DK Quat", nullptr)
                        ->addMenuItem("DK bom", nullptr)
                        ->addMenuItem("DK nuoc", nullptr))
      ->addMenuItem("VIP",
                    (new MenuScreen("VIP", 2))
                        ->addMenuItem("DK Quat", nullptr)
                        ->addMenuItem("DK bom", nullptr)
                        ->addMenuItem("DK nuoc", nullptr));

  wsem.addRoot(&menu_level_1);
}

int read_state_pin(int pin)
{
  int val = digitalRead(pin);
  return val;
}
void loop()
{
  // put your main code here, to run repeatedly:
  //wsem.hookInput();
  //wsem.render(&lcd);
  current_state_pin_home = digitalRead(pin_home);
  current_state_pin_select = digitalRead(pin_select);
  current_state_pin_updown = digitalRead(pin_updown);

  wsem.executeDefaultLicyleHook(&lcd);

  if (current_state_pin_home == LOW && current_state_pin_home != prev_state_pin_home)
  {
    wsem.home();
  }

  if (current_state_pin_select == LOW && current_state_pin_select != prev_state_pin_select)
  {
    wsem.submit();
  }

  if (current_state_pin_updown == LOW && current_state_pin_updown != prev_state_pin_updown)
  {
    wsem.down();
  }

  prev_state_pin_home = current_state_pin_home;
  prev_state_pin_select = current_state_pin_select;
  prev_state_pin_updown = current_state_pin_updown;
  delay(50);
}
