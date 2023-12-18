#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <math.h>
#include <string.h>
#include <termios.h>

#define C4  6
#define C3  13
#define C2  19
#define C1  26
#define R1  12
#define R2  16
#define R3  20
#define R4  21
#define LED 23

char pw[] = {'0', '0', '0', '0', '*'};
char p[10];										// 확인할
char nowpw[6];				// 현재
char newpw[6];				// 변경된
int attempts = 5;				// 제한횟수
int numarray[10];
int i = 0;

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
	pinMode(LED, OUTPUT);
	pullUpDnControl(C4, PUD_UP);
	pullUpDnControl(C3, PUD_UP);
	pullUpDnControl(C2, PUD_UP);
	pullUpDnControl(C1, PUD_UP);

	digitalWrite(R1, HIGH);
	digitalWrite(R2, HIGH);
	digitalWrite(R3, HIGH);
	digitalWrite(R4, HIGH);

	printf("Enter the password\n");

	while(1){

		scanf("%s", p);
		if(strcmp(pw, p) == 0){
			strcpy(nowpw, p);
			printf("Unlock!\n");
			digitalWrite(LED, HIGH);
			delay(2000);
		}else{
			attempts--;
			if(attempts == 0){
				printf("Enable to enter.\n");
				break;
			}else{
				printf("Enter it again:\n");
				for(int i =0; i < 5; i++){
					digitalWrite(LED, HIGH);
					delay(1000);
					digitalWrite(LED, LOW);
					delay(1000);
				}
			}
		}

		if(strcmp(p, "#") == 0){
		printf("Enter current password:\n");
		scanf("%s", p);

		if(strcmp(nowpw, p) == 0){
			for(int j = 0; j < 5; j++){
				nowpw[j] = 0;
			}
			printf("Enter the New password:\n");
			scanf("%s", p);

			if(strlen(p) == 4){
				strcat(p, "*");
				strcpy(newpw, p);
				printf("Password chamged success!\n");
			}else{
				printf("Password is four digits.\n");
			}
		}else{
			printf("Incorrect current password!\n");
		}
		strcpy(pw, newpw);

		/*R1*/
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

		digitalWrite(R3, HIGH);
		delay(100);

		/*R4*/
		if(digitalRead(C3) == LOW){
			printf("*");
			fflush(stdout);
		}
		if(digitalRead(C2) == LOW){
			printf("0");
			fflush(stdout);
			numarray[i++]=0;
		}
		if(digitalRead(C3) == LOW){
			printf("#");
			fflush(stdout);
		}

		digitalWrite(R4, HIGH);
		delay(100);
	}
}
	return 0;
}
