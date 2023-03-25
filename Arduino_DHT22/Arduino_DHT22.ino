//=========================================================|
// How to use the DHT-22 sensor with Arduino uno
// Temperature and humidity sensor
//=========================================================|
#include "DHT.h"
//---------------------------------------------------------|
#define DHTPIN 2       // what digital pin we're connected
#define DHTTYPE DHT22  // DHT22  (AM2302), AM2321
//---------------------------------------------------------|
// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN
// Connect pin 2 in an 1k resistor and the resistor to VCC
// Connect pin 4 (on the right) of the sensor to GROUND
//---------------------------------------------------------|
// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);
//---------------------------------------------------------|
void setup() 
{
   Serial.begin(9600);
   Serial.println("DHT22 test");
   dht.begin();
}
//---------------------------------------------------------|
void loop()
{
   // Wait a few seconds between measurements.
   // DHT22 sensor reads only each 2 seconds.
   delay(2000);
   // Read the sensor takes about 250 milliseconds!
   float h = dht.readHumidity();
   // Read temperature as Celsius (isFahreheit = false)
   float t = dht.readTemperature(false);
   // Check if any reads failed and exit early (to try again).
   if (isnan(h) || isnan(t)) 
   {
      Serial.println("Failed to read from DHT sensor!");
      return;
   }
   // Compute heat index in Celsius (isFahreheit = false)
   float hic = dht.computeHeatIndex(t, h, false);
   Serial.print("Humidity: ");
   Serial.print(h);
   Serial.print(" %\t");
   Serial.print("Temperature: ");
   Serial.print(t);
   Serial.print(" *C \t");
   Serial.print("Heat index: ");
   Serial.print(hic);
   Serial.print(" *C ");
   Serial.println(" ");
}
//=========================================================|
