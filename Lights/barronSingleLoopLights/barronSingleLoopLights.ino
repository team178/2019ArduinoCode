#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

int lightNum = 0;
int cycleCount = 0;
char letter;
uint32_t c1;
uint32_t c2;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRBW + NEO_KHZ800);
#define RED strip.Color(255,0,0,0);
#define BLUE strip.Color(0,0,255,0);
#define YELLOW strip.Color(255,252,0,0);
#define ORANGE strip.Color(255,136,93,127);



void setup()
{
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'

  // open the serial port:
  Serial.begin(9600);
}

void loop()
{
  letter = (char)Serial.read();
  
  if(letter == 'r')
    {
      c1 = RED;
      c2 = RED;
      lightNum = 0;
    }
  else if(letter == 'b')
    {
      c1 = BLUE;
      c2 = BLUE;
      lightNum = 0;
    }
  else if(letter == 'f')
    {
      c1 = BLUE;
      c2 = YELLOW;
      lightNum = 0;
    }
  else if(letter == 'o')
    {
      c1 = ORANGE;
      c2 = ORANGE;
      lightNum = 0;
    }

  strip.setPixelColor(lightNum,c1);
  strip.setPixelColor(lightNum+1,c2);
  lightNum+=2;
  if(lightNum == 24)
    {
      lightNum = 0;
      strip.show();
    }
  delay(250);
}
