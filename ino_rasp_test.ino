
#include <SoftwareSerial.h>
#include<water_level_control.h>
#include <StringSplitter.h>
#include<PWM_control.h>

PWM_control motors;

SoftwareSerial HC12(D4, D3); // HC-12 TX Pin, HC-12 RX Pin
String message;
unsigned long int pmillis;
int sensor_refresh_time;
int weight =0 ;
int cap =0;
char go;
char turn;
String latt;
String longt;

void setup() 
{
 // put your setup code here, to run once:
Serial.begin(9600); 
HC12.begin(9600);               // Serial port to HC12
pmillis = millis();
sensor_refresh_time = millis();
}

void loop() 
{ 
  // put your main code here, to run repeatedly:
    if(Serial.available()>0)
    {
      char n = Serial.read();
       if(n == 'i')
       {
          cap = ultrasonic_reading();
          weight = water_level();
          Serial.print(weight);
          Serial.print(',');
          Serial.print(cap);
          Serial.print(',');
        }
      else
      {
       message += n;
      }
      delay(100);
      Serial.flush();
     }
     if(!message.equals("")){
     treat_message(message); 
     //HC12.print(message);
     message = "";}
}
   
   
   //espera a transmissão serial de dados completar
  //char c = Serial.read();  //gets one byte from serial buffer
  //if (c == ',') {
  //break;
  //}  //breaks out of capture loop to print readstring
  //readString += c;}} 
  //makes the string readString  
  //if (readString.length() >0){
  //while (millis() - pmillis < 1000)
   // ;
 //pmillis = millis();
 //HC12.print(readString);
 //delay(100);
 //HC12.println();



/*int ultrasonic_reading(){
const int trigPin = D6;
const int echoPin = D5;
long duration;
int distance;
int distance_ = 0;      
int sensorValue = 0;   
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);   
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
  for (int i =0; i < 10; i++)
    {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance_= duration*0.034/2;
    if (distance_ == distance)
      {
        delay(100);
        sensorValue = distance_;
      }
    if(sensorValue >2000){
      sensorValue =0;
    }}
  distance = 0;
  distance_ = 0;
  return sensorValue;
}*/

int ultrasonic_reading(){
const int trigPin = D6;
const int echoPin = D5;
long duration;
int distance;
int distance_ = 0;      
int sensorValue = 0;   
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);   
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
if(distance > 2000)
{
  distance =0;
}
return distance;
}


int water_level() {
  // put your main code here, to run repeatedly:
   if(analogRead(A0) > 100)
   {
    return 0;
   }
   else
   {
    return 1;
   }
}

void treat_message(String received_message)
{

   go = received_message.charAt(0);
    switch(go)
    {
          case 'g':
          motors.PWM_go_forwards(1);
          break;

          case 's':
          motors.PWM_go_forwards(0);
          break;

          case 'l':
          motors.PWM_turn(1);
          break;

          case 'r':
          motors.PWM_turn(0);
          break;
    }
}
   //Serial.print(go);
   //latt = received_message.substring(0,10);
   //HC12.print(latt);
   //longt = received_message.substring(10,20);
   //HC12.print(longt);
   //turn = received_message[21] - '0';
   //Serial.print(turn);

