#include <Wire.h> //*Include the Wire library which allows to use the I2C interface*
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h> //*library to easily take readings from the sensor*
#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

#define BLYNK_PRINT Serial

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourSSID";
char pass[] = "YourPassword";

#define SEALEVELPRESSURE_HPA (1018.2)

Adafruit_BME280 bme; //*Declare the bme variable, an easy to remember reference for the device*

unsigned long delayTime;
BlynkTimer timer; // Create a Timer object called "timer"

void setup() {
    //Every serial line is for debugging purposes. Uncomment them to check if sensor works when connected via USB
    //Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
    //Serial.println(F("BME280 test"));

    bool status;
    
    status = bme.begin();  //*Try to start the device*
    if (!status) { //*If it is not starting, print message*
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1); //* Go in an endless loop. This prevents the Arduino from calling the loop function*
    }
    
    //Serial.println("-- Default Test --");
    delayTime = 1000;

    //Serial.println();
    timer.setInterval(1000L, sendUptime); //  Here you set interval (1sec) and which function to call
}

void sendUptime()
{
  // This function sends Arduino up time every 1 second to Virtual Pin (V5)
  // In the app, Widget's reading frequency should be set to PUSH
  // You can send anything with any interval using this construction
  // Don't send more that 10 values per second

  Blynk.virtualWrite(V5, bme.readTemperature()); //Vx are the virtual pins that we use on the app interface
  Blynk.virtualWrite(V4, bme.readPressure() / 100.0F);
}

void loop() { 
    Blynk.run();
    timer.run(); // BlynkTimer is working...
    //printValues();
    delay(delayTime);
}

//void printValues() {
  //Serial.print("Temperature = "); //*Read and print temperature*
  //Serial.print(bme.readTemperature());
  //Serial.println(" *C");

  //Serial.print("Pressure = "); //*Read and print pressure*
  //Serial.print(bme.readPressure() / 100.0F);
  //Serial.println(" hPa"); // Calculate altitude assuming 'standard' barometric pressure of 1013.25 millibar = 101325 Pascal

  //Serial.print("Approx. Altitude = ");
  //Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA)); //*Read and print altitude*
  // you can get a more precise measurement of altitude if you know the current sea level pressure which willvvary with weather and such. If it is 1015 millibars that is equal to 101500 Pascals
  //Serial.println(" m");
  //Serial.print("Humidity = ");
  //Serial.print(bme.readHumidity()); //*Read and print humidity*
  //Serial.println(" %");
  //Serial.println();
}
