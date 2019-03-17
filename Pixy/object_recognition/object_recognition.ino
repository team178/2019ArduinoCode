#include <Pixy2.h>
#include <Wire.h>

Pixy2 pixy;  
int32_t val;//used to take data from pixy
byte valArray[8];//to send to roboRIO
/*
 * valArray[0] + valArray[1], first x value 
 * valArray[2] + valArray[3], second x value 
 * valArray[4] + valArray[5], number of blocks seen
 * valArray[6] + valArray[7], status of SPI connection, <0 if no communcation, 0 if works 
 * valArray[8] + valArray[9], status of I2C connection, 0 if no work, 1(?) if works
 * 
 */
int commsSPI;
int commsI2C;

void setup() 
{
  Wire.begin(8);//should correspond to RobotMap.pixyAddress
  Serial.begin(115200);
  Serial.println("Starting...");
  Wire.onRequest(requestEvent);//is essentially a definition, what to do when the roboRIO asks for data

  //sends status of I2C connection (WIP)
  commsI2C = Wire.write(1);
  valArray[9] = commsI2C & 0xFF;
  valArray[8] = (commsI2C >> 8) & 0xFF;

  //sends status of SPI connection from the pixy to the Arduino 
  commsSPI = pixy.init();
  valArray[7] = commsSPI & 0xFF;
  valArray[6] = (commsSPI >> 8) & 0xFF;

  //sets brightness 
  pixy.setCameraBrightness(10);
}

void requestEvent()//handler for onRequest method
{
  Wire.write(valArray, 8);//sending six bytes, two bytes for each 
}

void loop() 
{ 
  //Pixy seems to overload at fast speeds, implementing a delay
  delay(20);

  //get an array of all objects pixy is currently seeing
  //ccc stands for color connected components
  //will only run if blocks has values

/*
  //sends the number of blocks seen plus one - zero indicates that there is an error in communication
  int v = 0;
  if (pixy.ccc.getBlocks() < 0) {
    v = 0;
    valArray[5] = v & 0xFF;
    valArray[4] = (v >> 8) & 0xFF;
  } else {
    v = 1 + pixy.ccc.getBlocks();
    valArray[5] = v & 0xFF;
    valArray[4] = (v >> 8) & 0xFF;
  }
*/

  //alternative to sending the number of blocks plus one - where zero indicates that there is an error in communication
  pixy.ccc.getBlocks();
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
