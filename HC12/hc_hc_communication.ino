#include <SoftwareSerial.h>

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
  latt = -16.02873;
  longt = -48.05326;
  unsigned int weight =50;
  unsigned int cap = 1;
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


