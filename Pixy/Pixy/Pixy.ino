
#include <SPI.h>
#include <Pixy.h>
#include <Wire.h>

Pixy pixy;


void setup() 
{
  Serial.begin(9600);
  Serial.print("Starting...\n");
  
  pixy.init();
}

void loop() 
{
  Wire.write(1);
  
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
      pixy.blocks[0].x;
      Serial.print("Yash\n");
      //this is where we want to write
      pixy.blocks[1].x;
      Serial.print("I don't know\n");
      //this is where we want to write
    }
    
  }
  else
  {
    // return -1
    Serial.print("The\n");
  }
  
}
