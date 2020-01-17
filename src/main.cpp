#include <Arduino.h>

#include "test1.hpp"

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  test1 test; 
  test.runTest();

}

void loop() {
  // put your main code here, to run repeatedly:

  // Serial.println("Astro");
  // delay(100);
}