#include <Arduino.h>
#include "test1.hpp"
#include "GPS.hpp"
#include <ButtonEncoder.hpp>

GPS gps;
ButtonEncoder enc;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  test1 test; 
  
  gps.setupGPS();
  enc.ButtonEncoderSetup();

  test.runTest();

}

void loop() {
  // put your main code here, to run repeatedly:
  gps.updateGPS();


   int navigated, pressed;

  enc.ButtonEncoderUpdate(navigated, pressed);
  
  if(navigated != 0)
    Serial.println(navigated);
  // Serial.println("Astro");
  // delay(100);
}