#include "GPS.hpp"

void GPS::setupGPS()
{
    Serial.println("GPS setup start");

    Serial2.begin(9600, SERIAL_8N1);//, RXD2, TXD2);
    Serial.print("Simple TinyGPS library v. ");
    Serial.println(TinyGPS::library_version());

    Serial.println("GPS setup complete");


    pinMode(33,OUTPUT);

    digitalWrite(33,HIGH);
    delay(1000);
    digitalWrite(33,LOW);

}

bool GPS::getGPSPosition(GPSPosition &pos)
{
    if (!isValid)
        return false;
  
    pos = gpsPos;
    return true;
}

bool GPS::getGPSTime(GPSTime &time)
{
    if (!isValid)
        return false;

    time = gpsTime;
    return true;
}


int GPS::getConnectedSatellites()
{
    return connectedSatellites;
}

void GPS::updateGPS()
{
    bool newData = false;

    if(Serial2.available())
    {
        char c = Serial2.read();
       // Serial.write(c);

        if (gps.encode(c))
            newData = true;
    }

    if (newData)
    {
        digitalWrite(33,HIGH);
        float flat, flon;
        unsigned long age;
        gps.f_get_position(&flat, &flon, &age);
        Serial.print("LAT=");
        Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
        Serial.print(" LON=");
        Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
        Serial.print(" SAT=");
        Serial.println(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
        Serial.print(" PREC=");
        Serial.println(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());

        connectedSatellites = gps.satellites();

        gpsPos.alt = gps.f_altitude();
        gpsPos.lat = flat;
        gpsPos.lon = flon;
        isValid = true;

        calculateDateTime(gps);
    }
    else 
    {
        connectedSatellites = 0;
        digitalWrite(33,LOW);
    }
}

void GPS::calculateDateTime(TinyGPS &gps)
{
    int year;
    byte month, day, hour, minute, second, hundredths;
    unsigned long age;
    gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);

    if (age == TinyGPS::GPS_INVALID_AGE)
        isValid = false;
    else
    {
        gpsTime.year = year;
        gpsTime.month = month;
        gpsTime.day = day;
        gpsTime.minutes = minute;
        gpsTime.second = second;

        char sz[32];
        sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d ",
                month, day, year, hour, minute, second);
        Serial.print(sz);
    }
}