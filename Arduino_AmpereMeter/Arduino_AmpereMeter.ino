//=========================================================|
// Measuring Tension(V) and Current(A) Using ACS712
//=========================================================|
const int analogIn = A2;
// Use 185=5A, 100=20A or 66=30A Module
int mVperAmp = 100; 
int RawValue= 0;
// ACS712 Offset = 2.5V (Volts per Amps) rate.
int ACSoffset = 2500;
double Voltage = 0;
double Amperes = 0;
//---------------------------------------------------------|
void setup()
{ 
   Serial.begin(9600);
}
//---------------------------------------------------------|
void loop()
{
   RawValue = analogRead(analogIn);
   // mV = pin Voltage / pin range * Voltage rate 5:1 * mVolts.
   Voltage = (RawValue / 1024.0) * 5.0 * 1000.0; 
   Amperes = ((Voltage - ACSoffset) / mVperAmp);
   // Convert to mVolts to Volts.
   Voltage /= 1000.0;
   // Show the read and computed values.
   Serial.print("Raw Value = " );
   Serial.print(RawValue);
   Serial.print("\t Volts = ");
   Serial.print(Voltage,4);
   Serial.print("\t Amps = ");
   Serial.println(Amperes,4);
   delay(2500);
}
//=========================================================|
