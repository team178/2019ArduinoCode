#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define PIN 3
int numOfPixels = 5-9;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numOfPixels, PIN, NEO_GRB + NEO_KHZ800);
String myWord = "";
String message = "";


void setup()
{
  turnOff();//turns lights off
  Wire.begin(7); //change to 7
  Wire.onReceive(readRoborioMessage); //is essentially a definition, calls the handler to be run when the roboRIO sends a message
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(50);
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
  message = myWord;
  int counter = 0;

  turnEnforcersPattern();//default, wil run "all" the time
  if (message.equals("c")) //mainB - cargo orange flashing
  {    
    turnRGB(255, 40, 0);
  }

  if (message.equals("h")) //mainY - hatch panel yellow flashing
  {
    turnRGB(150,255,0); //hatch panel yellow
  }
  
  if (message.equals("f")) //mainX - default enforcers
  {
    turnEnforcersPlain();
  }
  
  if (message.equals("n")) //mainA - off
  {
    //turnOff();
  }  
  //turnEnforcersPlain();
  turnRGBFlash(255, 40, 0);
}


void turnOff()
{
  for (int i = 0; i <= numOfPixels; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}


void turnRGB(int R, int G, int B)
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
}

void turnRGBFlash(int R, int G, int B)
{
  //for(int count = 0; count <= 10; count++)
  //{
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
  //}
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


void turnEnforcersPattern()
{ 
    // enforcers Colors
    for (int i = numOfPixels; i > 0; i--)
    {
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


void turnEnforcersPlain()
{
  for(int i = 0; i <= numOfPixels; i = i+2)
  {
    strip.setPixelColor(i, 229, 187, 0);
    strip.show();
    strip.setPixelColor(i+1, 7, 16, 99);
    strip.show();
  }
}
