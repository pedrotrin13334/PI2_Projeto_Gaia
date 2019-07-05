#ifndef Encoder_control_h
#define Encoder_control_h

#include<Arduino.h>

class Encoder_control 
{public:
  Encoder_control(void);
  int Encoder1_rpm(void);
  int Encoder2_rpm(void);
};

#endif
