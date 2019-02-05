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

int(orangeNum) = 0;
int(yellowNum) = 0;

void orangeFlashing()
{
 
  strip.setPixelColor(orangeNum, 255, 60, 0);
  
  strip.show();
  delay(50);


  orangeNum = orangeNum + 1;
}

void yellowFlashing()
{
  strip.setPixelColor(yellowNum, 200, 125, 0);

  strip.show();
  delay(50);

  yellowNum = yellowNum + 1;
}


void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {
  // put your main code here, to run repeatedly:
  orangeNum = 0;
  yellowNum = 0;
  orangeFlashing();
  for (int orangeNum=0; orangeNum <= 30; orangeNum++)
  {
    orangeFlashing();
  }
  yellowFlashing();
  for (int yellowNum=0; yellowNum <= 30; yellowNum++)
  {
    yellowFlashing();
  }
}
