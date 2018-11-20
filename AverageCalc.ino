#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>


int Samplecount;
int sum;


void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {
  // gets the temp from playground, stores it as a float
  float tempF=CircuitPlayground.temperatureF();
  
  //add temperature into sum
  sum+=tempF;
  
  //count will keep track for 10 values
  Samplecount+=1;
  
  //it's going to read every 1 sec.
  delay(1000);

  //just for testing purpose, i needed to see the value
  //Serial.println("This is sum ");
  //Serial.println(sum);
  
  //once there are 10 values, it will divide it by 10
  if (Samplecount ==10){
    Serial.print("The average temp is:" );
    Serial.println(sum/10);
    
    //resets both count and sum
    Samplecount=0;
    sum=0;

    // just double checking that it did reset
    //Serial.println(count);
    //Serial.println(sum);
  }  
}
