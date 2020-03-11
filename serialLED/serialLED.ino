#include<Arduino.h>
#include<stddef.h>
#include<HardwareSerial.h>
#include<Pin.h>

Pin POT_PIN = Pin(A2);
Pin LED_1 = Pin(5);
Pin LED_2 = Pin(6);


const float SCALING_FACTOR = 2.54;

void setup()
{
    Serial.begin(9600);
    POT_PIN.setInput();
    LED_1.setOutput();
    LED_2.setOutput()
}

void loop()
{
    delay(1000);
}

void serialEvent() {
    if(Serial.read() != 'L')
    {
        Serial.println("Can you just Input Correctly?");
        drain_serial();
        return;
    }
    u8 id = Serial.parseInt();

    if(Serial.read() != 'B')
    {
        Serial.println("Can you just Input Correctly?");
        drain_serial();
        return;
    }
    u8 brightness = (u8)(Serial.parseFloat() * SCALING_FACTOR);
    
    drain_serial();

    switch (id)
    {
    case 1:
        LED_1.setDutyCycle(brightness);
        break;
    case 2: 
        LED_2.setDutyCycle(brightness);
        break;
    default:
        Serial.println("Can you just Input Correctly?");
        break;
    }  
}

void drain_serial() {
    while(Serial.available()) { Serial.read(); }
}