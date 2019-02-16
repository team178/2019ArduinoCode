#include <Pixy2.h>
#include <Wire.h>

Pixy2 pixy;  
int32_t val;
byte valArray[4];

void setup() 
{
  Wire.begin(8);//technically address doesn't need to be here, but i haven't seen it work without it. (put 8 in as input)
  //Wire.onRequest(requestEvent);
  Serial.begin(115200);
  Serial.print("Starting...\n");
  Wire.onRequest(requestEvent);
  pixy.init();
  pixy.setCameraBrightness(16);
}

void requestEvent()//deprecated atm
{
  //should use the value set to val right before requestEvent is called
  Wire.write(valArray, 4);
}

void sendFirstX()//sends first x value over i2c address 8, done in order to better differentiate values in java
{
  Wire.begin(8);
  //Wire.beginTransmission(8);
  Wire.write(valArray, 2);
  //Wire.endTransmission(8);
}

void sendSecondX()//sends second x value over i2c address 9, see above
{
  Wire.begin(9);
  //Wire.beginTransmission(9);
  Wire.write(valArray, 2);
  //Wire.endTransmission(9);
}


void loop() 
{ 
  //Pixy seems to overload at fast speeds, implementing a delay
  delay(20);

  //counter variable
  int i;

  //get an array of all objects pixy is currently seeing
  //ccc stands for color connected components
  //pixy.ccc.getBlocks();
  
  //will only run if blocks has values
  if (pixy.ccc.getBlocks() > 0)
  {
   // for (i = 0; i < 2/*pixy.ccc.numBlocks*/; i++)
  //  {
      val = pixy.ccc.blocks[0].m_x;
          pixy.ccc.blocks[0].print();
      //m_x is the variable to represent x value from 0 to 315
   //   if (i % 2 == 0)
   //   {
        valArray[1] = val & 0xFF;
        valArray[0] = (val >> 8) & 0xFF;
        Serial.print(valArray[0]);
        Serial.print(valArray[1]);
        //Wire.onRequest(sendFirstX);
        //Wire.onRequest(requestEvent);
        Serial.println("val 1 = " + val);
  //    } else {
        val = pixy.ccc.blocks[1].m_x;
        pixy.ccc.blocks[1].print();
        valArray[3] = val & 0xFF;
        valArray[2] = (val >> 8) & 0xFF;
        Serial.print(valArray[2]);
        Serial.print(valArray[3]);
        //Wire.onRequest(sendSecondX);
        //Wire.onRequest(requestEvent);
        Serial.println("val 2 = " + val);
  //    }
 //   }
  }
  
  else
  {
    val = 0;
    valArray[1] = val & 0xFF;
    valArray[0] = (val >> 8) & 0xFF;

    for (i = 0; i < 2; i++) {
      Serial.println((byte) valArray[i]);
      }
    
    //will return value of -1 when nothing is recognized
   /* val = 0;
    while (val < 320) {
    Serial.println(val);//pnly one works for some reason 
    val = val + 1;//pnly one works for some reason
    //Wire.onRequest(sendFirstX);
    delay(1000);
    } */

    /*
    while (val >= 0) {
      Serial.println(val);
      val--;
      Wire.onRequest(sendSecondX);
      delay(1000);
    }
    
    //Wire.onRequest(requestEvent);
    */
  }
  
}
