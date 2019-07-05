#ifndef GPS_h
#define GPS_h

#include <Arduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h> 

class GPS
{

 public:
    GPS(TinyGPSPlus input_gpsSerial);
    int* get_info(); 
  private: 
   TinyGPSPlus gps; 
   SoftwareSerial gpsSerial;

}

#endif
