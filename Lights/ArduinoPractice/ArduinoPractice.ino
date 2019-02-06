#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);
int location=0;
void setup()
{
strip.begin();
strip.show();

}


void loop(){


strip.setPixelColor(location,255,255,255);
strip.show();
delay(100);
location++;
 
 if(location==30) {
    location = 0;
    for (int location = 0; location <= 30; location++) {
    strip.setPixelColor(location, 0, 0, 0);
  }
  strip.show();
  } 
}
