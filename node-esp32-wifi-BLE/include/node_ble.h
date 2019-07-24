#include <BLEServer.h>
#include <Arduino.h>
#include <defines.h>


class MyServerCallbacks : 


    public BLEServerCallbacks {

        bool _BLEClientConnected = false;

        void onConnect(BLEServer* pServer) {
        _BLEClientConnected = true;
        };

        void onDisconnect(BLEServer* pServer) {
        _BLEClientConnected = false;
        }
    };

void InitBLE();
void SetBLEbatteryLevel(uint8_t level);
