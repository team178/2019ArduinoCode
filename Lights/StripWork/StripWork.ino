#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);




void setup() {
  // put your setup code here, to run once:
  Wire.begin(8);
  //Wire.onReceive(readRoborioMessage);
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.print("Starting...\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  //turnEnforcers();
  //orangeFlashing();
  //yellowFlashing();
  //blueFlashing();
  //turnOff();
  turnRGBFlashing(255, 60, 0); //orange
  turnRGBFlashing(200,125,0); //yellow
  turnRGBFlashing(0, 0, 255); //blue
}



void turnOff() {
  for (int i = 0; i <= 30; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}


void orangeFlashing()
{
  for (int i = 0; i <= 30; i++)
  {
    strip.setPixelColor(i, 255, 60, 0);
    strip.show();
    delay(50);
  }
  strip.show();
}


void yellowFlashing()
{
  for (int i = 0; i <= 30; i++)
  {
    strip.setPixelColor(i, 200,125,0);
    strip.show();
    delay(50);
  }
  strip.show();
}


void blueFlashing()
{
  for(int i=0 ; i <= 30; i++)
  {
    strip.setPixelColor(i, 0,0,255);
    strip.show();
    delay(50);  
  }
  strip.show();
}


void turnRGB(int R, int G, int B)
{
  int numbers[3];
  numbers[3] = new int[3];
  numbers[0] = R;
  numbers[1] = G;
  numbers[2] = B;
  strip.setPixelColor(0,R,G,B);
  strip.show();
}


void turnRGBFlashing(int R, int G, int B)
{
  int numbers[3];
  numbers[3] = new int[3];
  numbers[0] = R;
  numbers[1] = G;
  numbers[2] = B;
  for(int i=0 ; i <= 30; i++)
  {
    strip.setPixelColor(i,R,G,B);
    strip.show();
    delay(50);  
  }
  strip.show();
}


void turnEnforcers() {
  // enforcers Colors:
  for (int i = 36; i > 0; i--) {
    for (int x = 0; x <= 30; x += 4) {
      strip.setPixelColor(i + x, 229, 187, 0);
      strip.setPixelColor(i + (x - 1), 229, 187, 0);
      strip.setPixelColor(i + (x - 2), 7, 16, 79);
      strip.setPixelColor(i + (x - 3), 7, 16, 79);

      strip.setPixelColor(i - x, 229, 187, 0);
      strip.setPixelColor(i - (x + 1), 229, 187, 0);
      strip.setPixelColor(i - (x + 2), 7, 16, 99);
      strip.setPixelColor(i - (x + 3), 7, 16, 99);
    }

    strip.show();
    delay(100);
  }
}
