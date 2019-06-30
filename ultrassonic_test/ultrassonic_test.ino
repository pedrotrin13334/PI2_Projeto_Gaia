
const int trigPin = D6;
const int echoPin = D5;
long duration;
int distance;
int distance_ = 0;      
int sensorValue = 0;   
int ReadValue = 0;
int ReadTimes = 0;
void setup() {

pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
Serial.begin(9600);
}

void loop() {
  
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
        delay(500);
        sensorValue = distance_;
      }
    }
    if(sensorValue >2000){
      sensorValue =0;
    }
  Serial.println(sensorValue);
  distance = 0;
  distance_ = 0;
  }

