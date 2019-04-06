#include "QuadDisplay2.h"
#define POMP_PIN        8
#define HUMIDITY_PIN    A0
#define HUMIDITY_MIN    700
#define HUMIDITY_MAX    900
#define INTERVAL        60000 * 5   
unsigned int humidity = 0;
unsigned long waitTime = 0;
QuadDisplay qd(9);

void setup(void)
{
  qd.begin();
  pinMode(POMP_PIN, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  qd.displayInt(0);
}

void loop(void)
{
  int humidityNow = analogRead(HUMIDITY_PIN);
  int WaterLevelDown = digitalRead(6);
  int WaterLevelUp = digitalRead(7);
  if(humidityNow != humidity) {
    humidity = humidityNow;
    qd.displayInt(humidityNow);
  }
  if(WaterLevelDown = 1) {
  if ((waitTime == 0 || millis() - waitTime > INTERVAL) && humidity < HUMIDITY_MIN ) {
    // включаем помпу
    digitalWrite(POMP_PIN, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    delay(15000);
    digitalWrite(POMP_PIN, LOW);
    digitalWrite(10, LOW); 
    waitTime = millis();
     }
  } else {
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    tone(3, 4500, 20);
    delay(500);
    tone(3, 440, 0);
    digitalWrite(12, LOW);
    delay(500);
    tone(3, 4500, 20);
    digitalWrite(12, HIGH);
    //if(WaterLevelDown = 0) break;
  }
}
