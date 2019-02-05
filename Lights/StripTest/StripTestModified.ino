#include <Adafruit_NeoPixel.h>

#define PIN 6
 
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

int(EnforcerBlueNum) = 0;
int(EnforcerGoldNum) = 1;

void enforcersColorsFlashing ()
{
  EnforcerBlueNum = enforcerBlueNum;
  EnforcerGoldNum = enforcerGoldNum;
 
  strip.setPixelColor(enforcerBlueNum, 15,8,56);
  strip.setPixelColor(enforcerGoldNum, 255,208,0);
  strip.show();
  delay(500);

  strip.setPixelColor(enforcerBlueNum, 0,0,0);
  strip.setPixelColor(enforcerGoldNum, 0,0,0);

  enforcerBlueNum++
  enforcerGoldNum++  

  if (enforcerBlue == 30){

    enforcerBlue = 0;
  }

  if (enforcerGold == 30){

    enforcerGold = 0;
  }
}

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {
  // put your main code here, to run repeatedly:
       
  enforcersColorsFlashing();
}
