#include <PWM_control.h>

PWM_control motors;
bool pwm = 1; 
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

        case '3': 
        motors.PWM_turn(LEFT);
        Serial.println("Turning Left");
        break;

         case '4': 
        motors.PWM_turn(RIGHT);
        Serial.println("turning right");
        break;

        case '5': 
        motors.PWM_go_forwards(0);
        Serial.println("motors have stopped");
        break;
          
    }
    delay(100);
}
}
