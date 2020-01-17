
struct Position
{
   float lon;
   float lat;
   float alt;
};

struct Time 
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
    Position getGPSPosition();
    Time getGPSTime(); // should not be void but not sure which return type it wil be.

private:



};


