
#include <SPI.h>
#include <Pixy.h>
#include <Wire.h>

Pixy pixy;
byte b = 11;

void setup() 
{
  byte b = 11;  
  Serial.begin(9600);
  Serial.print("Starting...\n");
  Wire.begin();
  Wire.beginTransmission(8);
  Wire.onRequest(requestEvent);
  //Wire.write(b);//for testing
  Wire.endTransmission(8);
  
  pixy.init();
}

void requestEvent()//might fix, its a tried 
{
  Wire.write(b);
}

void loop() 
{
  
  static int i = 0;
  uint16_t blocks;
  
  blocks = pixy.getBlocks();
  Serial.print("Cup\n");
  
  if (blocks)
  {
    //r
    i++;
    Serial.print("Blue\n");

    //This is in place so that the Arduino will take data when the Pixy is at
    //50 frames per second to prevent the Pixy from overloading
    if (i%50==0)
    {

      //this is where we want to write

    }
  }
  else
    
  {
    // return -1
    Serial.print("The\n");
  }
  
}
