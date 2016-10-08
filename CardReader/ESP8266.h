#pragma once
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "LCD.h"
class ESP8266
{
private:
	String ESP8266_SSID = "TP-LINK_8E70";
	String ESP8266_PASS = "974476272";
	String ESP8266_IP = "192.168.1.139";
	String ESP8266_URL = "http://" + ESP8266_IP + "/";

	Print *debug;
	LCD *lcd;
	SoftwareSerial *wifi;
public:
	ESP8266(uint8_t RX, uint8_t TX);
	virtual ~ESP8266();
	void init(Print *ser, LCD *lcd);
	void connect();
	int connectwifi(String ssid, String key);
	int reset();
	int createtcp(String ip, int port);
	int sendcmd(String cmd, int wtime);
	String httpRequest();
};

