#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>

#define BASE 100
#define SPI_CHAN 0
#define SW 25
#define X 0		// pin번호
#define Y 3
#define LEFT 100		// 좌로 이동 기준값
#define RIGHT 900		// 우로 이동 기준값

int main()
{
	wiringPiSetup();	// wPi번호
	printf("Raspberry Pi SPI ADC Program\n");
	mcp3004Setup(BASE, SPI_CHAN);
	pinMode(SW, INPUT);
	pinMode(X, INPUT);
	pullUpDnControl(SW, PUD_UP);

	int x = 0;
	while(1){

		int x_val = analogRead(BASE + X);	// 조건문에서 변경된 x 값 
		int y = analogRead(BASE + Y);
		printf("X Value: %4d\n", x_val);
		printf("Y Value: %4d\n", y);

		if(x_val < LEFT){			// joystick 제어
			printf("Left\n");
			x--;
		}else if(x_val > RIGHT){
			printf("Right\n");
			x++;
		}else{
			printf("Center\n");
		}

		if(digitalRead(SW) == LOW){		// switch 누르면 x = 0 설정
			printf("switch on\n");
			x = 0;
		}

		printf("X value: %d\n", x);
		delay(300);

		printf("\n");
	}
	return 0;
}
