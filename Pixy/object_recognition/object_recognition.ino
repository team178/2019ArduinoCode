#include <Pixy2.h>
#include <Wire.h>

Pixy2 pixy;  
int32_t val;//used to take data from pixy
byte valArray[6];//to send to roboRIO

void setup() 
{
  Wire.begin(8);//should correspond to RobotMap.pixyAddress
  Serial.begin(115200);
  Serial.println("Starting...");
  Wire.onRequest(requestEvent);//is essentially a definition, what to do when the roboRIO asks for data
  pixy.init();
  pixy.setCameraBrightness(10);
}

void requestEvent()//handler for onRequest method
{
  Wire.write(valArray, 6);//sending six bytes, two bytes for each 
}

void loop() 
{ 
  //Pixy seems to overload at fast speeds, implementing a delay
  delay(20);

  //get an array of all objects pixy is currently seeing
  //ccc stands for color connected components
  //will only run if blocks has values
  pixy.ccc.blocks[0].print();
  char c1 = Serial.read();
  pixy.ccc.blocks[1].print();
  char c2 = Serial.read();
  int v = 0;
  if (c1 == 'e' || c2 == 'e') {
    v = 0;
    valArray[5] = v & 0xFF;
    valArray[4] = (v >> 8) & 0xFF;
  } else {
    v = 1 + pixy.ccc.getBlocks();
    valArray[5] = v & 0xFF;
    valArray[4] = (v >> 8) & 0xFF;
  }
        //sends first x value
      val = pixy.ccc.blocks[0].m_x;//takes x value from 0th position in array from getBlocks();
      pixy.ccc.blocks[0].print();//prints data about the block, like it literally prints all of the info 
      delay(100);
      valArray[1] = val & 0xFF;//shifts byte over, then bitwise and, essentially to be able to send the values
      valArray[0] = (val >> 8) & 0xFF;
      /*Serial.print(valArray[0]);
      Serial.print(valArray[1]);
      Serial.print(" is first x value");
      Serial.println("val 1 = " + val);*/
      //sends second x value 
      val = pixy.ccc.blocks[1].m_x;
      pixy.ccc.blocks[1].print();//see above
      delay(100);
      valArray[3] = val & 0xFF;//same as above
      valArray[2] = (val >> 8) & 0xFF;
      /*Serial.print(valArray[2]);
      Serial.print(valArray[3]);
      Serial.print(" is second x value");
      Serial.println("val 2 = " + val);*/

}
