#pragma once
#include "Arduino.h"
#include "LiquidCrystal.h"
class LCD
{
public:
private:
	uint8_t led;
	LiquidCrystal *lcd;
public:
	LCD(uint8_t rs, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t led);
	virtual ~LCD();
	void LCD::init();
	void LCD::print(String m);
	void LCD::log(String m);
	void LCD::clear();
};

