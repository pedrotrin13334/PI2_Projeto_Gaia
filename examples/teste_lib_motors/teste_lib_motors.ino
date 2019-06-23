#include <PWM_control.h>

PWM_control motors;
int pwm = 500; 
char received_char; 
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available() > 0)
{   received_char = Serial.read();
    Serial.println(received_char);
    switch(received_char)
    {   case '1': 
        motors.PWM_go_forwards(pwm);
        Serial.println("Going Forwards");
        break;
        
        case '2': 
        motors.PWM_go_backwards(pwm);
        Serial.println("Going Backwards");
        break;

        case '3': 
        motors.PWM_turn(pwm, LEFT);
        Serial.println("Turning Left");
        break;

         case '4': 
        motors.PWM_turn(pwm,RIGHT);
        Serial.println("turning right");
        break;

        case 'x': 
        pwm = (pwm + 100)%1023;
        Serial.print("PWM value: ");
        Serial.println(pwm);
          
    }
    delay(100);
}
}
