#include <Arduino.h>
#include <Ephemeris.h>

class test1
{

public:
    void runTest();

private:
    void printPlanet(char *solarSystemObjectName, SolarSystemObjectIndex index, int day, int month, int year, int hour, int minute, int second );
    void printSolarSystemObjects(int day, int month, int year, int hour, int minute, int second);
    void printHorizontalCoordinates(HorizontalCoordinates coord);
    void printEquatorialCoordinates(EquatorialCoordinates coord);
    void equatorialCoordinatesToString(EquatorialCoordinates coord, char raCoord[14] , char decCoord[14]);
    void printDateAndTime(int day, int month, int year, int hour, int minute, int second );
};