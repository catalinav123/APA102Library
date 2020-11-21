/*
 * Embedded Assignment.cpp
 *
 * Created: 02/11/2020 11.06.59
 * Author : Catalina
 */ 
#include "apa102_led.h"
#include <util/delay.h>


int main(void)
{
	//enable changes to CLKPR
	CLKPR |= (1<<CLKPCE);  
	// set the CLKDIV to 0 
	CLKPR = 0; 
/*    LED led(B,5,3,225);*/
/*	Strip led(B,5,3,225,10);*/
	Matrix led(B,5,3,225,8,8);
	uint8_t array2[][3] = { black,black,black,black,black,black,black,black,
							black,black,blue,blue,blue,blue,blue,black,
							black,black,white,white,red,white,white, black,
							black,black,white,red,red,red,white,black,
							black,black,white,white,red,white,white,black,
							black,black,blue,blue,blue,blue,blue,black,
							black,black,black,black,black,black,black,black,
							black,black,black,black,black,black,black,black};//plus
// 							
	uint8_t array4[][3] = {black,black,red,black,black,black,red,black,
							black,red,red,red,black,red,red,red,
							black, red,red,red,red,red,red,red,
							black, red,red,red,red,red,red,red,
							black,black, red,red,red,red,red,black,
							black,black,black,red,red,red,black,black,
							black,black,black,black,red,black,black,black,
							black,black,black,black,black,black,black,black,
							}; //heart
							
	uint8_t array1[][3] = {green,blue,black,black,black,green,red,black,
							green,yellow,green,black,green,green,green,black,
							black,blue,green,red,green,yellow,black,black,
							black,black,green,green,green,black,black,black,
							black,green,green,green,blue,green,black,black,
							green,green,yellow,black,green,blue,green,black,
							green,blue,black,black,black,yellow,green,black,
							black,black,black,black,black,black,black,black};
	
	while (1) 
    {
		led.set_color(255,0,0);
		_delay_ms(1000);
		led.clear();
		_delay_ms(1000);
		led.set_image(array4);
		_delay_ms(1000);
		led.set_image(array2);
 		_delay_ms(1000);
		led.set_image(array1);
		_delay_ms(1000);
    };
}

