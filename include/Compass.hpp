
#include <HMC5883L.h>
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
    float heading;


    HMC5883L compass;
    MagnetometerScaled valueOffset;

    int error;
    bool isCalibrated;
    bool valid;

};