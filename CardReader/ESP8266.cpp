#include "ESP8266.h"



ESP8266::ESP8266(uint8_t RX, uint8_t TX) {
	this->wifi = new SoftwareSerial(RX, TX);
}

ESP8266::~ESP8266() {
	// TODO Auto-generated destructor stub
}

void ESP8266::init(Print *ser, LCD *lcd) {
	this->debug = ser;
	this->lcd = lcd;
	wifi->begin(9600);
}

void ESP8266::connect() {
	lcd->log("wifi connecting");
rst: //sendcmd("AT+RST", 200);
	sendcmd("AT", 200);
	sendcmd("AT+CWMODE=1", 200);
	if (sendcmd("AT+CWJAP=\"" + ESP8266_SSID + "\",\"" + ESP8266_PASS + "\"", 5000)
		== 3) {
		lcd->log("wifi conn failed");
		goto rst;
	};
	sendcmd("AT+CIPMODE=1", 200);
	lcd->print(httpRequest());
	lcd->log("wifi connected");
	debug->println("wifi connected");
}

int ESP8266::sendcmd(String cmd, int wtime) {
	int retimes = 5;
	bool resend = false;
	int watimes = 5;
	String s = "";
	debug->print("exec: ");
	debug->println(cmd);
	wifi->println(cmd);
	while (1) {
		if (retimes < 1) {
			return 1;
		}
		delay(wtime);
		while (!wifi->available()) {
			if (retimes < 1) {
				retimes = 5;
				resend = true;
			}
			delay(1000);
			watimes--;
		}
		while (wifi->available()) {
			s += (char)wifi->read();
		}
		s.trim();
		if (s.length() == 0 or s == cmd) {
			continue;
		}
		debug->print("recv: ");
		debug->println(s);
		if (s.indexOf("ready") > -1 or s.indexOf("www.ai-thinker.com") > -1) {
			debug->println("wating ready");
			if (cmd.indexOf("RST") < 0) {
				resend = true;
			}
			delay(2000);
		}
		if (s.indexOf("FAIL") > -1) {
			debug->println("FAIL");
			return 2;
		}
		if (s.indexOf("no ip") > -1) {
			debug->println("no ip");
			return 2;
		}
		if (s.indexOf("ERROR") > -1) {
			debug->println("ERROR");
			return 3;
		}
		if (s.indexOf("busy") > -1) {
			debug->println("busy");
			return 3;
		}
		if (s.indexOf("OK") > -1) {
			debug->println("OK");
			return 0;
		}
		if (cmd.indexOf("MODE") > -1 & s.indexOf("no change") > -1) {
			debug->println("no change");
			return 0;
		}
		if (cmd.indexOf("CIPSEND") > -1 & s.indexOf(">") > -1) {
			debug->println(">");
			return 0;
		}
		if (resend) {
			resend = false;
			retimes--;

			debug->println(cmd);
			wifi->println(cmd);
		}
	}
}

String ESP8266::httpRequest() {
	String s = "";
	unsigned long t;
	while (sendcmd("AT+CIPSTART=\"TCP\",\"" + ESP8266_IP + "\",80", 3000) == 3) {
		sendcmd("AT+CIFSR", 200);
		delay(500);
	}
	if (sendcmd("AT+CIPSEND", 500) == 3) {
		connect();
	}
	delay(500);
	debug->println("GET " + ESP8266_URL + " HTTP/1.0");
	wifi->println("GET " + ESP8266_URL + " HTTP/1.0\r\n\r\n\r\n");
	t = millis();
	s = "";
	while (millis() - t < 5000) {
		while (wifi->available()) {
			s += (char)wifi->read();
		}
	}

	if (s.indexOf("ERROR") > -1) {
		debug->println("GET ERROR");
		connect();
	}

	s = s.substring(s.indexOf("\r\n\r\n") + 4);
	//s=s.substring(s.indexOf("\r\n\r\n")+4);

	debug->println(s);
	return s;
	//delay(5000);
}