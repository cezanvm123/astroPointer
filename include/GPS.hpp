#include <Arduino.h>
#include <TinyGPS.h>

#define RXD2 16
#define TXD2 17


struct GPSPosition
{
   float lon;
   float lat;
   float alt;
};

struct GPSTime 
{
    int year;
    int month;
    int day;
    int hour;
    int minutes;
    int second;
};

class GPS 
{

public:
    void setupGPS();
    void updateGPS();
    bool getGPSPosition(GPSPosition &pos);  // returns true is data is valid returns false if unvalid
    bool getGPSTime(GPSTime & time);    // returns true is data is valid returns false if unvalid
    int getConnectedSatellites();


private:
    TinyGPS gps;

    GPSPosition gpsPos;
    GPSTime gpsTime;


    // float flat, flon;
    // unsigned long age, data, time, chars = 0;
    // unsigned short sentences = 0, failed = 0;
    bool isValid = false;
    int connectedSatellites = 0;

    void calculatePostion(); // not currently used 
    void calculateDateTime(TinyGPS &gps);

};


