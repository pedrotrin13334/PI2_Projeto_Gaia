//#include <PWM_control.h>
#include<SoftwareSerial.h>
SoftwareSerial HC12(D4,D3); //tx rx
//PWM_control motors;
char received_char; 
int right_motor_pin = 5;
int left_motor_pin = 4;
int motor_enable_pin = 16;
void setup() {
  //Serial.begin(9600);
  // put your setup code here, to run once:
   HC12.begin(9600);
  pinMode(left_motor_pin,OUTPUT);
  pinMode(right_motor_pin,OUTPUT);

  pinMode(motor_enable_pin,OUTPUT);
   //digitalWrite(16,HIGH);
   
}

void loop() {
  // put your main code here, to run repeatedly:
if(HC12.available() > 0)
{   received_char = HC12.read();
    //Serial.println(received_char);
    switch(received_char)
      {   case '1': 
        //motors.PWM_go_forwards(true);
        //Serial.println("Going Forwards");
        digitalWrite(right_motor_pin,HIGH);
        digitalWrite(left_motor_pin,HIGH);

        digitalWrite(motor_enable_pin,HIGH);
        break;
        
        case '3': 
        //motors.PWM_turn(LEFT);
        //Serial.println("Turning Left");
         digitalWrite(right_motor_pin,HIGH);
        digitalWrite(left_motor_pin,LOW);

        
        digitalWrite(motor_enable_pin,HIGH);
        break;

         case '4': 
        //motors.PWM_turn(RIGHT);
       // Serial.println("turning right");
         digitalWrite(right_motor_pin,LOW);
        digitalWrite(left_motor_pin,HIGH);

        
        digitalWrite(motor_enable_pin,HIGH);
        break;
        
        case '5':
        //motors.PWM_go_forwards(false);
        //Serial.println("Motors was sttoped");
         digitalWrite(right_motor_pin,HIGH);
        digitalWrite(left_motor_pin,HIGH);

        
        digitalWrite(motor_enable_pin,LOW);
        break;
          
    }
    delay(100);
}
}
