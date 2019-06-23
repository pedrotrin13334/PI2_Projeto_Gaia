#include <Arduino.h>
#include <PWM_control.h>

#define PWM_right_pin 13
#define PWM_left_pin 14

#define inversion_right_pin 15
#define inversion_left_pin 12 

PWM_control::PWM_control(void)
{
   pinMode(PWM_right_pin,OUTPUT);
   pinMode(PWM_left_pin,OUTPUT); //initiates all used pins as output
   pinMode(inversion_right_pin,OUTPUT);
   pinMode(inversion_right_pin,OUTPUT);
   boat_state = idle;
}

void PWM_control::PWM_go_forwards(int PWM_value)
{ if(boat_state != going_forwards)
  { 
     digitalWrite(PWM_right_pin, 0);
     digitalWrite(PWM_left_pin,0); //stops the motors and waits for  a second
     delay(1000);
     digitalWrite(inversion_right_pin,LOW); 
     digitalWrite(inversion_left_pin,LOW); //puts both motors  in  foward direction
  }
  digitalWrite(PWM_right_pin, PWM_value); //rights the PWM value to make the motors work
  digitalWrite(PWM_left_pin, PWM_value);
      
}

void PWM_control::PWM_go_backwards(int PWM_value)
{ 
 if(boat_state != going_backwards)
 {   digitalWrite(PWM_right_pin, 0);
     digitalWrite(PWM_left_pin,0);
     delay(1000);
     digitalWrite(inversion_right_pin,HIGH); 
     digitalWrite(inversion_left_pin,HIGH); 
 }
  digitalWrite(PWM_right_pin, PWM_value);
  digitalWrite(PWM_left_pin, PWM_value);
}

void PWM_control:: PWM_turn(int PWM_value, bool direction)
{  
    if(direction)
     {  
          if(boat_state != turning_left)
          {
              digitalWrite(PWM_right_pin, 0);
              digitalWrite(PWM_left_pin,0);
              delay(1000);
          }

        digitalWrite(inversion_right_pin, LOW);
        digitalWrite(inversion_left_pin,HIGH);
     }
     else
     {   
         if(boat_state != turning_left)
          {
              digitalWrite(PWM_right_pin, 0);
              digitalWrite(PWM_left_pin,0);
              delay(1000);
          }

         digitalWrite(inversion_right_pin, HIGH);
         digitalWrite(inversion_left_pin,LOW);
     }

  digitalWrite(PWM_right_pin, PWM_value);
  digitalWrite(PWM_left_pin, PWM_value);
}

