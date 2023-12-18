#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <math.h>

#define C4  6
#define C3  13
#define C2  19
#define C1  26
#define R1  12
#define R2  16
#define R3  20
#define R4  21

int main()
{
	wiringPiSetupGpio();
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

	printf("Press the button to output\n");
	int num1 = 0;
	int num2 = 0;
	int numarray[10];
	int i = 0;
	char curOp = 0;
	while(1){

		digitalWrite(R1, LOW);
		if(digitalRead(C1) == LOW){
			printf("1");
			fflush(stdout);
			numarray[i++]=1;
		}
		if(digitalRead(C2) == LOW){
			printf("2");
			fflush(stdout);
			numarray[i++]=2;
		}
		if(digitalRead(C3) == LOW){
			printf("3");
			fflush(stdout);
			numarray[i++]=3;
		}
		if(digitalRead(C4) == LOW){
			printf("+");
			fflush(stdout);
			curOp = '+';
			for(int k = i-1, m = 0; k>=0; k--, m++){
				num1 += numarray[m]*(pow(10, k));
			}
			i = 0;
		}
		digitalWrite(R1, HIGH);
		delay(100);

		/*R2*/
		digitalWrite(R2, LOW);
		if(digitalRead(C1) == LOW){
			printf("4");
			fflush(stdout);
			numarray[i++]=4;
		}
		if(digitalRead(C2) == LOW){
			printf("5");
			fflush(stdout);
			numarray[i++]=5;
		}
		if(digitalRead(C3) == LOW){
			printf("6");
			fflush(stdout);
			numarray[i++]=6;
		}
		if(digitalRead(C4) == LOW){
			printf("-");
			fflush(stdout);
			curOp = '-';
			for(int k = i-1, m=0; k>=0; k--, m++){
				num1 += numarray[m]*(pow(10, k));
			}
			i = 0;
		}

		digitalWrite(R2, HIGH);
		delay(100);

		/*R3*/
		digitalWrite(R3, LOW);
		if(digitalRead(C1) == LOW){
			printf("7");
			fflush(stdout);
			numarray[i++]=7;
		}
		if(digitalRead(C2) == LOW){
			printf("8");
			fflush(stdout);
			numarray[i++]=8;
		}
		if(digitalRead(C3) == LOW){
			printf("9");
			fflush(stdout);
			numarray[i++]=9;
		}
		if(digitalRead(C4) == LOW){
			printf("x");
			fflush(stdout);
			curOp = 'x';
			for(int k = i-1, m=0; k>=0; k--, m++){
				num1 +=numarray[m]*(pow(10, k));
			}
			i = 0;
		}

		digitalWrite(R3, HIGH);
		delay(100);

		/*R4*/
		digitalWrite(R4, LOW);
		if(digitalRead(C1) == LOW){
			printf("=");
			fflush(stdout);
			for(int k = i-1, m = 0; k>=0; k--, m++){
				num2 += numarray[m]*(pow(10, k));
			}
			i=0;

			switch(curOp){
				case '+' : printf(" %d\n", num1+num2); break;
				case '-' : printf(" %d\n", num1-num2); break;
				case 'x' : printf(" %d\n", num1*num2); break;
				case '/' : printf(" %d\n", num1/num2); break;
			}
			num1=0;
			num2=0;
		}
		if(digitalRead(C2) == LOW){
			printf("0");
			fflush(stdout);
			numarray[i++]=0;
		}
		if(digitalRead(C3) == LOW)
			printf("#");
			fflush(stdout);
		if(digitalRead(C4) == LOW){
			printf("/");
			fflush(stdout);
			num1 = numarray[0];
			curOp = '/';
			numarray[0]=0;
			i = 0;
		}

		digitalWrite(R4, HIGH);
		delay(100);
	}
	return 0;
}
