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
  //turnOff();
  //when the roborio sends a message from an input, it will initiate the correct if statement
  String message = myWord;

  
  if (message.equals("c"))
  {
    //cargo
    turnRGBFlash(255, 40, 0); //cargo orange; press left bumper
  }

  if (message.equals("h"))
  {
    //hatch panel
    turnRGBFlash(175,75,0); //hatch panel yellow; press right bumper
  }

  if (message.equals("r"))
  {
    turnRGBBounce(255,10,0);//red alliance
  }

  if (message.equals("b"))
  {
    turnRGBBounce(5,40,132); //blue alliance
  }

  if (message.equals("f"))
  {
    turnEnforcers();
  }

  if (message.equals("s"))
  {
    turnFirst();
  }

  if (message.equals("y"))
  {
    turnRainbow();
  }
  
  
  
  //turnRGBFlash(255, 60, 0); //orange
  //turnRGBBounce(255, 60, 0); //orange
  //turnRGBBounce(200,125,0); //yellow 
  //turnRGBBounce(0, 0, 255); //blue
  //turnRGBBounce(255,10,0);//red alliance
  //turnRGBBounce(5,40,132); //blue alliance
  //turnFirst();
  //turnDeepSpace();
  //turnPolar();
  //turnRainbow();
  //turnBlueAndGold();
  //turnEnforcers();
}

if (message.equals("n"))
{
  turnoff():
}


void turnOff()
{
  for (int i = 0; i <= 59; i++) {
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
  for(int i=0; i <= 59; i++)
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
  for(int i=0 ; i <= 59; i++)
  {
    strip.setPixelColor(i,R,G,B);
    strip.show();
    delay(50);
    strip.show();
  }
  for(int i=59; i >= 0; i--)
  {
    strip.setPixelColor(i,0,0,0);
    strip.show();
    delay(50);
    strip.show();
  }
}


void turnEnforcers()
{
  // enforcers Colors:
  for (int i = 59; i > 0; i--) {
    for (int x = 0; x <= 59; x += 4) {
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


void turnFirst() 
{
  for (int i=59; i > 0; i--){
    for(int x= 0; x <=59; x+=4){
      strip.setPixelColor(i+x,237,28,36);
      strip.setPixelColor(i+(x-1),0,101,179);
      strip.setPixelColor(i+(x-2),35,31,32);
      strip.setPixelColor(i+(x-3),167,169,172);
  
      strip.setPixelColor(i-x,237,28,36);
      strip.setPixelColor(i-(x+1),0,101,179);
      strip.setPixelColor(i-(x+2),35,31,32);
      strip.setPixelColor(i-(x+3),167,169,172);
    } 
    strip.show();
    delay(100);
  }
}


void turnDeepSpace()  
{
  for (int i=59; i > 0; i--){
    for(int x= 0; x <=59; x+=4){
      strip.setPixelColor(i+x,239,120,34);
      strip.setPixelColor(i+(x-1),148,148,146);
      //strip.setPixelColor(i+(x-2),35,31,32);
      //strip.setPixelColor(i+(x-3),167,169,172);
  
      strip.setPixelColor(i-x,239,120,34);
      strip.setPixelColor(i-(x+1),148,148,148);
      //strip.setPixelColor(i-(x+2),35,31,32);
      //strip.setPixelColor(i-(x+3),167,169,172);
    } 
    strip.show();
    delay(100);
  }
}


void turnPolar() {
  for (int i=59; i > 0; i--){
    for(int x= 0; x <=59; x+=3){
      strip.setPixelColor(i+x,190,0,90);
      strip.setPixelColor(i+(x-1),60,49,110);
      strip.setPixelColor(i+(x-2),0,26,110);
  
      strip.setPixelColor(i-x,190,0,90);
      strip.setPixelColor(i-(x+1),60,49,110);
      strip.setPixelColor(i-(x+2),0,26,110);
    } 
    strip.show();
    delay(100);
  }
}

void turnRainbow() {
    for (int i=59; i > 0; i--){
      for(int x= 0; x <=59; x+=6){
        strip.setPixelColor(i+x,255,0,0);
        strip.setPixelColor(i+(x-1),255,165,0);
        strip.setPixelColor(i+(x-2),255,255,0);
        strip.setPixelColor(i+(x-3),0,255,0);
        strip.setPixelColor(i+(x-4),0,0,255);
        strip.setPixelColor(i+(x-5),255,0,255);
        strip.setPixelColor(i-x,255,0,0);
        strip.setPixelColor(i-(x+1),255,165,0);
        strip.setPixelColor(i-(x+2),255,255,0);
        strip.setPixelColor(i-(x+3),0,255,0);
        strip.setPixelColor(i-(x+4),0,0,255);
        strip.setPixelColor(i-(x+5),255,0,255);
      } 
      strip.show();
      delay(100);    
  }
}
