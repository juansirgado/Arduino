/*---------------------------------------------------------\
|    From: Ekobots Innovation Ltda - www.ekobots.com.br    |
|       by: Juan Sirgado y Antico - www.jsya.com.br        |
|----------------------------------------------------------|
|             Program Multimetro - 2019/09/23              |
|                All rights reserved 2019                  |
|---------------------------------------------------------*/
#include <SPI.h>
//---------------------------------------------------------|
#include <TimeLib.h>
 // setTime(hour,minute,second,day,month,year);
 // hour();    // The hour now (0-23)
 // minute();  // The minute now (0-59)
 // second();  // The second now (0-59)
 // weekday(); // Day of the week (1-7), Sunday is day 1
 // day();     // The day now (1-31)
 // month();   // The month now (1-12)
 // year();    // The full four digit year: (2009, 2010 etc)
//---------------------------------------------------------|
#include <LiquidCrystal.h>
 // LCD RS pin to Arduino digital pin 7
 // LCD (E)nable pin to Arduino digital pin 6
 // LCD D4 pin to Arduino digital pin 5
 // LCD D5 pin to Arduino digital pin 4
 // LCD D6 pin to Arduino digital pin 3
 // LCD D7 pin to Arduino digital pin 2
 LiquidCrystal lcd(7,6,5,4,3,2);
//---------------------------------------------------------|
#include <SD.h>
// Arduino GND – SD Card GND pin
// Arduino VIN – SD Card VCC pin (+5V)
// Arduino D10 – SD Card CS pin 
// Arduino D11 – SD Card MOSI pin (SI)
// Arduino D12 – SD Card MISO pin (SO)
// Arduino D13 – SD Card SCK pin (CLK)
//---------------------------------------------------------|
// Current sensor "ACS712" 
// Use sensitivity 5A=185, 20A=100, 30A=66;
const int currentPin = A0;
const int sensitValue = 100;
int ampsSensor = 0;
int countValue = 0;
double start_time = 0.0;
double totalValue = 0.0;
double voltsValue = 0.0;
double ampsValue = 0.0;
double offsetValue = 0.0;
//---------------------------------------------------------|
// Tension sensor "0V-25V"
// For fine tune adjust the value of fcor to your sensor;
const int tensionPin = A2;
const double corrValue = 0.92;
int voltsSensor = 0;
double voutValue = 0.0;
double R1Value = 30000.0;
double R2Value = 7500.0;
//---------------------------------------------------------|
// SD card shield
File myFile;
//---------------------------------------------------------|
const int delayValue = 2000;
double amperageValue = 0.0;  // Tension (Amps);
double voltageValue  = 0.0;  // Current (Volts);
double wattageValue  = 0.0;  // Power   (Watts);
//=========================================================|
void setup() 
{
   // Set Current Date and Time;
   setTime(0,0,0,1,1,2000);
   // Set sensors pin mode;
   pinMode(currentPin, INPUT);
   pinMode(tensionPin, INPUT);
   // Start serial;
   Serial.begin(9600);
   // Start LCD;
   lcd.begin(16,2);
   // Start SD Card;
   SD.begin(10);
   print_hello();
   delay(delayValue);
   calc_offset();
   delay(delayValue);
   blink_led();
}
//---------------------------------------------------------|
void loop()
{
   calc_volts();  
   print_volts();
   calc_amps();
   print_amps();
   calc_watts();
   print_watts();
//   print_sensors();
   blink_led();  
   write_sd_card;
   delay(delayValue);
}
//---------------------------------------------------------|
void calc_volts()
{
   // read the value at analog input
   voltsSensor = analogRead(tensionPin);
   // Arduino Analog pin 5V, Sensor Max 25V --> 5:1.
   // Range in the pin is 0 to 1023.
   voutValue = (voltsSensor * 5.0) / 1024.0;
   // Ohms law: Vout = Vin * Rpartial / Rtotal
   voltageValue = voutValue / (R2Value / (R1Value + R2Value)) * corrValue;
}
//---------------------------------------------------------|
void calc_amps()
{
   totalValue = 0;
   countValue = 0;
   start_time = millis();
   while((millis() - start_time) < 2000)
   {
      ampsSensor = analogRead(currentPin);
      // Serial.print(" Analog Read: ");
      // Serial.println(readValue);
      // Altering the range from 1024 to 512 without signal;
      // The values represent the range from -20A to +20A;
      // All positive values for the senoidal wave;
      // Multiply by 5V, Arduino analog port Max voltage;
      // Divide by 512 the new range for the values; 
      voltsValue = abs(ampsSensor - 512) * 5.0 / 512.0;
      // sum of squares; 
      totalValue = totalValue + sq(voltsValue);
      // number of squares;
      countValue++;
      delayMicroseconds(1492);
   }
   // Rate over 2000 milliseconds adjusted;
   // It is the square root of the sum of squares;
   // All divided by the quantity of squares;
   // Subtract the offset to adjust the 0 Amps in the sensor;
   // Apply sensor ACS712 20A sensitivity;
   amperageValue = (sqrt(totalValue / countValue) - offsetValue) * 100;
}
//---------------------------------------------------------|
void calc_watts()
{
   wattageValue = voltageValue * amperageValue;
}
//---------------------------------------------------------|
void calc_offset()
{
   // Offset amperage calculation
   calc_amps();
   offsetValue = amperageValue;
}
//---------------------------------------------------------|
void write_sd_card()
{
   // File is open;
   digitalWrite(13,HIGH);
   // Open file for write;
   myFile = SD.open("datetime.txt", FILE_WRITE);
   delay(90);
   if (myFile) 
   {
      myFile.print("Date-Time:(YYYY-MM-DD,W,HH:MM:SS) ");
      myFile.print(year());
      myFile.print("-");
      if(month()<10) myFile.print("0");
      myFile.print(month());
      myFile.print("-");
      if(day()<10) myFile.print("0");
      myFile.print(day());
      myFile.print(",");
      myFile.print(weekday());
      myFile.print(",");
      if(hour()<10) myFile.print("0");
      myFile.print(hour());
      myFile.print(":");
      if(minute()<10) myFile.print("0");
      myFile.print(minute());
      myFile.print(":");
      if(second()<10) myFile.print("0");
      myFile.print(second());
      myFile.println(";");
   }
   else 
   {
      // Open fail print an error:
      Serial.println("Error opening the file");
   }
   // Close file;
   myFile.close();
   delay(50);
   // File is closed;
   digitalWrite(13,LOW);
}
//---------------------------------------------------------|
void blink_led()
{
   // end exec loop
   for(int l=0;l<=9;l++)
   {
     digitalWrite(13,HIGH);
     delay(10);
     digitalWrite(13,LOW);
     delay(10);
   }
}
//---------------------------------------------------------|
void print_hello()
{
   // display the Hello message
   Serial.println("Current Sensor with Arduino.");
   lcd.setCursor(0,0);
   lcd.print(" Current Sensor ");
   lcd.setCursor(0,1);
   lcd.print("  with Arduino.  ");
}
//---------------------------------------------------------|
void print_sensors()
{
   // display tension(V) sensor read
   Serial.print("Sensor 0V-25V Value = " );
   Serial.println(voltsSensor);
   Serial.print("Sensor ACS712 Value = " );
   Serial.println(ampsSensor);
   lcd.clear();
   delay(100);
   lcd.setCursor(0,0);
   lcd.print("0V-25V: ");
   lcd.setCursor(10,0);
   lcd.print(voltsSensor);
   lcd.setCursor(0,1);
   lcd.print("ACS712: ");
   lcd.setCursor(10,1);
   lcd.print(ampsSensor);
}
//---------------------------------------------------------|
void print_volts()
{
   // display the Tension in Volts
   Serial.print("Tension-Voltage(V) = ");
   Serial.println(voltageValue,3);
   lcd.clear();
   delay(100);
   lcd.setCursor(0,0);
   lcd.print("Tension-Voltage");
   lcd.setCursor(3,1);
   lcd.print(voltageValue,3);
   lcd.setCursor(12,1);
   lcd.print("V");
 }
