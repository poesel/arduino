#include <arduino.h>

int readBatteryLevel(int pin, int zero) {

    int value = analogRead(pin);
    if (value < zero) { value = zero; };        // any value below zero is 0% bettery load
    return( map(value, zero, 4095, 0, 100));
    // TODO: map value with actual unloading curve (capacity)
 }
