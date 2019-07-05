#include <Arduino.h>
#include <GPS.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define RXpin 13
#define TXpin 15
GPS::GPS(void)
{ gpsSerial = inputgpsSerial;
  gps = input_gps;
  gpsSerial.begin(9600);

}

int* GPS::get_info(void)
{ int lat_long[2]; 
 if (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
    {  
       if(gps.location.isValid())
       {   
         lat_long[0] = gps.location.lat();
         lat_long[1] = gps.location.lng();
       }
       else
       {  
         lat_long[0] = 0;
         lat_long[1] = 0;
       }
    }
   else
    {  lat_long[0] = 0;
       lat_long[1] = 0;
     }
 return lat_long; 
}
