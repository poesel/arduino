#include <defines.h>
#include <Arduino.h>

#include <node_ble.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>



// ***** battery level *****
// BLE stuff
#define batteryLevelService BLEUUID((uint16_t)0x180F)
BLECharacteristic batteryLevelCharacteristic(BLEUUID((uint16_t)0x2A19), BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ);
BLEDescriptor batteryLevelDescriptor(BLEUUID((uint16_t)0x2901));

// ***** weight *****
// BLE stuff
#define weightService BLEUUID((uint16_t)0x181D)
BLECharacteristic weightFeaturesCharacteristic(BLEUUID((uint16_t)0x2A9E), BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ);
BLECharacteristic weightMeasurementCharacteristic(BLEUUID((uint16_t)0x2A9D), BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ);



void InitBLE() {
    BLEDevice::init(HIVEID);
    // Create the BLE Server
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Create the BLE Service
    BLEService *pBattery = pServer->createService(batteryLevelService);
    BLEService *pWeight = pServer->createService(weightService);

    pBattery->addCharacteristic(&batteryLevelCharacteristic);
    batteryLevelDescriptor.setValue("Voltage");
    batteryLevelCharacteristic.addDescriptor(&batteryLevelDescriptor);
    batteryLevelCharacteristic.addDescriptor(new BLE2902());

    pWeight->addCharacteristic(&weightFeaturesCharacteristic);
    pWeight->addCharacteristic(&weightMeasurementCharacteristic);

    
    pServer->getAdvertising()->addServiceUUID(batteryLevelService);
    pServer->getAdvertising()->addServiceUUID(weightService);

    pBattery->start();
    pWeight->start();
    
    // Start advertising
    pServer->getAdvertising()->start();
}

void SetBLEbatteryLevel(uint8_t level) {

    batteryLevelCharacteristic.setValue(&level, 1);
    batteryLevelCharacteristic.notify();
}