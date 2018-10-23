/*
  UV Project - color changing
  TE 303 Prototyping
  
  (c) 2018 Concepcion Sosa & Duheng "Hansen" Liang
 
 */

int lit = 0;

#include <Adafruit_CircuitPlayground.h>

void setup() {
  CircuitPlayground.begin();

}

void loop() {

  
  CircuitPlayground.setPixelColor(3, 0xFF00FF);
  CircuitPlayground.setPixelColor(8,0x00CCCC);
}
