#include <Pixy2.h>
#include <Wire.h>

Pixy2 pixy;  
int val;

void setup() 
{
  Wire.begin();//technically address doesn't need to be here, but i haven't seen it work without it. (put 8 in as input)
  //Wire.onRequest(requestEvent);
  
  pixy.init();
  pixy.setCameraBrightness(16);
}

void requestEvent()//deprecated atm
{
  //should use the value set to val right before requestEvent is called
  Wire.write(val);
}

void sendFirstX()//sends first x value over i2c address 8, done in order to better differentiate values in java
{
  Wire.beginTransmission(8);
  Wire.write(val);
  Wire.endTransmission(8);
}

void sendSecondX()//sends second x value over i2c address 9, see above
{
  Wire.beginTransmission(9);
  Wire.write(val);
  Wire.endTransmission(9);
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
      if (i % 2 == 0)
      {
        Wire.onRequest(sendFirstX);
      } else {
        Wire.onRequest(sendSecondX);
      }
    }
  }
  
  else
  {
    //will return value of -1 when nothing is recognized
    val = -1;
    Wire.onRequest(requestEvent);
  }
  
}
