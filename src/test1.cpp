#include <test1.hpp>


void test1::printDateAndTime(int day, int month, int year, int hour, int minute, int second )
{
  Serial.print(day);
  Serial.print("/");
  Serial.print(month);
  Serial.print("/");
  Serial.print(year);
  Serial.print(" ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.print(second);
}


void test1::equatorialCoordinatesToString(EquatorialCoordinates coord, char raCoord[14] , char decCoord[14])
{
  int raHour,raMinute;
  float raSecond;
  Ephemeris::floatingHoursToHoursMinutesSeconds(coord.ra, &raHour, &raMinute, &raSecond);
    
  sprintf(raCoord," %02dh%02dm%02ds.%02d",raHour,raMinute,(int)raSecond,(int)round(((float)(raSecond-(int)raSecond)*pow(10,2))));
    
  int decDegree,decMinute;
  float decSecond;
  Ephemeris::floatingDegreesToDegreesMinutesSeconds(coord.dec, &decDegree, &decMinute, &decSecond);
    
  if(decDegree<0)
  {
    sprintf(decCoord,"%02dd%02d'%02d\".%02d",(int)decDegree,decMinute,(int)decSecond,(int)round(((float)(decSecond-(int)decSecond)*pow(10,2))));
  }
  else
  {
    sprintf(decCoord," %02dd%02d'%02d\".%02d",(int)decDegree,decMinute,(int)decSecond,(int)round(((float)(decSecond-(int)decSecond)*pow(10,2))));
  }
}

void test1::printEquatorialCoordinates(EquatorialCoordinates coord)
{
  if( isnan(coord.ra) ||  isnan(coord.dec))
  {
    // Do not work for Earth of course...
    Serial.println("R.A: -");
    Serial.println("Dec: -");
        
    return;
  }
    
  char raCoord[14];
  char decCoord[14];
  equatorialCoordinatesToString(coord,raCoord,decCoord);

  Serial.print("R.A: ");
  Serial.println(raCoord);

  Serial.print("Dec: ");
  Serial.println(decCoord);

  return;
}

void test1::printHorizontalCoordinates(HorizontalCoordinates coord)
{
  if( isnan(coord.azi) ||  isnan(coord.alt))
  {
    // Do not work for Earth of course...
    Serial.println("Azi: -");
    Serial.println("Alt: -");
        
    return;
  }

  Serial.print("Azi: ");
  Serial.print(coord.azi,2);
  Serial.println("d");

  Serial.print("Alt: ");
  Serial.print(coord.alt,2);
  Serial.println("d");
}

void test1::printSolarSystemObjects(int day, int month, int year, int hour, int minute, int second)
{
  Serial.println("_____________________________________");
  printPlanet("Sun",          Sun,     day, month, year, hour, minute, second);
  Serial.println("_____________________________________");
  printPlanet("Mercury",      Mercury, day, month, year, hour, minute, second);
  Serial.println("_____________________________________");
  printPlanet("Venus",        Venus,   day, month, year, hour, minute, second);
  Serial.println("_____________________________________");
  printPlanet("Earth",        Earth,   day, month, year, hour, minute, second);
  Serial.println("_____________________________________");
  printPlanet("Earth's Moon", EarthsMoon,   day, month, year, hour, minute, second);
  Serial.println("_____________________________________");
  printPlanet("Mars",         Mars,    day, month, year, hour, minute, second);
  Serial.println("_____________________________________");
  printPlanet("Jupiter",      Jupiter, day, month, year, hour, minute, second);
  Serial.println("_____________________________________");
  printPlanet("Saturn",       Saturn,  day, month, year, hour, minute, second);
  Serial.println("_____________________________________");
  printPlanet("Uranus",       Uranus,  day, month, year, hour, minute, second);
  Serial.println("_____________________________________");
  printPlanet("Neptune",      Neptune, day, month, year, hour, minute, second);
  Serial.println("_____________________________________");
}

void test1::printPlanet(char *solarSystemObjectName, SolarSystemObjectIndex index, int day, int month, int year, int hour, int minute, int second )
{
  SolarSystemObject solarSystemObject = Ephemeris::solarSystemObjectAtDateAndTime(index, day, month, year, hour, minute, second);

  if( index == Earth )
  {
    Serial.println(solarSystemObjectName);
    Serial.println("Look under your feet... ;)");

    return;
  }
  
  Serial.println(solarSystemObjectName);
  printEquatorialCoordinates(solarSystemObject.equaCoordinates);
  printHorizontalCoordinates(solarSystemObject.horiCoordinates);

  if( solarSystemObject.riseAndSetState == RiseAndSetOk )
  {
    int hour,minute;
    float second;
    
    Ephemeris::floatingHoursToHoursMinutesSeconds(solarSystemObject.rise, &hour, &minute, &second);
    Serial.print("Rise: ");
    Serial.print(hour);
    Serial.print("h");
    Serial.print(minute);
    Serial.print("m");
    Serial.print(second);
    Serial.println("s");

    Ephemeris::floatingHoursToHoursMinutesSeconds(solarSystemObject.set, &hour, &minute, &second);
    Serial.print("Set:  ");
    Serial.print(hour);
    Serial.print("h");
    Serial.print(minute);
    Serial.print("m");
    Serial.print(second);
    Serial.println("s");
  }

  if( isnan(solarSystemObject.diameter) )
  {
    // Do not work for Earth of course...
    Serial.println("Dist: -");
    Serial.println("Diam: -");
  }
  else
  {
    Serial.print("Dist: ");
    if( index != EarthsMoon )
    {
      Serial.print(solarSystemObject.distance,3);
      Serial.println(" AU");
    }
    else
    {
      Serial.print(solarSystemObject.distance/6.68459e-9);
      Serial.println(" Km");
    }
    
    if( solarSystemObject.diameter <= 1 )
    {
      Serial.print("Diam: ");
      Serial.print(solarSystemObject.diameter*60,2);
      Serial.println("\"");
    }
    else
    {
      Serial.print("Diam: ");
      Serial.print(solarSystemObject.diameter,2);
      Serial.println("'");
    }
  }
}


void test1::runTest()
{
    // Set location on earth for horizontal coordinates transformations

    Ephemeris::setLocationOnEarth(51.569, 4.78571);

    // // East is negative and West is positive
    // Ephemeris::flipLongitude(false);

    // Set altitude to improve rise and set precision
    Ephemeris::setAltitude(0);

    // Choose a date and time
    int day = 17, month = 1, year = 2020, hour = 10, minute = 0, second = 0;

    // Compute and print solar system objects
    Serial.print("Data of Solar system objects (");
    printDateAndTime(day, month, year, hour, minute, second);
    Serial.println(")");
    printSolarSystemObjects(day, month, year, hour, minute, second);

    Serial.println("Benchmarking Solar system...");
    float startTime = millis();
    for (int num = Sun; num <= Neptune; num++)
    {
        SolarSystemObject solarSystemObject = Ephemeris::solarSystemObjectAtDateAndTime((SolarSystemObjectIndex)num, day, month, year, hour, minute, second);
    }
    float elapsedTime = ((float)millis() - startTime) / (float)1000;

    Serial.print("Elapsed time: ");
    Serial.print(elapsedTime);
    Serial.println("s");

    Serial.println("_____________________________________");
    Serial.println("Testing coordinates transformations:");

    EquatorialCoordinates polarStarEqCoord;
    polarStarEqCoord.ra = Ephemeris::hoursMinutesSecondsToFloatingHours(2, 31, 49);       // 2h31m49s
    polarStarEqCoord.dec = Ephemeris::degreesMinutesSecondsToFloatingDegrees(89, 15, 51); // +89° 15′ 51″
    printEquatorialCoordinates(polarStarEqCoord);

    Serial.println("Convert RA/Dec to Alt/Az:");
    HorizontalCoordinates polarStarHCoord = Ephemeris::equatorialToHorizontalCoordinatesAtDateAndTime(polarStarEqCoord,
                                                                                                      day, month, year,
                                                                                                      hour, minute, second);
    printHorizontalCoordinates(polarStarHCoord);

    Serial.println("Convert Alt/Az back to RA/Dec:");
    polarStarEqCoord = Ephemeris::horizontalToEquatorialCoordinatesAtDateAndTime(polarStarHCoord,
                                                                                 day, month, year,
                                                                                 hour, minute, second);
    printEquatorialCoordinates(polarStarEqCoord);

    return;
}