#include <SoftwareSerial.h>
#include<water_level_control.h>
#include <MPU9250.h>
#include <PWM_control.h>


SoftwareSerial HC12(D4, D3); // HC-12 TX Pin, HC-12 RX Pin
char start;
String readString;
String init_angle;
String boat_weight ; 
String ultrassound_dist;
String boat_dir ;
char received_char;
#define INICIO_MISSAO 1 
#define MISSAO_NORMAL 0
#define LEFT true
#define RIGHT false
char* received_message; 
bool estado;
String message; 
bool is_first_message = true;
String split_string[5] = ""; 



// motors
PWM_control motors; 

//MPU 
MPU9250 mpu;
unsigned long int pmillis;

void setup()
{
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  pmillis = millis();
  
  //MPU
   Wire.begin();

   delay(2000);
   mpu.setup();
}

void loop()
{  
  while (HC12.available()) {
    delay(10);  //small delay to allow input buffer to fill

    char c = HC12.read();  //gets one byte from serial buffer
   // if (c == ',') {
     // break;
    //}  //breaks out of capture loop to print readstring
    readString += c; 
  } //makes the string readString  

//  if (readString.length() >0)
   Serial.println(readString); //prints string to serial port out
   
   readString=""; //clears variable for new input
  
  while (millis() - pmillis < 1000)
    ;
  pmillis = millis();
  char init= 'I';
  char fim ='X';
  int cap = ultrasonic_reading();
  int weight = water_level();
  delay(100);
  //esp_rasp_communication(cap);
  //delay(100);
  //latt = gps_lat();
  //longt = gps_long(); 
  start = HC12.read();
  if(start == 's') { 

    received_char = HC12.read();
    switch(received_char)
    {   case 'a': 
        motors.PWM_go_forwards(1);
        break;

        case 'b': 
        motors.PWM_turn(LEFT);
        break;

         case 'c': 
        motors.PWM_turn(RIGHT);

        break;

        case 'd': 
        motors.PWM_go_forwards(0);
     
        break;
    }
     delay(100);
 HC12.print(init);
 delay(100);
 HC12.print(cap);
 delay(100);
// HC12.print(latt);
// delay(500);
// HC12.print(longt);
// delay(500);
 HC12.print(weight);
 delay(100);
 HC12.print(fim);
 delay(100);
  HC12.println();}
  bool reached_angle = false; 
  double boat_angle;
  double ref_angle;
  int go;
  int last_go = 0;
  ultrassound_dist = String(cap);
  boat_weight = String(weight);
  boat_angle = get_angle(); 
    boat_dir = String(boat_angle, 2);
    rasp_communication();
}

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
  //Serial.println(sensorValue);
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

double get_angle()
{
  mpu.update();
  double boat_angle = 2*mpu.getYaw();

  return boat_angle;
}

bool move_angle(int ref_angle, double boat_angle) 
{        
     double dif_angle = boat_angle - ref_angle;
     if(dif_angle < 5  || dif_angle > -5)
     {
       motors.PWM_go_forwards(false); 

       return true;
     }
     else
      {  if(dif_angle > 0)
          {  motors.PWM_turn(LEFT);
          }
          else
         {  motors.PWM_turn(RIGHT);
         }
         return false;
      }
}

char* rasp_communication()
{
  Serial.flush();
  received_char = Serial.read();
  if(received_char == 'i')
  { 
    if(estado)
    {  
       delay(100); 
       Serial.println(boat_weight);
       estado = MISSAO_NORMAL; 
       return "not";    
    }
    else
    { 
      delay(100);
      Serial.println(ultrassound_dist);
      
      Serial.readBytes(received_message, 30);    

      return received_message;}}}


void string_split(char* received_string)
{  
  int counter = 0;
  int index = 0;
   while(counter < 30)
   {
          if (received_string[counter] == ',') {
            index++;
            counter++;
          }  //breaks out of capture loop to print readstring
          split_string[index] += received_string[counter]; 
    counter++;
   }
}
