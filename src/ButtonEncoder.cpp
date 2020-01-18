#include <ButtonEncoder.hpp>

ButtonEncoder::ButtonEncoder()
{
    encoder.setButtonHeldEnabled(true);
    encoder.setDoubleClickEnabled(true);
    // Enable the button to be on pin 0.  Normally pin 0 is not recognized as a valid pin for a button,
    // this is to maintain backward compatibility with an old version of the library
    // This version can have the button on pin zero, and this call enables the feature.
    // in this version best to use pin -1 instead of 0 to disable button functions
    // encoder.setButtonOnPinZeroEnabled(true);
}

void ButtonEncoder::ButtonEncoderSetup()
{
}

void ButtonEncoder::ButtonEncoderUpdate(int &navigated, int &pressed)
{
    //Call Service in loop becasue using timer interrupts may affect ESP8266 WIFI
    //however call no more than 1 time per millisecond to reduce encoder bounce
    static uint32_t lastService = 0;
    if (lastService + 1000 < micros())
    {
        lastService = micros();
        encoder.service();
    }

    navigated = 0;
    pressed = 0;

    value = encoder.getValue();
    //value = encoder.getValue();
    
    if (value < 0)
        navigated = -1;
    if (value > 0)
        navigated = 1;

    //   if (value != lastEncPos) {
    //     lastEncPos = value;
    //     Serial.print("Encoder Value: ");
    //     Serial.println(value);

    //   }

    ClickEncoder::Button b = encoder.getButton();
    if (b != ClickEncoder::Open)
    {
        Serial.print("Button: ");
        switch(b)
        {
            case ClickEncoder::Pressed: 
                Serial.println("ClickEncoder::Pressed"); 
                break;

            case ClickEncoder::Held: 
                Serial.println("ClickEncoder::Beeing Held"); 
                pressed = 3;
                break;

            case ClickEncoder::Released: 
                Serial.println("ClickEncoder::Released"); 
                
                break;

            case ClickEncoder::Clicked: 
                Serial.println("ClickEncoder::Clicked"); 
                pressed = 1;
                break;
            
            case ClickEncoder::DoubleClicked: 
                Serial.println("ClickEncoder::DoubleClicked");
                pressed = 2; 
                break;

            default:
                break;
        }

    }
}