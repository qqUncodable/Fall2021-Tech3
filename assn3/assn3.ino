#include "config.h"
#include <ESP32Servo.h>
#define muscle A0

//buzzer pin
#define Buzzer 18
#define Sensor 19
#define LEDC_CHANNEL_0 0
#define LEDC_TIMER_13_BIT 13

//io
int current = 0;
int last = -1;
int m1;
AdafruitIO_Feed *muscle1 = io.feed("muscle");

//buzzer sings
int melody[] = {330, 330, 330, 262, 330, 392, 196, 262, 196, 165, 220, 247, 233, 220, 196, 330, 392, 440, 349, 392, 330, 262, 294, 247, 262, 196, 165, 220, 247, 233, 220, 196, 330, 392,440, 349, 392, 330, 262, 294, 247, 392, 370, 330, 311, 330, 208, 220, 262, 220, 262,
294, 392, 370, 330, 311, 330, 523, 523, 523, 392, 370, 330, 311, 330, 208, 220, 262,220, 262, 294, 311, 294, 262, 262, 262, 262, 262, 294, 330, 262, 220, 196, 262, 262,262, 262, 294, 330, 262, 262, 262, 262, 294, 330, 262, 220, 196};
int noteDurations[] = {8,4,4,8,4,2,2,3,3,3,4,4,8,4,8,8,8,4,8,4,3,8,8,3,3,3,3,4,4,8,4,8,8,8,4,8,4,3,8,8,2,8,8,8,4,4,8,8,4,8,8,3,8,8,8,4,4,4,8,2,8,8,8,4,4,8,8,4,8,8,3,3,3,1,8,4,4,8,4,8,4,8,2,8,4,4,8,4,1,8,4,4,8,4,8,4,8,2};

void setup() {
  
  Serial.begin(9600);

  //connect io
  while(! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  muscle1->onMessage(handleMessage1);
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
    }

  //get conditions of io
  Serial.println();
  Serial.println(io.statusText());
  muscle1->get();

}

void loop() 
{
//send to io
  io.run();
  current = analogRead(muscle);
  Serial.print("sending -> ");
  Serial.println(current);
  muscle1->save(current);
  delay(1000);

  //buzzer part
  int noteDuration;

  if (digitalRead(Sensor) == false) {
    for (int i = 0; i < sizeof(noteDurations); ++i){
      noteDuration = 800/noteDurations[i];
      ledcSetup(LEDC_CHANNEL_0, melody[i]*2, LEDC_TIMER_13_BIT);
      ledcAttachPin(Buzzer, LEDC_CHANNEL_0);
      ledcWrite(LEDC_CHANNEL_0, 50);
      delay(noteDuration * 1.30);
      if (digitalRead(19)){
        break;
      }
    }
    ledcWrite(0,0);
  }
  else{
        ledcWrite(0,0);
      }

}

void handleMessage1(AdafruitIO_Data *data) 
{
  Serial.print("received <- ");
  if(data->toPinLevel() == HIGH)
    Serial.println("HIGH");
  else
    Serial.println("LOW");
}
