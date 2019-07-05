#include <SoftwareSerial.h>
#include<water_level_control.h>

SoftwareSerial HC12(D4, D3); // HC-12 TX Pin, HC-12 RX Pin
char start;
String readString;

unsigned long int pmillis;
void setup()
{
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  pmillis = millis();
}

void loop()
{  
  while (HC12.available()) {
    delay(10);  //small delay to allow input buffer to fill

    char c = HC12.read();  //gets one byte from serial buffer
    if (c == ',') {
      break;
    }  //breaks out of capture loop to print readstring
    readString += c; 
  } //makes the string readString  

//  if (readString.length() >0)
//    Serial.println(readString); //prints string to serial port out
   readString=""; //clears variable for new input
  
  while (millis() - pmillis < 1000)
    ;
  pmillis = millis();
  char init= 'I';
  char fim ='X';
  int cap = ultrasonic_reading();
  delay(100);
  //esp_rasp_communication(cap);
  //delay(100);
  //latt = gps_lat();
  //longt = gps_long();
  // int weight = water_level(); 
  start = HC12.read();
  if(start == 's') { 
     delay(100);
 HC12.print(init);
 delay(100);
 HC12.print(cap);
 delay(100);
// HC12.print(latt);
// delay(500);
// HC12.print(longt);
// delay(500);
// HC12.print(weight);
// delay(500);
 HC12.print(fim);
 delay(100);
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
        delay(100);
    if (distance_ == distance)
      {
        delay(5);
        sensorValue = distance_;
      }
    if(sensorValue >2000){
      sensorValue =2000;
    }}
    delay(1000);
//  distance = 0;
//  distance_ = 0;
  Serial.println(sensorValue);
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

void esp_rasp_communication(int n) {
  // put your setup code here, to run once:
Serial.begin(9600);
  if(Serial. available());{
    Serial.println(n);
  }
return;
}

