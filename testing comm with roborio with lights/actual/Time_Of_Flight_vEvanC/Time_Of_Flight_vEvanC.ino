
#include "Adafruit_VL53L0X.h"
#include <Wire.h>
#include <SoftwareWire.h>
#include "math.h"

SoftwareWire softwareI2C(2, 4);

Adafruit_VL53L0X rightdist = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measureright;

Adafruit_VL53L0X leftdist = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measureleft;

String state = "n";

void setup() {
  Serial.begin(115200);
  Wire.begin(18);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X sensors booting...");
  if (!leftdist.begin(0x29, false) || !rightdist.begin(0x30, false)) {
    Serial.println(F("Failed to boot at least one VL53L0X sensor"));
    while(1);
  }
  // power 
  Wire.onRequest(roborioHasAskedForData);
}

void roborioHasAskedForData()
{
  Wire.write(state.c_str(), state.length());
}

void loop() {
    
  Serial.print("Reading a measurement from right side... ");
  rightdist.rangingTest(&measureright, false); // pass in 'true' to get debug data printout!

  if (measureright.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); 
    Serial.println(measureright.RangeMilliMeter);
    //Wire.onRequest(requestEventRight);

  } else {
    Serial.println(" out of range on right side ");
  }
  
    Serial.print("Reading a measurement from left side... ");
  leftdist.rangingTest(&measureleft, false); // pass in 'true' to get debug data printout!

  if (measureleft.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); 
    Serial.println(measureleft.RangeMilliMeter);
    //Wire.onRequest(requestEventLeft);

  } else {
    Serial.println(" out of range on left side ");
  }

  if (abs(measureright.RangeMilliMeter - measureleft.RangeMilliMeter) < 3) {
    Serial.println(" success ");
    state = "y"; //ready
  } else {
   if (measureright.RangeMilliMeter > measureleft.RangeMilliMeter && abs(measureright.RangeMilliMeter - measureleft.RangeMilliMeter) > 3){
    Serial.println("not parallel, turn right.");
    state = "r"; //turn right
   }
   if (measureleft. RangeMilliMeter > measureright.RangeMilliMeter && abs(measureright.RangeMilliMeter - measureleft.RangeMilliMeter) > 3){
    Serial.println("not parallel, turn left.");
    state = "l"; //turn left
   }
  }
  delay(100);
}
