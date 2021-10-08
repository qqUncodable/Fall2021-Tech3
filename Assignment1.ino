
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "paj7620.h"
#define GES_ENTRY_TIME			800				// When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
#define GES_QUIT_TIME			1000

#define PIN        6

#define NUMPIXELS 8

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint8_t colorR = 0,colorG = 0,colorB = 255;

void setup()
{
	uint8_t error = 0;
  strip.begin();
  strip.show();
	Serial.begin(9600);
	Serial.println("\nGesture TEST DEMO: Recognize 9 gestures.");
	error = paj7620Init();			// initialize Paj7620 registers
	if (error){
		Serial.print("INIT ERROR,CODE:");
		Serial.println(error);
	}
	else{
		Serial.println("INIT OK");
	}
	Serial.println("Please input your gestures:\n");
}

void loop()
{
	uint8_t data = 0, data1 = 0, error;
	error = paj7620ReadReg(0x43, 1, &data);				// Read Bank_0_Reg_0x43/0x44 for gesture result.
	if (!error){
		switch (data){
			case GES_RIGHT_FLAG:
				delay(200);
				paj7620ReadReg(0x43, 1, &data);
				if(data == GES_FORWARD_FLAG){
          //color_led(ON, OFF, ON);//  
					Serial.println("Forward");
					delay(GES_QUIT_TIME);
				}
				else if(data == GES_BACKWARD_FLAG){
          //color_led(OFF, ON, ON);//  
					Serial.println("Backward");
					delay(GES_QUIT_TIME);
				}
				else{
          for(int i=0; i<strip.numPixels(); i++) { 
        strip.setPixelColor(i, strip.Color(colorR,colorG,colorB));
        strip.setBrightness(100);
        strip.show();
        delay(20);}
					Serial.println("Right");
				}          
				break;
        
			case GES_LEFT_FLAG: 
				delay(200);
				paj7620ReadReg(0x43, 1, &data);
				if(data == GES_FORWARD_FLAG){
          //color_led(ON, OFF, ON);//  
					Serial.println("Forward");
					delay(GES_QUIT_TIME);
				}
				else if(data == GES_BACKWARD_FLAG){
              //color_led(OFF, ON, ON);// 
					Serial.println("Backward");
					delay(GES_QUIT_TIME);
				}
				else{
          //color_led(OFF, ON, OFF);//
					Serial.println("Left");
				}          
				break;
        
			case GES_UP_FLAG:
				delay(200);
				paj7620ReadReg(0x43, 1, &data);
				if(data == GES_FORWARD_FLAG){
          //color_led(ON, OFF, ON);//
					Serial.println("Forward");
					delay(GES_QUIT_TIME);
				}
				else if(data == GES_BACKWARD_FLAG){
          //color_led(OFF, ON, ON);// 
					Serial.println("Backward");
					delay(GES_QUIT_TIME);
				}
				else{
          //color_led(OFF, OFF, ON);
					Serial.println("Up");
				}          
				break;
        
			case GES_DOWN_FLAG:
				delay(200);
				paj7620ReadReg(0x43, 1, &data);
				if(data == GES_FORWARD_FLAG){
          //color_led(ON, OFF, ON);//
					Serial.println("Forward");
					delay(GES_QUIT_TIME);
				}
				else if(data == GES_BACKWARD_FLAG){
          //color_led(OFF, ON, ON);// 
					Serial.println("Backward");
					delay(GES_QUIT_TIME);
				}
				else{
          //color_led(ON, ON, OFF);//
					Serial.println("Down");
				}          
				break;
        
			case GES_FORWARD_FLAG:
        //color_led(ON, OFF, ON);//
				Serial.println("Forward");
				delay(GES_QUIT_TIME);
				break;
        
			case GES_BACKWARD_FLAG:	
        //color_led(OFF, ON, ON);//  
				Serial.println("Backward");
				delay(GES_QUIT_TIME);
				break;
        
			case GES_CLOCKWISE_FLAG:
				Serial.println("Clockwise");
				break;
        
			case GES_COUNT_CLOCKWISE_FLAG:
				Serial.println("anti-clockwise");
				break;
          
			default:
				paj7620ReadReg(0x44, 1, &data1);
				if (data1 == GES_WAVE_FLAG){
          //color_led(OFF, OFF, OFF);//
          for(int i=0; i<strip.numPixels(); i++) { 
        strip.setPixelColor(i, strip.Color(0,0,0));
        strip.show();}
          delay(GES_QUIT_TIME);
					Serial.println("wave");
				}
				break;
		}
	}
	delay(100);
}
