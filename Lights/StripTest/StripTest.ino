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

int(enforcerBlue) = 0;
int(enforcerGold) = 1;
int(green) = 2;

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {
  // put your main code here, to run repeatedly:
  enforcerBlue = enforcerBlue;
  enforcerGold = enforcerGold;
  green = green;
  
  strip.setPixelColor(enforcerBlue, 15,8,56);
  strip.setPixelColor(enforcerGold, 255,208,0);
  strip.setPixelColor(green, 0, 255, 0);
  strip.show();
  delay(500);

  strip.setPixelColor(enforcerBlue, 0,0,0);
  strip.setPixelColor(enforcerGold, 0,0,0);
  strip.setPixelColor(green, 0,0,0);

  enforcerBlue = enforcerBlue + 1;
  enforcerGold = enforcerGold + 1;
  green = green + 1;

  if (enforcerBlue == 12){

    enforcerBlue = 0;
  }

  if (enforcerGold == 12){

    enforcerGold = 0;
  }

     if (green == 12){

    green = 0;
  }
  
}
