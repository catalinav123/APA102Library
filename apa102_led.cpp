/*
 * apa102_led.cpp
 *
 * Created: 03/11/2020 17.09.35
 *  Author: Catalina
 */ 

#include "apa102_led.h"

 
///constructor takes portb-bit nrs and brightness as input
LED::LED(PortnameType p, char pinc, char pind, uint8_t bright)  
{
	Portname = p;   // 
	portclock = pinc;
	portdata = pind;
	if (Portname == B)
	{
		PORT = &PORTB;
		DDR = &DDRB;
	}
	if (Portname == C)
	{
		PORT = &PORTC;
		DDR = &DDRC;
	}
	if (Portname == D)
	{
		PORT = &PORTD;
		DDR = &DDRD;
	}
	
	*DDR = (1<<portclock) | (1<<portdata); 
	*PORT = (1<<portclock);
}

///SPI_write method uses bit-banging control to send data to the APA102 device
void LED :: SPI_write(uint8_t byte) {
	uint8_t i;
	for (i=0; i<8 ;i++)
	{
		if (byte&0b10000000) {
			// set data high
			*PORT |= (1<<portdata); 
			} else {
			// set data low
			*PORT &= ~(1<<portdata); 
		}
		// SCK hi , data sampled here
		*PORT |= (1<< portclock); 

		byte<<=1;
		// SCK low
		*PORT &= ~(1<<portclock); 
	}
/*	*PORT |= (1<<portdata); // data high*/
}

///SPI_start method produces 4 bytes of 0, equivalent to start frame by the APA102
void LED :: SPI_start() {
	
	SPI_write(0x00);  // Start Frame
	SPI_write(0x00);
	SPI_write(0x00);
	SPI_write(0x00);
}

///SPI_end method produces 4 bytes of 1, equivalent to end frame by the APA102
void LED :: SPI_end() {
	SPI_write(0xFF);
	SPI_write(0XFF);
	SPI_write(0XFF);
 	SPI_write(0XFF);  // End Frame
}

///SPI_LedFrame method used for SPI protocol transmission of data equivalent to led frame by the APA102
void LED :: SPI_LedFrame(uint8_t r, uint8_t g, uint8_t b) {
	
	SPI_write(brightness); // last 5 bits brightness
	SPI_write(b); // blue
	SPI_write(g); // green
	SPI_write(r); // red	
}
///set_color method gives the ability to set any color an LED
void LED :: set_color(uint8_t r, uint8_t g, uint8_t b){
	SPI_start();
	SPI_LedFrame(r,g,b);
	SPI_end();
}

///clear method sets the color of the LED "black" (clears the color of it)
void LED :: clear(){
	SPI_start();
	SPI_LedFrame(0,0,0);
	SPI_end();
}

///set_color method gives possibility to set any color to an array of LEDs
void Strip :: set_color(uint8_t r, uint8_t g, uint8_t b){
	SPI_start();
	for(int i=1; i<=strip_width; i++){
		SPI_LedFrame(r,g,b);
	};
	SPI_end();
}

///set_strip method gives possibility to set an array of LEDs different colors
void Strip ::set_strip(uint8_t color_array[][3] ){
	SPI_start();
	for(int i=0; i <= strip_width - 1; i++){
		SPI_LedFrame(color_array[i][0],color_array[i][1], color_array[i][2]);
	};
	SPI_end();

}

///clear method sets the color of the LED array "black"
void Strip :: clear() {
	SPI_start();
	for(int i=1; i <= strip_width; i++){
		SPI_LedFrame(0,0,0);
	};
	SPI_end();
}

///set_color method gives the possibility to set a two dimensional array of LEDs (matrix) any same color
void Matrix :: set_color(uint8_t r, uint8_t g, uint8_t b){
	SPI_start();
	for(int i=1; i<=strip_width * matrix_height; i++){
			SPI_LedFrame(r,g,b);
	};
	SPI_end();
}

///set_image method outputs an image on matrix represented by a two dimensional array of LEDs
void Matrix ::set_image(uint8_t matrix_array[][3]) {
	SPI_start();
	for(int i=0; i <= strip_width * matrix_height -1; i++){
			SPI_LedFrame(matrix_array[i][0], matrix_array[i][1], matrix_array[i][2]);
	};
	SPI_end();
}

///clear method clears the matrix
void Matrix :: clear(){
	SPI_start();
	for(int i=1; i<=strip_width * matrix_height; i++){
			SPI_LedFrame(0,0,0);
	};
	SPI_end();
	}
