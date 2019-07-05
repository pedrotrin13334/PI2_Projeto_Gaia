#include<SoftwareSerial.h>
#define LED 2
char teste;
SoftwareSerial HC12(4,5);
void setup() {
  // put your setup code here, to run once:
  HC12.begin(9600);
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(HC12.available())
  { teste = HC12.read();
    if(teste == 't') 
      { digitalWrite(LED,HIGH);
      }
    
      if(teste == 'o')
      {
        digitalWrite(LED,LOW);
      }
      Serial.println(teste);
  }
}
