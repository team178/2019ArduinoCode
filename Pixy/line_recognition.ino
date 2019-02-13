#include <Pixy2.h>
#include <Wire.h>

Pixy2 pixy;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  pixy.init();

  //change to line_tracking program
  Serial.println(pixy.changeProg("line"));
}

void loop() {
  // put your main code here, to run repeatedly:

}
