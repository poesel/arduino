#include <defines.h>
#include <Arduino.h>


//variabls for blinking an LED with Millis
const int led = 21; // ESP32 Pin to which onboard LED is connected
unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval = 2000;  // interval at which to blink (milliseconds)
int ledState = LOW;  // ledState used to set the LED

#ifdef WIFI
  #include <Basecamp.hpp>
  #include <node_wifi.h>
  Basecamp iot{
        Basecamp::
        SetupModeWifiEncryption::
        secured
      };
#endif  

//Variables for battery level
#ifdef BATTERYLEVEL
  #include <battery.h>
  static const int BatteryPin = 34;
  float batteryLimit = 360.0f;  // defines the point at which the battery is considered empty in [V] * 100
  int batteryZero = round(batteryLimit / 420.0 * 4095.0); // 4096 = resolution of analog input
  int BatteryLevel = 0; 
  String batteryTopic;
  String batteryValueTopic;
#endif
#ifdef SCALE
  #include <HX711_ADC.h>
  #include <scale.h>
  //HX711 constructor (dout pin, sck pin):
  static const int HX711DOutPin = 4;
  static const int HX711SCKPin = 5;
  HX711_ADC LoadCell(HX711DOutPin, HX711SCKPin);
  //int eepromAdress = 0;
#endif
#ifdef BLE
  #include <node_ble.h>
#endif


void setup() {

  pinMode(led, OUTPUT);    
  Serial.begin(115200);

  
  #ifdef WIFI
    iot.configuration.set("OTAActive", "true");
    setup_webpage(iot);
    iot.begin();
  #endif
  #ifdef BLE
    InitBLE();
  #endif
  #ifdef BATTERYLEVEL
    pinMode(BatteryPin, INPUT);
    #ifdef WIFI
      batteryTopic = "stat/" + iot.hostname + "/battery";
      batteryValueTopic = "stat/" + iot.hostname + "/batteryvalue";
    #endif
  #endif

}

void loop() {


  //test loop
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    ledState = not(ledState);
    // set the LED with the ledState of the variable:
    digitalWrite(led,  ledState);

    #ifdef BATTERYLEVEL
      BatteryLevel = readBatteryLevel(BatteryPin, batteryZero);
      Serial.println(BatteryLevel);
      SetBLEbatteryLevel(BatteryLevel);
      Serial.println(BatteryLevel);
    #endif
    #ifdef SCALE
      LoadCell.begin();
    #endif
 
  }

  
}