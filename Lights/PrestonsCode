#include <Adafruit_NeoPixel.h>

#define PIN 3
 
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(38, PIN, NEO_GRB + NEO_KHZ800);

int(enforcerBlueNum) = 0;
int(enforcerGoldNum) = 1;
int(hi) = 2;
int(green) = 3;
int(blue) = 4;
int(purple) = 5;
int(lightPurple) = 6;

void enforcersColorsFlashing ()
{
  //enforcerBlueNum = enforcerBlueNum;
  //enforcerGoldNum = enforcerGoldNum;

  strip.show();
  for x range in
  delay(1000);
  strip.setPixelColor(enforcerBlueNnm, 0,0,0);
  delay(1000);
  strip.setPixelColor(enforcerBlueNum, 255,0,0);
  strip.setPixelColor(enforcerGoldNum, 255,102,0);
  strip.setPixelColor(hi, 255,255,0);
  strip.setPixelColor(green,0,255,0);
  strip.setPixelColor(blue,0,0,255);
  strip.setPixelColor(purple,75,0,130);
  strip.setPixelColor(lightPurple,148,0,211);

  enforcerBlueNum+= 7;
  enforcerGoldNum+=7; 
  hi+=7;  
  green+=7;
  blue+=7;
  purple+=7;
  lightPurple+=7;

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
