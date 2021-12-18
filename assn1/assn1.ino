
#include <Wire.h>
#include "Gesture.h"
#define GES_ENTRY_TIME			800				// When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
#define GES_QUIT_TIME			1000
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define ON 1    
#define OFF 0   

void setup()
{
  uint8_t error = 0;
  Serial.begin(9600);
  Serial.println("\nGesture TEST DEMO: Recognize 9 gestures.");
  error = GestureInit();			// initialize Paj7620 registers
  if (error) {
    Serial.print("INIT ERROR,CODE:");
    Serial.println(error);
  }
  else {
    Serial.println("INIT OK");
  }
  Serial.println("Please input your gestures:\n");
  pwm.begin();//open servo driver
  pwm.setPWMFreq(60);//servo = 60HZ
  pwm.setPWM(0, 0, 400);
  pwm.setPWM(1, 0, 400);
  pwm.setPWM(2, 0, 400);
  pwm.setPWM(3, 0, 400);
  pwm.setPWM(4, 0, 400);
  pwm.setPWM(5, 0, 400);//initialize position
}

void loop()
{
  uint8_t data = 0, data1 = 0, error;
  error = GestureReadReg(0x43, 1, &data);				// Read Bank_0_Reg_0x43/0x44 for gesture result.
  if (!error) {
    switch (data) {
      case GES_RIGHT_FLAG:
        delay(200);
        GestureReadReg(0x43, 1, &data);
        if (data == GES_FORWARD_FLAG) {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if (data == GES_BACKWARD_FLAG) {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else {
          Serial.println("Right");
          pwm.setPWM(0, 0, 300);
          pwm.setPWM(1, 0, 300);
          delay(1000);
          pwm.setPWM(2, 0, 300);
          pwm.setPWM(3, 0, 300);
          delay(1000);
          pwm.setPWM(4, 0, 300);
          pwm.setPWM(5, 0, 300);
        }
        break;

      case GES_LEFT_FLAG:
        delay(200);
        GestureReadReg(0x43, 1, &data);
        if (data == GES_FORWARD_FLAG) {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if (data == GES_BACKWARD_FLAG) {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else {
          Serial.println("Left");
          pwm.setPWM(4, 0, 500);
          pwm.setPWM(5, 0, 500);
          delay(1000);
          pwm.setPWM(2, 0, 500);
          pwm.setPWM(3, 0, 500);
          delay(1000);
          pwm.setPWM(0, 0, 500);
          pwm.setPWM(1, 0, 500);
        }
        break;

      case GES_UP_FLAG:
        delay(200);
        GestureReadReg(0x43, 1, &data);
        if (data == GES_FORWARD_FLAG) {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if (data == GES_BACKWARD_FLAG) {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else {
          Serial.println("Up");
          pwm.setPWM(1, 0, 400);
          pwm.setPWM(3, 0, 400);
          pwm.setPWM(5, 0, 400);
          delay(1000);
          pwm.setPWM(0, 0, 400);
          pwm.setPWM(2, 0, 400);
          pwm.setPWM(4, 0, 400);
        }
        break;

      case GES_DOWN_FLAG:
        delay(200);
        GestureReadReg(0x43, 1, &data);
        if (data == GES_FORWARD_FLAG) {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if (data == GES_BACKWARD_FLAG) {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else {
          Serial.println("Down");
          pwm.setPWM(0, 0, 400);
          pwm.setPWM(2, 0, 400);
          pwm.setPWM(4, 0, 400);
          delay(1000);
          pwm.setPWM(1, 0, 400);          
          pwm.setPWM(3, 0, 400);
          pwm.setPWM(5, 0, 400);
        }
        break;

      case GES_FORWARD_FLAG:
        Serial.println("Forward");
        delay(GES_QUIT_TIME);
        break;

      case GES_BACKWARD_FLAG:
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
        GestureReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG) {
          delay(GES_QUIT_TIME);
          Serial.println("wave");
        }
        break;
    }
  }
  delay(100);
}
