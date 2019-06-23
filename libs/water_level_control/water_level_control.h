#ifndef water_level_control_h
#define water_level_control_h
 
#include <Arduino.h>

class WaterLevel
{ public:
   WaterLevel();
   bool check_status(void);
  private:
   bool value1;
   bool value2;
};
#endif
