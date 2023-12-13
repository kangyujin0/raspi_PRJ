/*LCD구구단출력*/
/*lcdmain.c*/

#include "lcd1602.h"
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

int xio;
int main()
{
	printf("Raspberry Pi LCD test program\n");
	wiringPiSetupGpio();
	xio = wiringPiI2CSetup(I2C_ADDR);
	lcd_init();

	char str[20];
	while(1){
		for(int i = 2; i <= 9; i++){
			lcdLoc(LINE1);
			sprintf(str, "%dMultiplication", i);
			typeln(str);
			lcdLoc(LINE2);

			for(int j= 1; j <= 9; j++){
				sprintf(str, "%d x %d = %d\n", i, j, i*j);
				typeln(str);
				delay(1000);
				if(j < 9){
					lcdLoc(LINE2);
				}
			}
			delay(1000);
		}
	}
	return 0;
}
