#include <Arduino.h>
#include <ClickEncoder.h>

class ButtonEncoder 
{
public:
    ButtonEncoder();
    void ButtonEncoderSetup();

    /*
    *   sets navigated according to the movement 
    *   1 = moved anti-clockwise* 
    *   0 = did not move 
    *   -1 = moved clockwise*
    * 
    *   *might swap these 
    * 
    *   sets pressed according to the press 
    *   0 = did not press 
    *   1 = button is pressed 
    *   2 = button is double pressed 
    *   3 = button was held 
    */

    void ButtonEncoderUpdate(int & navigated, int & pressed);  

private:
    //Encoder myEnc;
    
    int8_t  pinA = 2;
    int8_t  pinB = 4;
    int8_t  pinSW = 15;
    int8_t  steps = 4;

    ClickEncoder encoder = ClickEncoder(pinA, pinB, pinSW, steps);

    int16_t value = 0;
    int16_t lastEncPos = 0;


};
