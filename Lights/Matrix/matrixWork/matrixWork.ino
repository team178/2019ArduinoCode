#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

int r = 255;
int g = 208;
int b = 0;

void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  matrix.show();
  matrix.setBrightness(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int x = 0; x <= 32; x++){
    for(int y = 0; y <= 8; y++)
    {
      matrix.drawPixel(x,y,matrix.Color(r,g,b));
    }
  }
  matrix.show();
  if(r != 2){
    r--;
  }
  if(g != 5){
    g--;
  }
  if(b != 121){
    b++;
  }
  if(r == 2 && g == 5 && b == 121){
    r = 255;
    g = 208;
    b = 0;
  }
}
