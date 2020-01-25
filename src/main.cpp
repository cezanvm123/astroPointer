#include <Arduino.h>
#include "test1.hpp"
#include "GPS.hpp"
#include <ButtonEncoder.hpp>
#include <Compass.hpp>

GPS gps;
ButtonEncoder enc;
Compass compass;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  test1 test; 
  
  gps.setupGPS();

  enc.ButtonEncoderSetup();
  

 // test.runTest();
  compass.setupCompass();

}

void loop() {
  // put your main code here, to run repeatedly:     
  
  compass.updateCompass();


  gps.updateGPS();


  int navigated, pressed;
  enc.ButtonEncoderUpdate(navigated, pressed);

  if(navigated != 0)
    Serial.println(navigated);
  // Serial.println("Astro");
  // delay(100);
}