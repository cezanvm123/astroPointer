#include <Compass.hpp>

void Compass::setupCompass()
{
   compass.init();
   //compass.setSmoothing(10, true);
   lastMillis = millis();
}

// void Compass::calibrate()
// {
// }

void Compass::updateCompass()
{
   if ((millis() - lastMillis) < update_delay)
      return;


   lastMillis = millis();

   int x, y, z;
   compass.read();

   x = compass.getX();
   y = compass.getY();
   z = compass.getZ();

   Serial.println(x);
   Serial.println(y);
   Serial.println(z);

   float yxHeading = atan2(y, x);
   float zxHeading = atan2(z, x);

   heading = yxHeading;

   // this value is currently based on breda this should be calculated based on the GPS coordinates
   // magnetic deinclination is +1d 39'
   float degrees = 1;
   float degreeMinutes = 39;
   float degreeSeconds = 0;
   float degreesConverted = degrees + (degreeMinutes / 60) + (degreeSeconds / 60);

   float declinationAngle = degreesConverted * (PI / 180.0);

   heading += declinationAngle;

   if (heading < 0)
      heading += 2 * PI;

   // Check for wrap due to addition of declination.
   if (heading > 2 * PI)
      heading -= 2 * PI;

   float headingDegrees = heading * 180 / PI;

   Serial.print("Heading is: ");
   Serial.println(headingDegrees);
}
