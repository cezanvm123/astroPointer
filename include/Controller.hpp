#include <Arduino.h>

enum MainState { STARTUP, NORMAL_OPERATION};

enum StartupState { STEP_CALIBRATION, GPS_SEARCHING};
enum OperationState {NORMAL_TRACKING, CHANGING};

enum GPSState { VALID, INVALID_SHORT, INVALD};

class Controller 
{

public:
    Controller();
    void ControllerUpdate();

    void changeMainState(MainState state);
    void changeStartupState(StartupState state);
    void changeOperationState (OperationState state);

    void changeGPSState(GPSState state);

private:


};