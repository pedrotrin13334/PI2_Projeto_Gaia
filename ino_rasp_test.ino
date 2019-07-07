#include <SoftwareSerial.h>
#include<water_level_control.h>


void setup() {
 // put your setup code here, to run once:
Serial.begin(9600);
pinMode(2, OUTPUT);
digitalWrite(2, HIGH);  
}

void loop() {
  // put your main code here, to run repeatedly:
  int weight = water_level();
  int cap = ultrasonic_reading();
  if(Serial. available());{
  char n = Serial.read();
   if(n == 'i'){
  Serial.print(weight);
  Serial.print(',');
  Serial.print(cap);
  Serial.flush(); //espera a transmissão serial de dados completar
  }
  delay(1000);
}}

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
}

int water_level() {
  WaterLevel level_sensor;
  // put your main code here, to run repeatedly:
   if(level_sensor.check_status())
   {
    return 0;
   }
   else
   {
    return 1;
   }
}

