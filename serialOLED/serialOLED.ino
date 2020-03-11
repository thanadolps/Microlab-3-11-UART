#include<Arduino.h>
#include<stddef.h>
#include<HardwareSerial.h>
#include<Pin.h>
#include<Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int SCREEN_WIDTH = 128; // OLED display width, in pixels
const int SCREEN_HEIGHT = 64; // OLED display height, in pixels
const int OLED_RESET = -1;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Pin POT_PIN = Pin(A2);


const float SCALING_FACTOR = 2.54;

void setup()
{
    Serial.begin(9600);
    POT_PIN.setInput();

    display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
    display.setTextSize(1);
    display.setTextColor(WHITE);
}

void loop()
{
    delay(1000);
    long val = POT_PIN.getAnalogValue();
    Serial.println(val);
}

void display_val(int val) {
    display.clearDisplay();
    display.setCursor(0,3);

    display.println(val);

    display.drawRect(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, (val * SCREEN_HEIGHT)/1023, 0xFFF);

    display.display();  
}

void serialEvent() {
    int val = Serial.parseInt();
    display_val(val);
    drain_serial();
}

void drain_serial() {
    while(Serial.available() > 0) { Serial.read(); }
}