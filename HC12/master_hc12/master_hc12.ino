#include<SoftwareSerial.h>

SoftwareSerial HC12(4,5);
char teste;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  HC12.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available())
  { 
    HC12.write(Serial.read());
  }
 
}
