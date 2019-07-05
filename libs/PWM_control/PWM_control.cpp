#include <Arduino.h>
#include <PWM_control.h>

#define motor_enable_pin 16
#define inversion_right_pin 13
#define inversion_left_pin 15 

PWM_control::PWM_control(void)
{
   pinMode(motor_enable_pin,OUTPUT); //initiates all used pins as output
   pinMode(inversion_right_pin,OUTPUT);
   pinMode(inversion_left_pin,OUTPUT);
   boat_state = idle;
}

void PWM_control::PWM_go_forwards(int PWM_value)
{ if(boat_state != going_forwards)
  {  digitalWrite(motor_enable_pin, LOW);
     delay(1000);

     digitalWrite(inversion_right_pin,LOW); 
     digitalWrite(inversion_left_pin,LOW); //puts both motors  in  foward direction
  }
  if(PWM_value == false){
    boat_state = idle;
  }else{
    boat_state = going_forwards;
  }
     digitalWrite(motor_enable_pin, PWM_value);
}

//void PWM_control::PWM_go_backwards(int PWM_value)
//{ 
// if(boat_state != going_backwards)
// {   analogWrite(PWM_right_pin, 0);
//     analogWrite(PWM_left_pin,0);
//     delay(1000);
//     digitalWrite(inversion_right_pin,HIGH); 
//     digitalWrite(inversion_left_pin,HIGH); 
// }
//  analogWrite(PWM_right_pin, PWM_value);
//  analogWrite(PWM_left_pin, PWM_value);
//  boat_state = going_backwards; 
//}

void PWM_control:: PWM_turn(bool direction)
{  
    if(direction)
     {  
          if(boat_state != turning_left)
          {
              digitalWrite(motor_enable_pin, LOW);
              delay(1000);
          }

        digitalWrite(inversion_right_pin, LOW);
        digitalWrite(inversion_left_pin,HIGH);
        boat_state = turning_left;
     }
     else
     {   
          if(boat_state != turning_left)
          {
             digitalWrite(motor_enable_pin, LOW);
             delay(1000);
         }

         digitalWrite(inversion_right_pin, HIGH);
         digitalWrite(inversion_left_pin,LOW);
         boat_state = turning_right;
     }

  digitalWrite(motor_enable_pin, HIGH);
}
