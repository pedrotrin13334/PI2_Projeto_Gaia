#include <SoftwareSerial.h>
#include<water_level_control.h>

SoftwareSerial HC12(D4, D3); // HC-12 TX Pin, HC-12 RX Pin
char start;
double latt;
double longt;                    // using a constant String
unsigned long int pmillis;
void setup()
{
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  pmillis = millis();
}

void loop()
{
  while (millis() - pmillis < 1000)
    ;
  pmillis = millis();
  char init= 'I';
  char stat = 'o';
  unsigned int bat = analogRead(A0); //4.0V = 0x0333
  //latt = gps_lat();
  //longt = gps_long();
  unsigned int weight = water_level();
  unsigned int cap = ultrasonic_reading();
 char fim ='X'; 
  start = HC12.read();
  if(start == 's') { 
     delay(1000);
 HC12.print(init);
 delay(1000);
 HC12.print(bat);
 delay(1000);
 HC12.print(latt);
 delay(1000);
 HC12.print(longt);
 delay(1000);
 HC12.print(cap);
 delay(1000);
 HC12.print(weight);
 delay(1000);
 HC12.print(stat);
 delay(1000);
 HC12.print(fim);
 delay(1000);
  HC12.println();}}

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
