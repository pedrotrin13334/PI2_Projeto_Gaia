#include<GPS.h>
#include<TinyGPS++.h>
GPS gps; 
int lat_long[2];
void setup()
{
 Serial.begin(9600);
}

void loop()
{ 
 lat_long = gps.get_info();
 Serial.print("Latitude: ");
 Serial.println(lat_long[0], 6);
 Serial.print("Longitude: ");
 Serial.println(lat_long[1], 6);
  
 Serial.println();
 Serial.println();

 delay(1000);
}
