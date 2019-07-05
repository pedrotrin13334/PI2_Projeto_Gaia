#include<Arduino.h>
#include<Encoder_control.h>

#define encoder1_pin 4 //digital pin d2
#define encoder2_pin 5 //digital pin d1
#define window_time 100 // sampling of rpm data time
#define pulses_per_rev 20 //number of pulses per revolution
Encoder_control::Encoder_control(void)
{ pinMode(encoder1_pin,INPUT);
  pinMode(encoder2_pin,INPUT);
}

int encoder1_rpm()
{ 
  int counter = 0; 
  bool level_state = 0; //encoder signal level
  int begin_time = milis();
  int timeout_time = begin_time;
  while(timeout_time - begin_time != window_time)
  {
    if(digitalRead(encoder1_pin) != level_state)
    {  
       counter++; 
       level_state = !level_state;
    }

    timeout_time = milis();
  }

  return (counter*1000)/(window_time*pulses_per_rev);
}
