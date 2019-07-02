#include <Arduino.h>
#include <Basecamp.hpp>
#include <HX711_ADC.h>

#include <node_wifi.h>
#include <battery.h>
#include <scale.h>


// comment in options you need
#define WIFI             // enables webserver and MQTT
//#define BLE             // enable BLE functionality
#define SCALE            // if scale is attached
//#define TWOSCALES       // if another scale for a different hive is attached
#define BATTERYLEVEL     // measure battery level

//Variables for battery level
static const int BatteryPin = 33;
float batteryLimit = 360.0f;  // defines the point at which the battery is considered empty in [V] * 100
int batteryZero = round(batteryLimit / 420.0 * 4095.0); // 4096 = resolution of analog input
int BatteryLevel = 0; 
String batteryTopic;
String batteryValueTopic;

//HX711 constructor (dout pin, sck pin):
static const int HX711DOutPin = 4;
static const int HX711SCKPin = 5;
HX711_ADC LoadCell(HX711DOutPin, HX711SCKPin);
int eepromAdress = 0;

Basecamp iot{
        Basecamp::
        SetupModeWifiEncryption::
        secured
      };

void setup() {
    
    Serial.begin(115200);

    iot.configuration.set("OTAPassword", "qwe");
    iot.configuration.set("OTAActive", "true");

    #ifdef WIFI
      iot.begin();
      setup_webpage();
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

  Serial.println("Zero:");
  Serial.println(batteryZero);
  #ifdef BATTERYLEVEL
    BatteryLevel = readBatteryLevel(BatteryPin, batteryZero);
    Serial.println("Level:");
    Serial.println(BatteryLevel);
  #endif
  #ifdef SCALE
    LoadCell.begin();
  #endif

}