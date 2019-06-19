#ifndef PWM_control_h
#define PWM_control_h

#include <Arduino.h>
#define LEFT true
#define RIGHT false
class PWM_control 
{public:
   PWM_control(void);
   void PWM_go_forwards(int PWM_value);
   void PWM_go_backwards(int PWM_value);
   void PWM_turn(int PWM_value, bool direction);
 private:
   enum states {idle = 4,going_forwards = 3, going_backwards =2 , turning_right = 1, turning_left = 0}; 
   enum states boat_state;
};
#endif
