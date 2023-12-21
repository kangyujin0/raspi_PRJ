/*mcp3008와 조이스틱 연결*/
/*joy.v1.c*/
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>

#define BASE 100
#define SPI_CHAN 0
#define SW 25
int main()
{
	wiringPiSetup();	// wPi번호
	printf("Raspberry Pi SPI ADC Program\n");
	mcp3004Setup(BASE, SPI_CHAN);
	pinMode(SW, INPUT);
	pullUpDnControl(SW, PUD_UP);
	int joystickSW = 1;
	while(1){

		if(digitalRead(SW) == 0){
			printf("ok\t");
		}else{
			printf("no\t");
		}
		printf("jpystickSW:%d\n", joystickSW);

		for(int i = 0; i < 2; i++){
			printf("channel%d value:%4d\t", i, (analogRead(BASE + i)));
			delay(200);
		}
		printf("\n");
	}
	return 0;
}
