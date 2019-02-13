#include <Pixy2.h>
#include <Wire.h>

Pixy2 pixy;  
int val;

void setup() 
{
  Wire.begin(8);
  //Wire.onRequest(requestEvent);
  
  pixy.init();
  pixy.setCameraBrightness(16);
}

void requestEvent()
{
  //should use the value set to val right before requestEvent is called
  Wire.write(val);
}

void loop() 
{ 
  //Pixy seems to overload at fast speeds, implementing a delay
  delay(20);

  //counter variable
  int i;

  //get an array of all objects pixy is currently seeing
  //ccc stands for color connected components
  pixy.ccc.getBlocks();
  
  //will only run if blocks has values
  if (pixy.ccc.numBlocks)
  {
    for (i = 0; i < pixy.ccc.numBlocks; i++)
    {
      val = pixy.ccc.blocks[i].m_x;
      //m_x is the variable to represent x value from 0 to 315
      Wire.onRequest(requestEvent);
    }
  }
  
  else
  {
    //will return value of -1 when nothing is recognized
    val = -1;
    Wire.onRequest(requestEvent);
  }
  
}
