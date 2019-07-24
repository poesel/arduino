#include <defines.h>
#include <arduino.h>

uint8_t readBatteryLevel(int pin, int zero) {

    uint8_t mapped = 0;
    int value = analogRead(pin);
    if (value < zero) { value = zero; };        // any value below zero is 0% bettery load
    mapped = map(value, zero, 4095, 0, 100);
    Serial.println('v ' + value + 'z ' + zero + 'm ' + mapped);
    return mapped;
    // TODO: map value with actual unloading curve (capacity)
 }
