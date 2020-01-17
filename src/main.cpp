#include <Arduino.h>
#include "test1.hpp"
#include "GPS.hpp"

GPS gps;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  test1 test; 
  
  gps.setupGPS();


  test.runTest();

}

void loop() {
  // put your main code here, to run repeatedly:
  gps.updateGPS();
  // Serial.println("Astro");
  // delay(100);
}