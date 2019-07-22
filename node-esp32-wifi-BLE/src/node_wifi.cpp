#include <defines.h>
#include <Basecamp.hpp>

void setup_webpage (Basecamp & iot) {

    String weight01 = "12.3";
    iot.configuration.set("weight01", weight01);
    iot.configuration.save();
    #ifdef SCALE        
        iot.web.addInterfaceElement("scaleDisplay", "input", "Gewicht: ", "#configform", "weight01");
        iot.web.setInterfaceElementAttribute("scaleDisplay", "readonly", "true");
        #ifdef TWOSCALES
            iot.web.addInterfaceElement("scaleDisplay2", "input", "Gewicht 2: ", "#configform", "weight02");
            iot.web..setInterfaceElementAttribute("scaleDisplay2", "readonly", "true");
        #endif
    #endif
/*
    #ifdef BATTERYLEVEL
        iot.configuration.set("battery01", String(BatteryLevel));
        iot.configuration.save();
        iot.web.addInterfaceElement("batteryDisplay", "input", "Akku: ", "#configform", "battery01");
        iot.web.setInterfaceElementAttribute("batteryDisplay", "readonly", "true");
    #endif
*/
}
