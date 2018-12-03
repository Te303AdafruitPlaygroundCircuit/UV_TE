void UvAlarm(){
    CircuitPlayground.playTone(1000,1000);
    CircuitPlayground.playTone(1340,1024);
    delay(1000);
    if (leftButtonPressed==true){
      exit(1);
    }
}

//can call the alarm at any time, I wasn't sure where it would be located
