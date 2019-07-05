#include<Arduino.h>
#include<water_level_control.h>

#define SINKING true 
#define NOT_SINKING false
#define sensor_pin A0

WaterLevel::WaterLevel(void)
{ pinMode(sensor_pin, INPUT);
}

bool WaterLevel::check_status()
{  
   value1 = analogRead(sensor_pin);

   if(value1 > 500)
   {
      return 1; 
   }
   else
   { 
      return 0; 
   }
}
