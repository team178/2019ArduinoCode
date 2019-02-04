#include <Adafruit_NeoPixel.h>
#include <Wire.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(36, 7, NEO_GRB + NEO_KHZ800);
String myWord = "";

void setup() {
  Wire.begin(8);
  Wire.onReceive(readRoborioMessage);
  Serial.begin(9600);
}

void readRoborioMessage(int howMany) 
{
  myWord = "";
  while (0 < Wire.available()) {
    char c = Wire.read();
    myWord = myWord + c;
  }
  
  //Serial.println("hello");
  //Serial.println(myWord);
}

void loop() 
{
  String message = myWord;
  if(message.equals("test"))
  {
    turnGreen();
    Serial.println("it works");
  }

}

void turnGreen()
{
  strip.begin();
   for (int i=36; i > 0; i--){
    for(int x= 0; x <=36; x+=3){
      strip.setPixelColor(i+x,0,255,0);
      strip.setPixelColor(i+(x-1),0,100,0);
      strip.setPixelColor(i+(x-2),100,255,0);
      strip.setPixelColor(i-x,0,255,0);
      strip.setPixelColor(i-(x+1),0,100,0);
      strip.setPixelColor(i-(x+2),100,255,0);
    } 

    strip.show();
    delay(100);
   }
}
