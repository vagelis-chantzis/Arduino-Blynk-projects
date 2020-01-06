#include <Wire.h> //*Include the Wire library which allows to use the I2C interface*
#include "DHT.h"
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

//#define BLYNK_PRINT Serial

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "Zr2jJuRInIkQZxsABy6unGdlM1KZPPNh";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SlowerThanDeath2";
char pass[] = "MaStErOfPuPpEtS@16946261703";

unsigned long delayTime;
BlynkTimer timer; // Create a Timer object called "timer"

void setup() {
    //Every serial line is for debugging purposes. Uncomment them to check if sensor works when connected via USB
    //Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
    dht.begin();
    delayTime = 1000;    
    timer.setInterval(1000L, sendUptime); //  Here you set interval (1sec) and which function to call
}

void sendUptime()
{
  // This function sends Arduino up time every 1 second to Virtual Pin (V5)
  // In the app, Widget's reading frequency should be set to PUSH
  // You can send anything with any interval using this construction
  // Don't send more that 10 values per second

  Blynk.virtualWrite(V3, dht.readHumidity()); //Vx are the virtual pins that we use on the app interface
  Blynk.virtualWrite(V5, dht.readTemperature());  
}

void loop() { 
  delay(2000);
  Blynk.run();
  timer.run(); // BlynkTimer is working...
  delay(delayTime);
}
