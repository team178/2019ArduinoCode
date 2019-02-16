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
Adafruit_NeoPixel strip = Adafruit_NeoPixel(59, PIN, NEO_GRB + NEO_KHZ800);
String myWord = "";
int numOfPixels = 59;

void setup()
{
  turnOff();
  Wire.begin(7);
  Wire.onReceive(readRoborioMessage); 
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.println("Starting...");
}

void readRoborioMessage()
{
  //used for communication between roborio and arduino
  myWord = "";
  while (0 < Wire.available()) {
    char c = Wire.read();
    myWord = myWord + c;
  }
  Serial.println(myWord);
  //go to Tools --> Serial Monitor or press Ctrl+Shift+M
}

void loop()
{
  //when the roborio sends a message from an input,
  //it will initiate the correct if statement
  String message = myWord;

  
  if (message.equals("c")) //mainB - cargo orange flashing
  {
    turnRGBFlash(255, 40, 0);
  }

  if (message.equals("h")) //mainY - hatch panel yellow flashing
  {
    turnRGBFlash(175,75,0); //hatch panel yellow
  }
  
  if (message.equals("f")) //mainX - default enforcers
  {
    turnEnforcers();
  }
  
  if (message.equals("n")) //mainA - off
  {
    turnOff();
  }  
}


void turnOff()
{
  for (int i = 0; i <= numOfPixels; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}


void turnRGBFlash(int R, int G, int B)
{
  int i = 0;
  int numbers[3];
  numbers[3] = new int[3];
  numbers[0] = R;
  numbers[1] = G;
  numbers[2] = B;
  for(int i = 0; i <= numOfPixels; i++)
    {
      strip.setPixelColor(i,R,G,B);
      strip.show();
    }
  delay(250);
  turnOff();
  delay(250);
}



void turnRGBBounce(int R, int G, int B)
{
  int numbers[3];
  numbers[3] = new int[3];
  numbers[0] = R;
  numbers[1] = G;
  numbers[2] = B;
  for(int i = 0; i <= numOfPixels; i++)
  {
    strip.setPixelColor(i,R,G,B);
    strip.show();
    delay(50);
    strip.show();
  }
  for(int i = numOfPixels; i >= 0; i--)
  {
    strip.setPixelColor(i,0,0,0);
    strip.show();
    delay(50);
    strip.show();
  }
}


void turnEnforcers()
{
  // enforcers Colors
  for (int i = numOfPixels; i > 0; i--) {
    for (int x = 0; x <= numOfPixels; x += 4) {
      strip.setPixelColor(i + x, 229, 187, 0);
      //strip.setPixelColor(i + (x - 1), 229, 187, 0);
      strip.setPixelColor(i + (x - 2), 7, 16, 79);
      //strip.setPixelColor(i + (x - 3), 7, 16, 79);

      strip.setPixelColor(i - x, 229, 187, 0);
      //strip.setPixelColor(i - (x + 1), 229, 187, 0);
      strip.setPixelColor(i - (x + 2), 7, 16, 99);
      //strip.setPixelColor(i - (x + 3), 7, 16, 99);
    }

    strip.show();
    delay(100);
  }
}
