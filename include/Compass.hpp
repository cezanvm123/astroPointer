
#include<Arduino.h>
#include <Wire.h>

class Compass 
{
public:
    void setupCompass();
    void updateCompass();

    bool getHeading(float & heading); // bool is true when heading is valid;
    bool calibrated();
    

private:
    void calibrate();
    void displaySensorDetails();
    float heading;

    


    int error;
    bool isCalibrated;
    bool valid;

};