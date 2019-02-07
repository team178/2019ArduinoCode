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
String myWord = "";
boolean isON;

void setup() {
  // put your setup code here, to run once:
  turnOff();
  Wire.begin(8);
  Wire.onReceive(readRoborioMessage);
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.println("Starting...");
  isON = false;
}

void readRoborioMessage() {
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
  // put your main code here, to run repeatedly;
  //turnOff();

  String message = myWord;
  if (message.equals("o"))
  {
    if (isON) {
      turnOff();
      isON = false;
    } else {
      turnRGBFlash(255, 60, 0); //orange
      Serial.println("orange");
    }
  }
  else if (message.equals("e"))
  {
    if (isON) {
      Serial.println("yeet");
      turnOff();
      isON = false;
    } else {
      turnEnforcers();
      Serial.println("enforcers");
    }
  }
  //turnRGBFlash(255, 60, 0);
  //turnRGBBounce(255, 60, 0); //orange
  //turnRGBBounce(200,125,0); //yellow 
  //turnRGBBounce(0, 0, 255); //blue
  //turnRGBBounce(255,10,0);//red alliance
  //turnRGBBounce(5,40,132); //blue alliance
  //turnFirst();
  //turnDeepSpace();
}

void turnOff() {
  for (int i = 0; i <= 30; i++) {
    strip.setPixelColor(i, 0, 0, 0);
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


void turnRGBFlash(int R, int G, int B)
{
  //int i = 0;
  int numbers[3];
  numbers[3] = new int[3];
  numbers[0] = R;
  numbers[1] = G;
  numbers[2] = B;
  //isON = true;

  
 /* if(digitalRead(PIN) == LOW)
  {
      if (message == 0) 
    {
      message = 255;
    }
    else
    {
      message = 0;
    }
  
    if(message > 0)
    {
      //for(int i=0; i <= 30; i++)
      //{
        strip.setPixelColor(0,R,G,B);
        strip.show();
      //}
    }
  }
  */
}



void turnRGBBounce(int R, int G, int B)
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
    strip.show();
  }
  //strip.show();
  for(int i=30; i >= 0; i--)
  {
    strip.setPixelColor(i,0,0,0);
    strip.show();
    delay(50);
    strip.show();
  }
  //strip.show();
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


void turnFirst() 
{
  for (int i=30; i > 0; i--){
    for(int x= 0; x <=36; x+=4){
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
  for (int i=30; i > 0; i--){
    for(int x= 0; x <=36; x+=4){
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
