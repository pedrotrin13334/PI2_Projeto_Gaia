#include <SoftwareSerial.h>


//HC12
char start;
char init_char= 'I';
char end_char ='X';
SoftwareSerial HC12(D4, D3); // HC-12 TX Pin, HC-12 RX Pin

void setup() 
{
   // put your setup code here, to run once:
   Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int weight = water_level();
  int cap = ultrasonic_reading();
  if(Serial. available()>0)
  {
    char n = Serial.read();
     if(n == 'i'){
    Serial.print(weight);
    Serial.print(',');
    Serial.print(cap);
    Serial.flush(); //espera a transmissão serial de dados completar
  }

  if(HC12.available()>0)
  {
   start = HC12.read();
    if(start == 's') 
    { 
           delay(100);
       HC12.print(init_char);
       HC12.print(cap);
      // HC12.print(latt);
      // delay(500);
      // HC12.print(longt);
      // delay(500);
       HC12.print(weight);
       HC12.print(end_char);
    }
  }
}
}

int ultrasonic_reading()
{
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
      if(sensorValue >2000)
        {
        sensorValue =0;
        }
    }
  distance = 0;
  distance_ = 0;
  return sensorValue;
}

int water_level() 
{
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
