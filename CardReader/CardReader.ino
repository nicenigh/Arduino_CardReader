#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include "Arduino.h"
#include "ESP8266.h"
#include "RC522.h"
#include "LCD.h"

LCD lcd(4, 5, 6, 7, 8, 9, A0);

RC522 rfid(10, A2);

ESP8266 wifi(2, 3);

int beeper = A1;
int rc552 = A2;
int power = A3;

String serNum = "0000000000";
unsigned long ts = 0;
unsigned long lastRT = 0;

void setup()
{

  /* add setup code here */
	Serial.begin(9600);
	pinMode(beeper, OUTPUT);
	pinMode(power, OUTPUT);
	digitalWrite(power, HIGH);
	lcd.init();
	wifi.init(&Serial, &lcd);
	wifi.connect();
	rfid.init();
}

void loop()
{

  /* add main program code here */
	if (millis() - ts > 2000) {
		Serial.println("read card");
		String tNum = rfid.read();
		if (tNum != "") { // and (tNum != serNum xor millis() - lastRT > 5000)
			lcd.clear();
			serNum = tNum;
			lcd.log(serNum);
			Serial.println(serNum);
			beep();

			lastRT = millis();
		}
		wifi.connect();
		ts = millis();
		lcd.print(wifi.httpRequest());
	}
}

void beep() {
	digitalWrite(beeper, LOW);
	digitalWrite(beeper, HIGH);
	delay(100);
	digitalWrite(beeper, LOW);
	delay(100);
	digitalWrite(beeper, HIGH);
	delay(100);
	digitalWrite(beeper, LOW);
}