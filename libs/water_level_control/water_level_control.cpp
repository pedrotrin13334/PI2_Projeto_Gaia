#include<Arduino.h>
#include<water_level_control.h>

#define SINKING true 
#define NOT_SINKING false
#define sensor_pin 16

WaterLevel::WaterLevel(void)
{ pinMode(sensor_pin, INPUT);
}

bool WaterLevel::check_status()
{  
   value1 = digitalRead(sensor_pin);
   delay(10);
   value2 = digitalRead(sensor_pin);

   if(value1 != value2)
   {
      this->check_status();
   }
   else
   { 
      return value1; 
   }
}
