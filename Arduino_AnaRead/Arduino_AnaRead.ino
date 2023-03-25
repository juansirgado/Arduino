/*---------------------------------------------------------\
|    From: Ekobots Innovation Ltda - www.ekobots.com.br    |
|       by: Juan Sirgado y Antico - www.jsya.com.br        |
|----------------------------------------------------------|
|              Program SD_CARD - 2019/09/28                |
|                All rights reserved 2019                  |
|---------------------------------------------------------*/
//---------------------------------------------------------|
const int currentPin = A1;
int readValue = 0;
int countValue = 0;
int delayValue = 5000;
int sensitValue = 100;
double start_time = 0.0;
double totalValue = 0.0;
double voltsValue = 0.0;
double ampsValue = 0.0;
double offsetValue = 0.0;
//---------------------------------------------------------|
void setup()
{
   Serial.begin(19200);
   // calc offset value no current;
   calc_amps();
   offsetValue = ampsValue;
   print_amps();
}
//---------------------------------------------------------|
void loop()
{
   // calc current value;
   calc_amps();
   print_amps();
}
//---------------------------------------------------------|
void calc_amps()
{
   totalValue = 0;
   countValue = 0;
   start_time = millis();
   while((millis() - start_time) < 2000)
   {
      readValue = analogRead(currentPin);
      // Serial.print(" Analog Read: ");
      // Serial.println(readValue); 
      // Altering the range from 1024 to 512 without signal;
      // The values represente the range from -20A to +20A;
      // All positive values for the senoidal wave.
      // Multiply by 5V, Arduino analog port Max voltage.
      // Divide by 512 the new range for the values;     
      voltsValue = abs(readValue - 512) * 5.0 / 512.0;
      totalValue = totalValue + sq(voltsValue);
      countValue++;
      delayMicroseconds(1492);
   }
   // Rate over 2000 milliseconds adjusted;
   // It is the square root of the sum of squares;
   // All divided by the quantity of squares;
   // Subtract the offset to adjust the 0 Amps in the sensor;
   // Apply sensor ACS712 20A sensitivity;
   ampsValue = sqrt(totalValue / countValue) - offsetValue;
}
//---------------------------------------------------------|
void print_amps()
{
   Serial.print(" Amps Current: ");
   Serial.print(ampsValue,4);
   Serial.print(" Samples: ");
   Serial.println(countValue);
   delay(delayValue);
}
//---------------------------------------------------------|
