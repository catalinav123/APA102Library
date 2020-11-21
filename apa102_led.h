/*
 * apa102_led.h
 *
 * Created: 03/11/2020 17.13.05
 *  Author: Catalina
 */ 


#ifndef APA102_LED_H_
#define APA102_LED_H_
#include <avr/io.h>
///MCU crystal
#define F_CPU 16000000UL  
///predefined colors
#define red {255,0,0}  
#define green {0,255,0}
#define blue {0,0,255}
#define white {255,255,255}
#define yellow {204,119,34}
#define black {0,0,0}

typedef enum
{	B,	C,	D}
PortnameType;

class LED 
{
	public:
	LED(PortnameType p, char pinc, char pind, uint8_t bright); 
	/// set color of the led
	void set_color(uint8_t r, uint8_t g, uint8_t b); 
	///clear the led
	void clear(); 
	protected:
	/// pointer to PORT
	volatile uint8_t	*PORT;
	/// pointer to DDR
	volatile uint8_t	*DDR;
	volatile uint8_t brightness;
	unsigned char portclock;
	unsigned char portdata;
	PortnameType Portname;
	///bit-banging for SPI protocol
	void SPI_write(uint8_t byte); 
	///Start frame
	void SPI_start();
	///LED frame
	void SPI_LedFrame(uint8_t r, uint8_t g, uint8_t b);
	///End frame
	void SPI_end();
	
};

class Strip : public LED
{
	public:
	///subclass
	Strip(PortnameType p, char pinc, char pind, uint8_t bright, int width) : LED(p, pinc, pind, bright){strip_width = width;}; 
	/// set color of the strip
	void set_color(uint8_t r, uint8_t g, uint8_t b); 
	 /// set the colors of the strip depending on the given array
	 void set_strip(uint8_t array[][3] );
	/// clear the strip
	void clear();
	protected:
	volatile int strip_width;
	private:
};

class Matrix : public Strip
{
	public:
	///subclass
	Matrix(PortnameType p, char pinc, char pind,uint8_t bright, int height, int width) : Strip(p, pinc, pind, bright, width){matrix_height = height;};
	/// set color of the matrix
	void set_color(uint8_t r, uint8_t g, uint8_t b); 
	///set the colors of the matrix depending on the given array
	void set_image(uint8_t matrix_array[][3]); 
	/// clear the matrix
	void clear(); 
	volatile int matrix_height;
	protected:
	
	private:
};



#endif /* APA102_LED_H_ */