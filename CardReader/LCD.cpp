#include "LCD.h"



LCD::LCD(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2,
	uint8_t d3, uint8_t led) {
	// TODO Auto-generated constructor stub
	this->lcd = new LiquidCrystal(rs, enable, d0, d1, d2, d3);
	pinMode(led, OUTPUT);
	this->led = led;
}

LCD::~LCD() {
	// TODO Auto-generated destructor stub
}

void LCD::init() {
	char* a = new char[11]{ 202, 219, 176, 44, 220, 176, 217, 196, 222, 33, 0 };
	digitalWrite(led, HIGH);
	// set up the LCD's number of columns and rows:
	lcd->begin(16, 2);
	lcd->setCursor(0, 0);
	lcd->print(a);
	lcd->setCursor(0, 1);
	lcd->print(a);
}

void LCD::print(String m) {
	while (m.length() < 16) {
		m += " ";

	}
	lcd->setCursor(0, 1);
	lcd->print(m);
}

void LCD::log(String m) {
	while (m.length() < 16) {
		m += " ";

	}
	lcd->setCursor(0, 0);
	lcd->print(m);
}

void LCD::clear() {
	lcd->clear();
}