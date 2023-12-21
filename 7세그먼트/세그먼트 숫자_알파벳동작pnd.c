세그먼트 숫자/알파벳 동작
/*pnd.v1.c*/
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
int main()
{
	wiringPiSetupGpio();
	int i = 0;
	int pin[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(LED4, OUTPUT);
	pinMode(LED5, OUTPUT);
	pinMode(LED6, OUTPUT);
	pinMode(LED7, OUTPUT);
	pinMode(LED8, OUTPUT);

	// FND All off
	for(int i = 0; i < 8; i++){
		digitalWrite(pin[i], HIGH);
	}

	while(1){

		digitalWrite(LED1, LOW);
		digitalWrite(LED2, LOW);
		digitalWrite(LED3, LOW);
		digitalWrite(LED4, LOW);
		digitalWrite(LED5, LOW);
		digitalWrite(LED6, LOW);
		printf("0\n");
		delay(1000);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(LED2, LOW);
		digitalWrite(LED3, LOW);
		printf("1\n");
		delay(1000);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(LED1, LOW);
		digitalWrite(LED2, LOW);
		digitalWrite(LED4, LOW);
		digitalWrite(LED5, LOW);
		digitalWrite(LED7, LOW);
		printf("2\n");
		delay(1000);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(LED1, LOW);
		digitalWrite(LED2, LOW);
		digitalWrite(LED3, LOW);
		digitalWrite(LED4, LOW);
		digitalWrite(LED7, LOW);
		printf("3\n");
		delay(1000);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(LED2, LOW);
		digitalWrite(LED3, LOW);
		digitalWrite(LED6, LOW);
		digitalWrite(LED7, LOW);
		printf("4\n");
		delay(1000);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(LED1, LOW);
		digitalWrite(LED3, LOW);
		digitalWrite(LED4, LOW);
		digitalWrite(LED6, LOW);
		digitalWrite(LED7, LOW);
		printf("5\n");
		delay(1000);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(LED1, LOW);
		digitalWrite(LED3, LOW);
		digitalWrite(LED4, LOW);
		digitalWrite(LED5, LOW);
		digitalWrite(LED6, LOW);
		digitalWrite(LED7, LOW);
		printf("6\n");
		delay(1000);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(LED1, LOW);
		digitalWrite(LED2, LOW);
		digitalWrite(LED3, LOW);
		printf("7\n");
		delay(1000);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(LED1, LOW);
		digitalWrite(LED2, LOW);
		digitalWrite(LED3, LOW);
		digitalWrite(LED4, LOW);
		digitalWrite(LED5, LOW);
		digitalWrite(LED6, LOW);
		digitalWrite(LED7, LOW);
		printf("8\n");
		delay(1000);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(LED1, LOW);
		digitalWrite(LED2, LOW);
		digitalWrite(LED3, LOW);
		digitalWrite(LED4, LOW);
		digitalWrite(LED6, LOW);
		digitalWrite(LED7, LOW);
		printf("9\n");
		delay(1000);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(LED1, LOW);
		digitalWrite(LED2, LOW);
		digitalWrite(LED3, LOW);
		digitalWrite(LED5, LOW);
		digitalWrite(LED6, LOW);
		digitalWrite(LED7, LOW);
		printf("A\n");
		delay(1000);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(LED3, LOW);
		digitalWrite(LED4, LOW);
		digitalWrite(LED5, LOW);
		digitalWrite(LED6, LOW);
		digitalWrite(LED7, LOW);
		printf("B\n");
		delay(1000);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(LED1, LOW);
		digitalWrite(LED4, LOW);
		digitalWrite(LED5, LOW);
		digitalWrite(LED6, LOW);
		printf("C\n");
		delay(1000);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(LED2, LOW);
		digitalWrite(LED3, LOW);
		digitalWrite(LED4, LOW);
		digitalWrite(LED5, LOW);
		digitalWrite(LED7, LOW);
		printf("D\n");
		delay(1000);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(LED1, LOW);
		digitalWrite(LED4, LOW);
		digitalWrite(LED5, LOW);
		digitalWrite(LED6, LOW);
		digitalWrite(LED7, LOW);
		printf("E\n");
		delay(1000);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}

		digitalWrite(LED1, LOW);
		digitalWrite(LED5, LOW);
		digitalWrite(LED6, LOW);
		digitalWrite(LED7, LOW);
		printf("F\n");
		delay(1000);
		for(int i = 0; i < 8; i++){
			digitalWrite(pin[i], HIGH);
		}
	}
	return 0;
}