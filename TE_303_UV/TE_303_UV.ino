/*
  UV Project
  TE 303 Prototyping
  
  (c) 2018 Concepcion Sosa & Duheng "Hansen" Liang
 
 */


#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

const int UV_SENSE_PIN = A4;
const int LED_COUNT = 10;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  CircuitPlayground.begin();
  
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(UV_SENSE_PIN);
  Serial.println(sensorValue);
  
  delay(1);        // delay in between reads for stability
  
  int instReading = map(sensorValue, 0, 127, 0, LED_COUNT); // scale reading to LEDs
  showMeter(instReading);
}

// show a "meter" with the ring of LEDs on the board. Input how many lights should go on
void showMeter(int meterValue) {  

  
  //Limiter
  if (meterValue > LED_COUNT){
    meterValue = LED_COUNT;
  }

  if (meterValue < 0) {
    meterValue = 0;
  }


  // light up the LEDs in their pre-assigned colors while remapping to intuitive order
  switch (meterValue) {
    case 10: CircuitPlayground.setPixelColor(5, 0xff0000);
    case 9: CircuitPlayground.setPixelColor(6, 0xff0000);
    case 8: CircuitPlayground.setPixelColor(7, 0xf94e00);
    case 7: CircuitPlayground.setPixelColor(8, 0xf9a600);
    case 6: CircuitPlayground.setPixelColor(9, 0xf9db00);
    case 5: CircuitPlayground.setPixelColor(0, 0xaaf900);
    case 4: CircuitPlayground.setPixelColor(1, 0x52f900);
    case 3: CircuitPlayground.setPixelColor(2, 0x00f918);
    case 2: CircuitPlayground.setPixelColor(3, 0x00bef9);
    case 1: CircuitPlayground.setPixelColor(4, 0x005ff9);
  }

  clearOtherLEDs(meterValue);
  
}

// turns off all LEDs (somehow the default .clearPixels() doesn't work...)
void clearLEDs(){
  for (int i = 0; i < LED_COUNT; i++){
    CircuitPlayground.setPixelColor(i, 0x000000);
  }
}

// turn the rest of the LEDs not being used
void clearOtherLEDs(int meterValue){
  // turn off LEDs while remapping to intuitive order
  switch (meterValue) {
    case 1: CircuitPlayground.setPixelColor(4, 0x000000);
    case 2: CircuitPlayground.setPixelColor(3, 0x000000);
    case 3: CircuitPlayground.setPixelColor(2, 0x000000);
    case 4: CircuitPlayground.setPixelColor(1, 0x000000);
    case 5: CircuitPlayground.setPixelColor(0, 0x000000);
    case 6: CircuitPlayground.setPixelColor(9, 0x000000);
    case 7: CircuitPlayground.setPixelColor(8, 0x000000);
    case 8: CircuitPlayground.setPixelColor(7, 0x000000);
    case 9: CircuitPlayground.setPixelColor(6, 0x000000);
    case 10: CircuitPlayground.setPixelColor(5, 0x000000);
    
  }
}
