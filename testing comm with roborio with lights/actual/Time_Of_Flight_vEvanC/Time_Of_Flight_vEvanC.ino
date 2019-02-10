#include "Adafruit_VL53L0X.h"
#include <Wire.h>
#include <SoftwareWire.h>

SoftwareWire master(2, 3);

Adafruit_VL53L0X rightdist = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measureright;

Adafruit_VL53L0X leftdist = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measureleft;

String state = "Not Initialized";

void setup() {
  Serial.begin(115200);
  Wire.begin(18);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!leftdist.begin(0x29, false, master) || !rightdist.begin(0x30, false, master)) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
  Wire.onRequest(roborioHasAskedForData);
}

void roborioHasAskedForData()
{
  Wire.write(state.c_str(), state.length());
}

void loop() {
    
  Serial.print("Reading a measurement from right side... ");
  rightdist.rangingTest(&measureright, false); // pass in 'true' to get debug data printout!

  if (measureright.RangeStatus != 4) {  //should probably add a margin of error
    Serial.print("Distance (mm): "); 
    Serial.println(measureright.RangeMilliMeter);
    //Wire.onRequest(requestEventRight);

  } else {
    Serial.println(" out of range on right side ");
  }
  
    Serial.print("Reading a measurement from left side... ");
  leftdist.rangingTest(&measureleft, false); // pass in 'true' to get debug data printout!

  if (measureleft.RangeStatus != 4) {  
    Serial.print("Distance (mm): "); 
    Serial.println(measureleft.RangeMilliMeter);
    //Wire.onRequest(requestEventLeft);

  } else {
    Serial.println(" out of range on left side ");
  }

  if (measureright.RangeMilliMeter == measureleft.RangeMilliMeter) {
    Serial.println(" success ");
    state = "Ready";
  } else {
   if (measureright.RangeMilliMeter > measureleft.RangeMilliMeter){
    Serial.println("not parallel, turn right.");
    state = "Turn Right";
   }
   if (measureleft. RangeMilliMeter > measureright.RangeMilliMeter){
    Serial.println("not parallel, turn left.");
    state = "Turn Left";
   }
  }
  delay(100);
}
