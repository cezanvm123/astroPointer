#include <Compass.hpp>

void Compass::setupCompass()
{
    Serial.println("Compass setup started!");

    Wire.begin();

    Serial.println("Setting measurement scale");
    error = compass.setScale(1.3); // Set the scale of the compass.
    if (error != 0)                // If there is an error, print it out.
        Serial.println(compass.getErrorText(error));

    Serial.println("Setting measurement mode to continous.");
    error = compass.setMeasurementMode(MEASUREMENT_CONTINUOUS); // Set the measurement mode to Continuous
    if(error != 0) // If there is an error, print it out.
        Serial.println(compass.getErrorText(error));

    Serial.println("Compas setup complete");

    calibrate();
}

void Compass::calibrate()
{
    //Serial << ">>>> calibrate the compass\n";
    Serial.println("calibrating the compass"); //  THIS should be displayed on the display
    MagnetometerScaled valueMax = {0, 0, 0};
    MagnetometerScaled valueMin = {0, 0, 0};

    // calculate x, y and z offset

    Serial.println("please rotate the device"); //  THIS should be displayed on the display
    int xcount = 0;
    int ycount = 0;
    int zcount = 0;
    boolean xZero = false;
    boolean yZero = false;
    boolean zZero = false;
    MagnetometerScaled value;
    Serial.println("Starting while");
    while (xcount < 3 || ycount < 3 || zcount < 3)
    {
        Serial.println("In while");
        value = compass.readScaledAxis();
        if ((fabs(value.XAxis) > 600) || (fabs(value.YAxis) > 600) || (fabs(value.ZAxis) > 600))
        {
            continue;
        }

        if (valueMin.XAxis > value.XAxis)
        {
            valueMin.XAxis = value.XAxis;
        }
        else if (valueMax.XAxis < value.XAxis)
        {
            valueMax.XAxis = value.XAxis;
        }

        if (valueMin.YAxis > value.YAxis)
        {
            valueMin.YAxis = value.YAxis;
        }
        else if (valueMax.YAxis < value.YAxis)
        {
            valueMax.YAxis = value.YAxis;
        }

        if (valueMin.ZAxis > value.ZAxis)
        {
            valueMin.ZAxis = value.ZAxis;
        }
        else if (valueMax.ZAxis < value.ZAxis)
        {
            valueMax.ZAxis = value.ZAxis;
        }

        if (xZero)
        {
            if (fabs(value.XAxis) > 50)
            {
                xZero = false;
                xcount++;
            }
        }
        else
        {
            if (fabs(value.XAxis) < 40)
            {
                xZero = true;
            }
        }

        if (yZero)
        {
            if (fabs(value.YAxis) > 50)
            {
                yZero = false;
                ycount++;
            }
        }
        else
        {
            if (fabs(value.YAxis) < 40)
            {
                yZero = true;
            }
        }

        if (zZero)
        {
            if (fabs(value.ZAxis) > 50)
            {
                zZero = false;
                zcount++;
            }
        }
        else
        {
            if (fabs(value.ZAxis) < 40)
            {
                zZero = true;
            }
        }

        delay(30);
    }

    valueOffset.XAxis = (valueMax.XAxis + valueMin.XAxis) / 2;
    valueOffset.YAxis = (valueMax.YAxis + valueMin.YAxis) / 2;
    valueOffset.ZAxis = (valueMax.ZAxis + valueMin.ZAxis) / 2;
#if 0 
  Serial << "max: " << valueMax.XAxis << '\t' << valueMax.YAxis << '\t' << valueMax.ZAxis << endl;
  Serial << "min: " << valueMin.XAxis << '\t' << valueMin.YAxis << '\t' << valueMin.ZAxis << endl;
  Serial << "offset: " << valueOffset.XAxis << '\t' << valueOffset.YAxis << '\t' << valueOffset.ZAxis << endl;
  
  Serial << "<<<<" << endl;
#endif
    Serial.print("max: ");
    Serial.print(valueMax.XAxis);
    Serial.print(valueMax.YAxis);
    Serial.println(valueMax.ZAxis);
    Serial.print("min: ");
    Serial.print(valueMin.XAxis);
    Serial.print(valueMin.YAxis);
    Serial.println(valueMin.ZAxis);
    Serial.print("offset: ");
    Serial.print(valueOffset.XAxis);
    Serial.print(valueOffset.YAxis);
    Serial.println(valueOffset.ZAxis);
}

void Compass::updateCompass()
{
    MagnetometerRaw raw = compass.readRawAxis();
    
    MagnetometerScaled scaled = compass.readScaledAxis();

    scaled.XAxis -= valueOffset.XAxis;
    scaled.YAxis -= valueOffset.YAxis;
    scaled.ZAxis -= valueOffset.ZAxis;

    float yxHeading = atan2(scaled.YAxis, scaled.XAxis);
    float zxHeading = atan2(scaled.ZAxis, scaled.XAxis);

    heading = yxHeading;

    // this value is currently based on breda this should be calculated based on the GPS coordinates
    // magnetic deinclination is +1d 39'
    float degrees = 1;
    float degreeMinutes = 39;
    float degreeSeconds = 0;
    float degreesConverted = degrees + (degreeMinutes / 60 ) + (degreeSeconds /60);

    float declinationAngle = degreesConverted * (PI/ 180.0);

    heading += declinationAngle;

    if(heading < 0)
        heading += 2*PI;
    
    // Check for wrap due to addition of declination.
    if(heading > 2*PI)
        heading -= 2*PI;

    float headingDegrees = heading * 180/PI; 

    Serial.print("Heading is: ");
    Serial.println(heading);

}
