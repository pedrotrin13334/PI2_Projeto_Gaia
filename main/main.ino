#include <SoftwareSerial.h>
#include<water_level_control.h>
#include <MPU9250.h>
#include <PWM_control.h>

//rasp_esp communication variables
#define INICIO_MISSAO 1 
#define MISSAO_NORMAL 0
bool estado;
String lat_min;
String lon_min;
String lat_max;
String lon_max;

String init_angle;

String message; 
char* received_message; 

char received_char;

String boat_weight ; 
String ultrassound_dist;
String boat_dir ;

String first_loc[4];
bool is_first_message = true;
//rasp_esp communication variables

String split_string[5] = ""; 
#define LEFT true
#define RIGHT false

SoftwareSerial HC12(D4, D3); // HC-12 TX Pin, HC-12 RX Pin
char start;
double latt;
double longt;                    // using a constant String
unsigned long int pmillis;

// motors
PWM_control motors; 

//MPU 
MPU9250 mpu;

String read_String;

void setup()
{
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  pmillis = millis();

 estado = INICIO_MISSAO;
  //motors
  
  //MPU
   Wire.begin();

   delay(2000);
   mpu.setup();

}

void loop()
{  
 //makes the string readString  

     
//  if (readString.length() >0)
//    Serial.println(readString); //prints string to serial port out
  
  while (millis() - pmillis < 1000);
  pmillis = millis();
  char init= 'I';
  char fim ='X';
  int cap = ultrasonic_reading();
  int weight = water_level();
  bool reached_angle = false; 
  double boat_angle;
  double ref_angle;
  int go;
  int last_go = 0;
  ultrassound_dist = String(cap);
  boat_weight = String(weight);

  if(is_first_message)
  { get_first_locations();
    lat_min = first_loc[0];
    lon_min = first_loc[1];
    lat_max = first_loc[2];
    lat_max = first_loc[3];

    boat_angle = get_angle(); 
    boat_dir = String(boat_angle, 2);
    
    rasp_communication();
    is_first_message = false;
   }
  else
  {  received_message = rasp_communication();
     //string_split(received_message);
     
     ref_angle = split_string[3].toFloat();
     go = split_string[0].toInt();
     latt = split_string[1].toFloat();
     longt =  split_string[2].toFloat();
     if(last_go == go)
     {   
        if(go)
        {
         motors.PWM_go_forwards(1);
        }
        else
        { int init_time = millis();
          while(!reached_angle && millis() - init_time < 50)
          { boat_angle = get_angle();
            boat_dir = String(boat_angle, 2);
            reached_angle = move_angle(ref_angle,boat_angle);
          } 
        }
     }
     else
     {
       if(go)
       {
         motors.PWM_go_forwards(1);
       }
       else
       {
        motors.PWM_go_forwards(0);
       }
     }
  }
  delay(100);
  //esp_rasp_communication(cap);
  //delay(100);
  //latt = gps_lat();
  //longt = gps_long();
  // int weight = water_level(); 
  start = HC12.read();
  if(start == 's') {
    received_char = Serial.read();
    switch(received_char)
    {   case '1': 
        motors.PWM_go_forwards(1);
        break;

        case '2': 
        motors.PWM_turn(LEFT);
        break;

         case '3': 
        motors.PWM_turn(RIGHT);

        break;

        case '4': 
        motors.PWM_go_forwards(0);
     
        break;
          
    } 
     delay(100);
 HC12.print(init);
 delay(100);
 HC12.print(cap);
 delay(100);
 HC12.print(weight);
 delay(100);
 HC12.print(latt);
 delay(100);
 HC12.print(longt);
 delay(100);
 HC12.print(fim);
 delay(100);
  HC12.println();

  
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
       message = lat_min + ',' + lon_min + ',' + lat_max + ',' + lon_max + ',' + init_angle + ','; 
       Serial.println(message);
       estado = MISSAO_NORMAL; 
       return "not";    
    }
    else
    { message = boat_weight + ',' + ultrassound_dist + ',' + boat_dir + ',';
      delay(100);
      Serial.println(message);
      
      Serial.readBytes(received_message, 30);    

      return received_message;
    }
  }
 
}


void get_first_locations()
{ //int num_of_loc = 0;
   //while(num_of_loc <4)
   //{
      while (HC12.available()) 
      {
          delay(10);  //small delay to allow input buffer to fill

          char c = HC12.read();  //gets one byte from serial buffer
          if (c == ',') {
            break;
          }  //breaks out of capture loop to print readstring
          read_String += c; 
      } //makes the string readString 
    //first_loc[num_of_loc] = read_String;
    read_String = "";
    //num_of_loc += 1;
   }

   HC12.println("Received");
}

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
