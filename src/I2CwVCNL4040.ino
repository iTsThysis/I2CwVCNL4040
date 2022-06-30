SYSTEM_MODE(MANUAL)
SYSTEM_THREAD(ENABLED)

#include "oled-wing-adafruit.h"
#include "Wire.h"


//Wire.begin(0x60);

void setup() {
  // Put initialization like pinMode and begin functions here.
  Wire.begin(); 
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

}