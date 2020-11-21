APA102 is a RGB LED with a built-in controller. This library allows you to control an LED, a strip and a matrix formed from more LEDS. 
	
	To use this library #include “apa102_led.h”
	
	Initialization of objects (examples):
	LED led (B, 5, 3, 225) parameters (port letter, clock pin, data pin, brightness);
	Strip led (B, 5, 3, 225, 10) parameters (port letter, clock pin, data pin, brightness, nr of leds);
	Matrix led (B, 5, 3, 225, 8, 8) parameters (port letter, clock pin, data pin, brightness, height of the matrix, width of the matrix).
	
	Functions:
	Matrix Class:
	•	set_image(array[][]):
		o	passes an array of RGB values to the matrix of leds;
		o	gives the possibility to output an image;
		o	parameters: array of RGB values (range(0-255)).
	Strip Class:
	•	set_strip(array[][]):
		o	passes an array of RGB values to the strip of leds;
		o	gives the possibility to set different colors;
		o	parameters: array of RGB values (range (0-255)).
	LED, Strip, Matrix Class:
	•	set_color(r,g,b) : 
		o	passes the RGB values to the LEDs giving the possibility to set any color;
		o	parameters: range(0-255).
	•	clear():
		o	clears the color of the LEDS, passing (0,0,0) as RGB values;
		o	no parameters.
