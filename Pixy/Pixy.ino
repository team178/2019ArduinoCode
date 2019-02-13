//this is for pixy the FIRST. DOES NOT WORK WITH PIXY2


#include <SPI.h>
#include <Pixy.h>
#include <Wire.h>

Pixy pixy;  
int val;

void setup() 
{
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  
  pixy.init();
}

void requestEvent()
{
  Wire.write(val);
}

void loop() 
{
  
  static int i = 0;
  uint16_t blocks;
  
  blocks = pixy.getBlocks();
  Serial.print("Cup\n");
  
  if (blocks)
  {
    i++;
    Serial.print("Blue\n");

    //This is in place so that the Arduino will take data when the Pixy is at
    //50 frames per second to prevent the Pixy from overloading
    if (i%50==0)
    {
      val = pixy.blocks[0].x;
      val = pixy.blocks[1].x;
    }
  }
  else
    
  {
    val = -1;
  }
  
}
