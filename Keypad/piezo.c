/*피에조 부저(Piezo Buzzer)를 제어*/

/*piezo.c*/
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <softTone.h>

#define C4  6
#define C3  13
#define C2  19
#define C1  26
#define R1  12
#define R2  16
#define R3  20
#define R4  21

const int pinPiezo = 18;
const int melody[] = {131, 147, 165, 175, 196, 220, 247, 262};

int main()
{
	wiringPiSetupGpio();
	softToneCreate(pinPiezo);
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

	printf("Enter the piano\n");

	while(1){

		for(int i = 0; i < 8; i++){
			digitalWrite(R1, LOW);
			if(digitalRead(C1) == LOW){
				printf("도pressed\n");
			softToneWrite(pinPiezo, melody[0]);
			delay(1000);
			}
			digitalWrite(R1, LOW);
			if(digitalRead(C2) == LOW){
				printf("레pressed\n");
			softToneWrite(pinPiezo, melody[1]);
			delay(1000);
			}
			digitalWrite(R1, LOW);
			if(digitalRead(C3) == LOW){
				printf("미pressed\n");
			softToneWrite(pinPiezo, melody[2]);
			delay(1000);
			}
			digitalWrite(R1, LOW);
			if(digitalRead(C4) == LOW){
				printf("파pressed\n");
			softToneWrite(pinPiezo, melody[3]);
			delay(1000);
			}
			digitalWrite(R2, LOW);
			if(digitalRead(C1) == LOW){
				printf("솔pressed\n");
			softToneWrite(pinPiezo, melody[4]);
			delay(1000);
			}
			digitalWrite(R2, LOW);
			if(digitalRead(C2) == LOW){
				printf("라pressed\n");
			softToneWrite(pinPiezo, melody[5]);
			delay(1000);
			}
			digitalWrite(R2, LOW);
			if(digitalRead(C3) == LOW){
				printf("시pressed\n");
			softToneWrite(pinPiezo, melody[6]);
			delay(1000);
			}
			digitalWrite(R2, LOW);
			if(digitalRead(C4) == LOW){
				printf("도pressed\n");
			softToneWrite(pinPiezo, melody[7]);
			delay(1000);
			}
		}
		softToneWrite(pinPiezo, 0);
		delay(100);
	}
	return 0;
}