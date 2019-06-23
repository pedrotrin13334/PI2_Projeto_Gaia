#include<water_level_control.h>

WaterLevel level_sensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   if(level_sensor.check_status())
   {
    Serial.println("The boat is sinking");
   }
   else
   {
    Serial.println("The boat is not sinking");
   }
}
