# Arduino_CardReader

学生会签到的读卡器
328p+rc522+esp8266+php+mysql
http://cqrkjsj.applinzi.com

******************
v0.0
引脚连接图：

					-	-	-	-	-			
	ESP8266	RX	-	|	TX	A	RAW	|	-		
	ESP8267	TX	-	|	RX	R	GND	|	-		
				-	|	RST	D	RST	|	-		
				-	|	GDN	U	VCC	|	-		
		BEEPER	-	|	2	I	A3	|	-		
		LCD	LED	-	|	3	N	A2	|	-		
		LCD	RS	-	|	4	O	A1	|	-		
		LCD	E	-	|	5	 	A0	|	-			
		LCD	D4	-	|	6	3	13	|	-	SCK		RC522
		LCD	D5	-	|	7	2	12	|	-	MISO	RC523
		LCD	D6	-	|	8	8	11	|	-	MOSI	RC524
		LCD	D7	-	|	9	P	10	|	-	SDA		RC525
					-	-	-	-	-			
arduino 328p + rc522 + esp8266
然而并不好用。。。

******************
v0.1
引脚连接图：

					-	-	-	-	-			
				-	|	TX	A	RAW	|	-		
				-	|	RX	R	GND	|	-		
				-	|	RST	D	RST	|	-		
				-	|	GDN	U	VCC	|	-		
	ESP8266	RX	-	|	2	I	A3	|	-		
	ESP8267	TX	-	|	3	N	A2	|	-		
		LCD	RS	-	|	4	O	A1	|	-	BEEPER	
		LCD	E	-	|	5	 	A0	|	-	LED		LCD
		LCD	D4	-	|	6	3	13	|	-	SCK		RC522
		LCD	D5	-	|	7	2	12	|	-	MISO	RC523
		LCD	D6	-	|	8	8	11	|	-	MOSI	RC524
		LCD	D7	-	|	9	P	10	|	-	SDA		RC525
					-	-	-	-	-			
RC522工作时竟然会影响到ESP8266的WiFi连接认证，所以必须要在初始化RC522之前，先让ESP8266连接上wifi。

******************
v0.2
引脚连接图：

					-	-	-	-	-			
				-	|	TX	A	RAW	|	-		
				-	|	RX	R	GND	|	-		
				-	|	RST	D	RST	|	-		
				-	|	GDN	U	VCC	|	-		
	ESP8266	RX	-	|	2	I	A3	|	-	POWER	AMS1117	
	ESP8267	TX	-	|	3	N	A2	|	-	RST		RC522	
		LCD	RS	-	|	4	O	A1	|	-	BEEPER	BEEPER
		LCD	E	-	|	5	 	A0	|	-	LED		LCD
		LCD	D4	-	|	6	3	13	|	-	SCK		RC522
		LCD	D5	-	|	7	2	12	|	-	MISO	RC523
		LCD	D6	-	|	8	8	11	|	-	MOSI	RC524
		LCD	D7	-	|	9	P	10	|	-	SDA		RC525
					-	-	-	-	-			
说明：在之前的版本中使用的是AMS1117-3.3作为ESP8266和RC522的供电。

为了解决RC522和ESP8266互相影响的情况，和ESP8266偶尔出现的卡死(软重启AT+RST无效)，在电源和AMS1117之间增加了一个S9013来控制供电，同时连接了RC522的RST引脚，A2输出HIGH时RC522工作。

此时可以通过A3引脚来控制ESP8266和RC522的供电，输出HIGH通电，LOW断电。
