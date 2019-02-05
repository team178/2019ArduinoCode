#include <Servo.h>
#define PIN 2
Servo linearActuator;
int linearValue = 1000;

void setup()
{
  linearActuator.attach(PIN, 1050, 2000);
  linearActuator.writeMicroseconds(linearValue);
}

void loop()
{
  linearValue = 700;
  linearActuator.writeMicroseconds(linearValue);
}