//---------------------------------------------------------|
void print_amps()
{
   // display the Current in Amperes
   Serial.print("Current-Amperage(A) = ");
   Serial.println(amperageValue,4);
   lcd.clear();
   delay(100);
   lcd.setCursor(0,0);
   lcd.print("Current-Amperage");
   lcd.setCursor(3,1);
   lcd.print(amperageValue,4);
   lcd.setCursor(12,1);
   lcd.print("A");
}
//---------------------------------------------------------|
void print_watts()
{
   // display the Power in Watts
   Serial.print("Power-Wattage(W) = ");
   Serial.println(wattageValue,2);
   lcd.clear();
   delay(100);
   lcd.setCursor(0,0);
   lcd.print(" Power-Wattage");
   lcd.setCursor(3,1);
   lcd.print(wattageValue,2);
   lcd.setCursor(12,1);
   lcd.print("W");
}
//---------------------------------------------------------|
void print_offset()
{
   // display the offset Tension in Volts
   Serial.print("Offset-Voltage(V) = ");
   Serial.println(offsetValue,3);
   lcd.clear();
   delay(100);
   lcd.setCursor(0,0);
   lcd.print("Offset-Voltage");
   lcd.setCursor(3,1);
   lcd.print(offsetValue,3);
   lcd.setCursor(12,1);
   lcd.print("V");
}
//=========================================================|
