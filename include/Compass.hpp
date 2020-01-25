
#include <Arduino.h>
#include <Wire.h>
#include <QMC5883LCompass.h>

class Compass 
{
public:
    void setupCompass();
    void updateCompass();

    bool getHeading(float & heading); // bool is true when heading is valid;
    bool calibrated();
    

private:

    QMC5883LCompass compass = QMC5883LCompass();
    float heading;
    int error;
    bool isCalibrated;
    bool valid;

    float update_delay = 1000;  // @todo manage millis() to not turncate
    float lastMillis = 0;

};