/*4자리수 표현*/
/*pnd.v2.c*/
#include <stdio.h>
#include <wiringPi.h>

#define LED1 21	// A 11
#define LED2 16	// B 7
#define LED3 23	// C 4
#define LED4 25	// D 2
#define LED5 12	// E 1
#define LED6 20	// F 10
#define LED7 18	// G 5
#define LED8 24	// DP 3
#define DIG1 19
#define DIG2 13
#define DIG3 6
#define DIG4 5

int main()
{
	wiringPiSetupGpio();
	int pin[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};
	int digPin[] = {DIG1, DIG2, DIG3, DIG4};
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(LED4, OUTPUT);
	pinMode(LED5, OUTPUT);
	pinMode(LED6, OUTPUT);
	pinMode(LED7, OUTPUT);
	pinMode(LED8, OUTPUT);
	pinMode(DIG1, OUTPUT);
	pinMode(DIG2, OUTPUT);
	pinMode(DIG3, OUTPUT);
	pinMode(DIG4, OUTPUT);

	for(int i = 0; i < 4; i++){		// FND All off
		digitalWrite(digPin[i], HIGH);
	}

	for(int i = 0; i < 8; i++){		// FND All off
		digitalWrite(pin[i], HIGH);
	}

	while(1){

		digitalWrite(DIG1, HIGH);
		digitalWrite(DIG2, LOW);
		digitalWrite(DIG3, LOW);
		digitalWrite(DIG4, LOW);
		digitalWrite(LED2, LOW);
		digitalWrite(LED3, LOW);
		printf("1\n");
		delay(1);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(DIG1, LOW);
		digitalWrite(DIG2, HIGH);
		digitalWrite(DIG3, LOW);
		digitalWrite(DIG4, LOW);
		digitalWrite(LED1, LOW);
		digitalWrite(LED2, LOW);
		digitalWrite(LED4, LOW);
		digitalWrite(LED5, LOW);
		digitalWrite(LED7, LOW);
		printf("2\n");
		delay(1);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(DIG1, LOW);
		digitalWrite(DIG2, LOW);
		digitalWrite(DIG3, HIGH);
		digitalWrite(DIG4, LOW);
		digitalWrite(LED1, LOW);
		digitalWrite(LED2, LOW);
		digitalWrite(LED3, LOW);
		digitalWrite(LED4, LOW);
		digitalWrite(LED7, LOW);
		printf("3\n");
		delay(1);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(DIG1, LOW);
		digitalWrite(DIG2, LOW);
		digitalWrite(DIG3, LOW);
		digitalWrite(DIG4, HIGH);
		digitalWrite(LED2, LOW);
		digitalWrite(LED3, LOW);
		digitalWrite(LED6, LOW);
		digitalWrite(LED7, LOW);
		printf("4\n");
		delay(1);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

	}
	return 0;
}
