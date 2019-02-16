#include <Pixy2.h>
#include <Wire.h>

Pixy2 pixy;  
int32_t val;//used to take data from pixy
byte valArray[4];//to send to roboRIO

void setup() 
{
  Wire.begin(8);//should correspond to RobotMap.pixyAddress
  Serial.begin(115200);
  Serial.println("Starting...");
  Wire.onRequest(requestEvent);//is essentially a definition, what to do when the roboRIO asks for data
  pixy.init();
  pixy.setCameraBrightness(16);
}

void requestEvent()//handler for onRequest method
{
  Wire.write(valArray, 4);//sending four bytes, two bytes for each 
}

void loop() 
{ 
  //Pixy seems to overload at fast speeds, implementing a delay
  delay(20);

  //get an array of all objects pixy is currently seeing
  //ccc stands for color connected components
  //will only run if blocks has values
  if (pixy.ccc.getBlocks() > 0)//updates the blocks[] with the current objects the pixy, returning if it worked (value higher than 0)
  {
        //sends first x value 
        val = pixy.ccc.blocks[0].m_x;//takes x value from 0th position in array from getBlocks();
        pixy.ccc.blocks[0].print();//prints data about the block, like it literally prints all of the info stored
        valArray[1] = val & 0xFF;//shifts byte over, then bitwise and, essentially to be able to send the values
        valArray[0] = (val >> 8) & 0xFF;
        Serial.print(valArray[0]);
        Serial.print(valArray[1]);
        Serial.print(" is first x value");
        Serial.println("val 1 = " + val);

        //sends second x value 
        val = pixy.ccc.blocks[1].m_x;
        pixy.ccc.blocks[1].print();//see above
        valArray[3] = val & 0xFF;//same as above
        valArray[2] = (val >> 8) & 0xFF;
        Serial.print(valArray[2]);
        Serial.print(valArray[3]);
        Serial.print(" is second x value");
        Serial.println("val 2 = " + val);
  }
  
  else
  {
    val = 0;//if no objects are recongnized, sends zero 
    valArray[1] = val & 0xFF;//same as above 
    valArray[0] = (val >> 8) & 0xFF;
  }
  
}
