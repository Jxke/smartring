#include "config.h"
int state = 0;
int piezoPin = 12;


AdafruitIO_Feed *ringTrigger = io.feed("ringmaster.ringtrigger", "Jxke");

void setup() {
  Serial.begin(115200);
  while(! Serial);
  Serial.print("Connecting to Adafruit IO");

  io.connect();


  ringTrigger->onMessage(handleMessage);


  while(io.mqttStatus() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }


  ringTrigger->get();

  Serial.println();
  Serial.println(io.statusText());

}

void loop() {
  io.run();

}

void handleMessage(AdafruitIO_Data *data) {
  Serial.print("received <- ");
  Serial.println(data->value());
  state = state + 1;
  Serial.println(state);
    if ((state % 2) == 0){
    tone(piezoPin, 800, 600);
    delay(100);
    tone(piezoPin, 900, 800);
    delay(4000);
   } else {
    tone(piezoPin, 500, 400);
    delay(200);
    tone(piezoPin, 300, 400);
    delay(200);
    tone(piezoPin, 200, 500);
    delay(200);
    tone(piezoPin, 100, 700);
    delay(4000);
   }
}
