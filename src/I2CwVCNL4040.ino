SYSTEM_THREAD(ENABLED)

#include "oled-wing-adafruit.h"
#include "Wire.h"
#include "SparkFun_VCNL4040_Arduino_Library.h"
#include "blynk.h"
VCNL4040 proximitySensor;
OledWingAdafruit display;

bool proximity = true;
bool ambient = false;
bool app = false;
 

BLYNK_READ(V0) {
  unsigned int proxValue = proximitySensor.getProximity(); 
  Blynk.virtualWrite(V0, proxValue);
  if (0 < proxValue && proxValue < 100) {
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
    digitalWrite(D8, HIGH);
  } else if (100 < proxValue && proxValue < 2500) {
    digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);
    digitalWrite(D8, LOW);
  } else if (2500 < proxValue && proxValue < 9000) {
    digitalWrite(D6, HIGH);
    digitalWrite(D7, LOW);
    digitalWrite(D8, LOW);
  }
}


//Wire.begin(0x60);
void displaySetup() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
}
void getProximity() {
  displaySetup();
  unsigned int proxValue = proximitySensor.getProximity(); 
  display.print("Proximity Value: ");
  display.print(proxValue);
  display.println();
  delay(10);
  display.display();
  if (0 < proxValue && proxValue < 100) {
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
    digitalWrite(D8, HIGH);
  } else if (100 < proxValue && proxValue < 2500) {
    digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);
    digitalWrite(D8, LOW);
  } else if (2500 < proxValue && proxValue < 9000) {
    digitalWrite(D6, HIGH);
    digitalWrite(D7, LOW);
    digitalWrite(D8, LOW);
  }
}

void getAmbient() {
  displaySetup();
  proximitySensor.powerOnAmbient();
  unsigned int ambientValue = proximitySensor.getAmbient(); 
  display.print("Ambient light level: ");
  display.println(ambientValue);
  display.display();
}
void setup() {
  pinMode(D8, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D6, OUTPUT);
  display.setup();
  displaySetup();
  display.setTextColor(WHITE);
  display.println("SparkFun VCNL4040 Example");
  display.display();
  Blynk.begin("HhSNoHZh0Hi4I6iE2vwwLouu1urhKPF3", IPAddress(167, 172, 234, 162), 8080);
  Wire.begin(); 
  if (proximitySensor.begin() == false) {
    displaySetup();
    display.println("Device not found. Please check wiring.");
    display.display();
    while (1);
  }
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  display.loop();
  if (display.pressedA()) {
    proximity = true;
    ambient = false;
    app = false;
  }  
  if (display.pressedB()) {
    proximity = false;
    ambient = true;
    app = false;
  }
  if (display.pressedC()) {
    proximity = false;
    ambient = false;
    app = true;
  }
  if (proximity == true) {
    getProximity();
  }
  if (ambient == true) {
    getAmbient();
  }
  if (app == true) {
    displaySetup();
    Blynk.run();
    display.display();
  }
}