
/*lcd01.c*/
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define I2C_ADDR 0x3f
#define LCD_CHR  1
#define LCD_CMD  0
#define LINE1    0x80
#define LINE2    0xC0
#define LCD_BACKLIGHT  0x08
#define ENABLE   0x04

void lcd_init(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);

void typeInt(int i);
void typeFloat(float myFloat);
void lcdLoc(int line);
void lcdClear(void);
void typeln(const char* s);
void typeChar(char val);
int xio;
int main()
{
	printf("Raspberry Pi LCD test program\n");
	wiringPiSetupGpio();
	xio = wiringPiI2CSetup(I2C_ADDR);
	lcd_init();

	char str1[] = "Hello World";
	char str2[] = "LCD TEST";
	while(1){
		lcdClear();
		lcdLoc(LINE1);
		typeln("I2C Program");
		lcdLoc(LINE2);
		typeln("in C not Python");
		delay(2000);

		lcdClear();
		lcdLoc(LINE1);
		typeln(str1);
		lcdLoc(LINE2);
		typeln(str2);
		delay(2000);
	}

	return 0;
}
/*주어진 부동 소수점 수(float)를 문자열로 변환하여 LCD에 출력
sprintf 함수를 사용 부동 소수점 값을 문자열로 변환*/
void typeFloat(float myFloat)
{
	char buffer[20];
	sprintf(buffer, "%4.2f", myFloat);
	typeln(buffer);
}
/*정수를 문자열로 변환하여 LCD에 출력
sprintf 함수를 사용하여 정수 값을 문자열로 변환*/
void typeInt(int i)
{
	char array[20];
	sprintf(array, "%d", i);
	typeln(array);
}
/*LCD 화면을 지우는 함수*/
void lcdClear(void)
{
	lcd_byte(0x01, LCD_CMD);
	lcd_byte(0x02, LCD_CMD);
}
/*LCD 화면의 특정 라인으로 커서를 이동시키는 함수*/	
void lcdLoc(int line)
{
	lcd_byte(line, LCD_CMD);
}
/*주어진 문자(char)를 LCD에 출력하는 함수*/
void typeChar(char val)
{
	lcd_byte(val, LCD_CHR);
}
/*주어진 문자열을 LCD에 출력하는 함수*/
void typeln(const char *s)
{
	while(*s) lcd_byte(*(s++), LCD_CHR);
}
/*LCD에 명령을 보내는 함수
bits와 mode를 조합하여 LCD에 데이터를 전송*/
void lcd_byte(int bits, int mode)
{
	int bits_high;
	int bits_low;
	bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT;
	bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT;

	wiringPiI2CReadReg8(xio, bits_high);
	lcd_toggle_enable(bits_high);

	wiringPiI2CReadReg8(xio, bits_low);
	lcd_toggle_enable(bits_low);
}
/*LCD Enable 핀을 토글하는 함수*/
void lcd_toggle_enable(int bits)
{
	delayMicroseconds(500);
	wiringPiI2CReadReg8(xio, (bits | ENABLE));
	delayMicroseconds(500);
	wiringPiI2CReadReg8(xio, (bits& ~ENABLE));
	delayMicroseconds(500);
}
/*LCD 초기화를 위한 함수*/
void lcd_init()
{
	lcd_byte(0x33, LCD_CMD);
	lcd_byte(0x32, LCD_CMD);
	lcd_byte(0x06, LCD_CMD);
	lcd_byte(0x0C, LCD_CMD);
	lcd_byte(0x28, LCD_CMD);
	lcd_byte(0x01, LCD_CMD);
	delayMicroseconds(500);
}
/*
make유틸리티
c소스파일과 헤더파일 분리
c = 정의, h = 선언, main( )

gcc -c source_file.c(c파일 모두 gcc)
gcc -o source_file.o(o파일 모두 gcc)
라이브러리 링크(해당 파일이 필요하면)

makefile 생성
lcd : lcdmain.o lcd1602.o
   gcc -o lcd lcdmain.o lcd1602.o -lwiringPi

lcdmain.o : lcdmain.c lcd1602.h
   gcc -c lcdmain.c

lcd1602.o : lcd1602.c lcd1602.h
   gcc -c lcd1602.c
make 업데이트 후 
./동작실행
*/