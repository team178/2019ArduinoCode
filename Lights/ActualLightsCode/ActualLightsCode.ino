#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define PIN 3
int numOfPixels = 59;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numOfPixels, PIN, NEO_GRB + NEO_KHZ800);
char message;

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
  if (0 < Wire.available()) {
    message = Wire.read();
  }
  Serial.println(message);
  //go to Tools --> Serial Monitor or press Ctrl+Shift+M
}

void loop()
{
  //when the roborio sends a message from an input,
  //it will initiate the correct if statement
  
  if (message == 'c') //cargo orange flashing to signal we are ready to load cargo; happens when gate open
  {    
    turnRGBFlash(255, 40, 0, 'c');
  }

  if (message == 'h') //button5 - hatch panel yellow flashing
  {
    turnRGBFlash(229, 187, 0,'h'); //hatch panel yellow
  }
  
  if (message == 'f') //button7 - default enforcers
  {
    turnEnforcersPlain();
  }

  if (message == 'a') //button10 - align green light
  {
    turnGreen();
    //turnRGBSolid(0,255,0,'a');
  }

  if (message == 'x') //turn red to signal that we can't align
  {
    turnRed();
    //turnRGBSolid(255,0,0,'x');
  }

  if (message == 'o') //button 6 - turn solid orange to signal that we are getting cargo
  {
    turnOrange();
    //turnRGBSolid(255, 40, 0, 'o');
  }

  if (message == 'r') //button8 - rainbow colors
  {
    turnRainbowPlain();
  }
  
  if (message == 'n') //button9 - off
  {
    turnOff();
  }

  if (message == 'd') //alliance color - blue 
  {
    turnChaseBlue();
  }

  if(message == 's')//alliance color - red
  {
    turnSkipRed();
  }
}


void turnOff()
{
  for (int i = 0; i <= numOfPixels; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}

void turnRGBSolid(int R, int G, int B, char sent)
{
  if(message != sent)
  {
    return;
  }
  int i = 0;
  int numbers[3];
  numbers[3] = new int[3];
  numbers[0] = R;
  numbers[1] = G;
  numbers[2] = B;
  for(int i = 0; i <= numOfPixels; i++)
    {
      strip.setPixelColor(i,R,G,B);        
    }
  strip.show();
}

void turnRGBFlash(int R, int G, int B, char sent)
{
    if(message != sent)
    {
      return;
    }
    int i = 0;
    int numbers[3];
    numbers[3] = new int[3];
    numbers[0] = R;
    numbers[1] = G;
    numbers[2] = B;
    for(int i = 0; i <= numOfPixels; i++)
      {
        strip.setPixelColor(i,R,G,B);        
      }
    strip.show();
    delay(250);
    turnOff();
    delay(250);
}

void turnEnforcersPlain()
{
  for(int i = 0; i <= numOfPixels; i = i+2)
  {
    strip.setPixelColor(i, 229, 187, 0);
    strip.setPixelColor(i+1, 7, 16, 99);
  }
  strip.show();
}

void turnRainbowPlain()
{
  for(int i = 0; i <= numOfPixels; i = i+6) {
      strip.setPixelColor(i, 255, 0, 0);
      strip.setPixelColor(i+1, 255, 40, 0);
      strip.setPixelColor(i+2, 255, 255, 0);
      strip.setPixelColor(i+3, 0, 255, 0);
      strip.setPixelColor(i+4, 0, 0, 255);
      strip.setPixelColor(i+5, 128, 0, 255);
  }
  strip.show();
}

void turnGreen()
{
  for(int i = 0; i <= numOfPixels; i++)
  {
    strip.setPixelColor(i, 0, 255, 0);
  }
  strip.show();
}

void turnRed()
{
  for(int i = 0; i <= numOfPixels; i++)
  {
    strip.setPixelColor(i, 255, 0, 0);
  }
  strip.show();
}

void turnOrange()
{
  for(int i = 0; i <= numOfPixels; i++)
  {
    strip.setPixelColor(i, 255, 40, 0);
  }
  strip.show();
}

void turnBlue()
{
  for(int i = 0; i <= numOfPixels; i++)
   {
    strip.setPixelColor(i, 0, 0, 255);
  }
  strip.show();
}

void turnChaseRed()
{
   for (int i=numOfPixels; i > 0; i--){
    for(int x= 0; x <=numOfPixels; x+=5){
      strip.setPixelColor(i+x,255,0,0);
      strip.setPixelColor(i+(x-1),255,11,0);
      strip.setPixelColor(i+(x-2),255,22,0);
      strip.setPixelColor(i+(x-3),255,44,0);
      strip.setPixelColor(i+(x-4),255,69,0);   
  
      strip.setPixelColor(i-x,255,0,0);
      strip.setPixelColor(i-(x+1),255,11,0);
      strip.setPixelColor(i-(x+2),255,22,0);
      strip.setPixelColor(i-(x+3),255,44,0);
      strip.setPixelColor(i-(x+4),255,69,0);
      
    } 
    strip.show();
    delay(100);
  }
}


void turnChaseBlue()
{
  for (int i=numOfPixels; i > 0; i--){
    for(int x= 0; x <=numOfPixels; x+=3){
      strip.setPixelColor(i+x,0,0,255);
      strip.setPixelColor(i+(x-1),0,0,255);
      strip.setPixelColor(i+(x-2),0,200,255);
  
      strip.setPixelColor(i-x,0,0,255);
      strip.setPixelColor(i-(x+1),0,0,255);
      strip.setPixelColor(i-(x+2),0,200,255);
    } 
    strip.show();
    delay(100);
  }
}

void turnSkipRed()
{
    for(int i=10; i > 0; i--){
        for(int x= 0; x <= 37; x+=4){
          strip.setPixelColor(i+x,255,0,0);//red
          strip.setPixelColor(i+(x-1),0,0,0);//blank
          strip.setPixelColor(i+(x-2),255,0,0);//red
          strip.setPixelColor(i+(x-3),0,0,0);//blank
          
          strip.setPixelColor(i-x,255,0,0);//red
          strip.setPixelColor(i+(x-1),0,0,0);//blank
          strip.setPixelColor(i-(x+2),255,20,0);//red
          strip.setPixelColor(i+(x-3),0,0,0);//blank
          strip.show();
          delay(100);
        }
    }
}
