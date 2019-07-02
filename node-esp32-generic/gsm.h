#include <TinyGsmClient.h>
#include <SoftwareSerial.h>


class gsmmodem  {

  private:

    #if !defined(D5)
    #define D5 (14)
    #define D6 (12)
    #define D7 (13)
    #define D8 (15)
    #endif

    #define TINY_GSM_MODEM_SIM800
    #if defined(ESP8266)
      SoftwareSerial SerialAT(D7, D6); // RX, TX
    #else
      SoftwareSerial SerialAT(D5, D6); // RX, TX
    #endif
    // Client FOR GSM
    TinyGsm modem(SerialAT);
    TinyGsmClient client(modem);
    TinyGsmClient clientMQTT(modem);
    
    const char apn[]  = "pinternet.interkom.de";  //Abhängig vom Netzprovider - ggfs.auf eigene Provider  anpassen.
    const char user[] = "";                       //Abhängig vom Netzprovider - in Abhängigkeit vom Provider eintragen
    const char pass[] = "";                       //Abhängig vom Netzprovider - in Abhängigkeit vom Provider eintragen
    
    int gsm_csq;

  public:


  void gsm_setup() {
  
  
    // Set GSM module baud rate
    SerialAT.begin(9600);
    delay(3000);
  
    // Restart takes quite some time
    // To skip it, call init() instead of restart()
    Serial.println("Initializing modem...");
    modem.restart();
  
    // Unlock your SIM card with a PIN - falls SIM mit PIN belegt ist hier die PIN hinterlegen.
    // modem.simUnlock("1234");

  }

  void gsm_SleepModeOff() {

    modem.sendAT(GF("+CSCLK=0"));
    delay(1000);

  }
  
  void gsm_connect() {

    Serial.print("Waiting for network...");
    if (!modem.waitForNetwork()) {
      Serial.println(" fail");
      delay(10000);
      return;
    }
    Serial.println("Connected to mobil network");
  
    Serial.print("GPRS Connecting to ");
    Serial.print(apn);
    if (!modem.gprsConnect(apn, user, pass)) {
      Serial.println(" fail");
      delay(10000);
  
      // Falls die Verbindung mit dem GSM & GPRS Netz nicht klappt, legt sich der der ESP schlafen und wir starten im Anschluß von vorn.
      // GSM Modem stoppen

       gsm_disconnect();

      // Sleep für 60 Sekunden

      ESP.deepSleep(60 * 1000000, WAKE_RF_DEFAULT);
      delay(100);
      
      return;
    }
    
  Serial.println("GPRS Connection established");

  }


  void gsm_info() {
    
    gsm_csq = modem.getSignalQuality();
    volt_level = modem.getBattPercent();
    voltage = modem.getBattVoltage() / 1000.0F;
  
    Serial.println();
    Serial.println("Signal Qualität");
    Serial.println(gsm_csq);
  
    Serial.println("Batterie Level ");
    Serial.println(volt_level);
  
    Serial.println("Batterie Level ");
    Serial.println(voltage);
  
  }
  
    
  void gsm_disconnect() {
  
    // For dem Sleep  - Verbindung kappen
    Serial.println("GPRS Disconnect");
    modem.gprsDisconnect();
  
    // For dem Sleep  - Modem RadioOFF schalten 
    Serial.println("GSM Radio Off ");
    modem.radioOff();
  
    delay(1000);
  
    Serial.println("GSM Sleep Mode 2 Enablen ");
    gsm_SleepMode2On();
  
  }
  
  void gsm_SleepMode2On() {
  
    modem.sendAT(GF("+CSCLK=2"));
    delay(1000);
  
  }

};
