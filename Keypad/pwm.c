/*PWM(Software Pulse Width Modulation)을 사용하여 LED를 조절*/

/*pwm.c*/
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <wiringPiI2C.h>

#define C4  6
#define C3  13
#define C2  19
#define C1  26
#define R1  12
#define R2  16
#define R3  20
#define R4  21

const int pinLed = 5;

int main()
{
	wiringPiSetupGpio();
	softPwmCreate(pinLed, 0, 200);
	pinMode(C4, INPUT);
	pinMode(C3, INPUT);
	pinMode(C2, INPUT);
	pinMode(C1, INPUT);
	pinMode(R1, OUTPUT);
	pinMode(R2, OUTPUT);
	pinMode(R3, OUTPUT);
	pinMode(R4, OUTPUT);

	pullUpDnControl(C4, PUD_UP);
	pullUpDnControl(C3, PUD_UP);
	pullUpDnControl(C2, PUD_UP);
	pullUpDnControl(C1, PUD_UP);

	digitalWrite(R1, HIGH);
	digitalWrite(R2, HIGH);
	digitalWrite(R3, HIGH);
	digitalWrite(R4, HIGH);

	printf("Enter the keypad\n");

	while(1){
		digitalWrite(R1, LOW);
		if(digitalRead(C1) == LOW){
			printf("1 pressed\n");
			for(int i = 0; i < 50; i++){
				softPwmWrite(pinLed, i);
				delay(100);
			}
		}
		digitalWrite(R2, LOW);
		if(digitalRead(C2) == LOW){
			printf("2 pressed\n");
			for(int i = 0; 0 < i < 100; i++){
				softPwmWrite(pinLed, i);
				delay(100);
			}
		}
		digitalWrite(R3, LOW);
		if(digitalRead(C3) == LOW){
			printf("3 pressed\n");
			for(int i = 0; 0 < i < 200; i++){
				softPwmWrite(pinLed, i);
				delay(100);
			}
		}
		delay(100);
	}
	return 0;
}