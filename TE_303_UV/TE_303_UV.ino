/*
  UV Project
  TE 303 Prototyping

  This UV project has 2 modes: 
  Slide switch - left: Instant UV meter mode will show # of LEDs based on the currently measured UV Index
  Slide switch - right: Cumulative UV exposure mode (currenlty tuned to a demo mode, which will go off  quickly) keeps adding how much exposure you've had and plays an alarm when you've exceeded your daily safe dose of UV.
  
  (c) 2018 Concepcion Sosa & Duheng "Hansen" Liang
 
 */

#include <timer.h>
#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

const int UV_SENSE_PIN = A4;
const int LED_COUNT = 10;
bool leftButtonPressed = false;
bool muted = false;
const int UV_EXP_THRESH = 210; // According to EPA, over 30 minutes of UVI 7 exposure can lead to skin damage
int cuUVExp = 0;
int instUVI = 0;
auto timer = timer_create_default();

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {
  timer.tick();
  // read the input on analog pin 0:
  int sensorValue = analogRead(UV_SENSE_PIN);
  
  //delay(1);        // delay in between reads for stability

  leftButtonPressed = CircuitPlayground.leftButton(); // for muting the alarm


  // if slideswitch is on the left, it's the instant UV meter mode
  if(CircuitPlayground.slideSwitch()){
      showMeter(instUVI);
  }
  // if the slideswitch is on the right, show the cumulative exposure
  else{
    int currentExposure = map(cuUVExp, 0, UV_EXP_THRESH, 0, LED_COUNT);
      showMeter(currentExposure);
  }

  
  instUVI = map(sensorValue, 0, 1023, 0, 50); // according to Adafruit, the reading 0-5V corresponds linearly to UVI 0 - 50
  timer.every(1000, addExp); // Every minute, add current UVI to cumulative exposure 
  
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
    //case 1: CircuitPlayground.setPixelColor(4, 0x005ff9);
    default: CircuitPlayground.setPixelColor(4, 0x005ff9); // always light 1 up to show it's working.
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
    case 0:
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

// add current exposure to the cumulative value. Play alarm if cumulative value is above the threshold.
bool addExp(void *){
  cuUVExp += instUVI;
  if(cuUVExp > UV_EXP_THRESH && !muted) {
    playAlarm();
  }
  Serial.println(cuUVExp);
  return true; // keep the timer active by returning true
}

void playAlarm(){
    CircuitPlayground.playTone(1000,1000);
    CircuitPlayground.playTone(1340,1000);
    if(CircuitPlayground.leftButton()){
      muted = true;
    }
    return;
}
