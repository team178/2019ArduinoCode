#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define PIN 3
int numOfPixels = 59;

uint32_t BLUE1;
uint32_t BLUE2;
uint32_t BLUE3;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numOfPixels, PIN, NEO_GRB + NEO_KHZ800);
char message;
int frame = 0;



void setup()
{
  BLUE1 = strip.Color(0,0,255);
  turnOff();//turns lights off
  Wire.begin(7); //change to 7
  Wire.onReceive(readRoborioMessage); //is essentially a definition, calls the handler to be run when the roboRIO sends a message
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
  Serial.println("Starting...");
  strip.setPixelColor(1, BLUE1);
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
    turnEnforcers();
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
    turnChaseRed();
  }
  frame++;
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

void turnEnforcers()
{
  for (int i = numOfPixels; i >= 0; i--){
    if (frame % 2 == 0){
      if (i % 3 == 0){
        strip.setPixelColor(i,229, 187, 0);
      }
      if (i % 3 == 1) {
        strip.setPixelColor(i,7, 16, 99); 
      }
      if ( i % 3 == 2){
        strip.setPixelColor(i,229, 187, 0);
      }  
    } else if (frame % 2 == 1) {
      if (i % 3 == 0){
        strip.setPixelColor(i,7, 16, 99);      
      }
      if (i % 3 == 1) {
        strip.setPixelColor(i,229, 187, 0);
      }
      if ( i % 3 == 2){
        strip.setPixelColor(i,7, 16, 99); 
      }   
    }
  }
    strip.show();
    delay(100);
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
   for (int i = numOfPixels; i >= 0; i--){
    if (frame % 2 == 0){
      if (i % 3 == 0){
        strip.setPixelColor(i,255,0,0);
      }
      if (i % 3 == 1) {
        strip.setPixelColor(i,255,50,0); 
      }
      if ( i % 3 == 2){
        strip.setPixelColor(i,178,0,0);
      }  
    } else if (frame % 2 == 1) {
      if (i % 3 == 0){
        strip.setPixelColor(i,178,0,0);      
      }
      if (i % 3 == 1) {
        strip.setPixelColor(i,255,0,0);
      }
      if ( i % 3 == 2){
        strip.setPixelColor(i,255,50,0); 
      }   
    }
  }
    strip.show();
    delay(100);
}


void turnChaseBlue()
{
  for (int i = numOfPixels; i >= 0; i--){
    if (frame % 2 == 0){
      if (i % 3 == 0){
        strip.setPixelColor(i,0,0,255);
      }
      if (i % 3 == 1) {
        strip.setPixelColor(i,0,200,255); 
      }
      if ( i % 3 == 2){
        strip.setPixelColor(i,0,0,178);
      }  
    } else if (frame % 2 == 1) {
      if (i % 3 == 0){
        strip.setPixelColor(i,0,0,178);        
      }
      if (i % 3 == 1) {
        strip.setPixelColor(i,0,0,255);
      }
      if ( i % 3 == 2){
        strip.setPixelColor(i,0,200,255); 
      }   
    }
  }
    strip.show();
    delay(100);
}
