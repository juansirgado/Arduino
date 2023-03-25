//=========================================================|
//     Ekobots Innovation Ltda - www.ekobots.com.br        |
//        Juan Sirgado y Antico - www.jsya.com.br          |
//---------------------------------------------------------|
//        Program Magnetic Levitator - 2018/05/15          |
//               All rights reserved 2018                  |
//=========================================================|
int anaPin1 = 1;   // Arduino Analog Pin 1;
int anaPin2 = 2;   // Arduino Analog Pin 2;
int digPin1 = 5;   // Arduino Digital Pin 5;
int digPin2 = 6;   // Arduino Digital Pin 6;
int digPin3 = 10;  // Arduino Digital Pin 10;
int digPin4 = 11;  // Arduino Digital Pin 11;
int addPin1 = 4;   // Arduino Digital Pin 4;
int subPin1 = 7;   // Arduino Digital Pin 7;
int addPin2 = 8;   // Arduino Digital Pin 8;
int subPin2 = 12;  // Arduino Digital Pin 12;
//
int     anaValX = 0;  // Analogic read(hall effect sensor 1 X axis) value;
int     anaValY = 0;  // Analogic read(hall effect sensor 2 Y axis) value;
boolean digValR = 0;  // Digital write(electromagnet X Rigth) value;
boolean digValL = 0;  // Digital write(electromagnet X Left) value;
boolean digValF = 0;  // Digital write(electromagnet Y Front) value;
boolean digValB = 0;  // Digital write(electromagnet Y Back) value;
//
int levValX = 228;   // Levitation point value for the X axis;
int levValY = 228;   // Levitation point value for the Y axis;
int dlyVal = 250;    // Delay in micro seconds(Electromagnet frequency);
//---------------------------------------------------------|
void setup()
{
   // Levitator initialization begin; 
   Serial.begin(57600);
   Serial.println("Levitator by JSyA");
   Serial.println("Starting...");
   // Digital pins work mode setup;
   pinMode(digPin1, OUTPUT);
   pinMode(digPin2, OUTPUT);
   pinMode(digPin3, OUTPUT);
   pinMode(digPin4, OUTPUT);
   pinMode(addPin1, INPUT_PULLUP);
   pinMode(subPin1, INPUT_PULLUP);
   pinMode(addPin2, INPUT_PULLUP);
   pinMode(subPin2, INPUT_PULLUP);
   // Levitator initialization end; 
   Serial.println("Started.");
}
//---------------------------------------------------------|
void loop() 
{
   // Hall effect sensor read (magnetic field intensity) X axis;
   anaValX = analogRead(anaPin1);
   // Hall effect sensor read (magnetic field intensity) X axis;
   anaValY = analogRead(anaPin2);
   // Levitation point fine tune with the switches;
   lev_point();
   // Check the levitation point X axis;
   digValR = LOW;
   digValL = LOW;
   if (anaValX < levValX) digValR = HIGH;
   if (anaValX > levValX) digValL = HIGH;
   // Check the levitation point Y axis;
   digValF = LOW;
   digValB = LOW;
   if (anaValY > levValY) digValF = HIGH;
   if (anaValY < levValY) digValB = HIGH;
   // Turn ON/OFF the electromagnets;
   // With base on sensors value and the levitation points;
   digitalWrite(digPin1, digValR);
   digitalWrite(digPin2, digValL);
   digitalWrite(digPin3, digValF);
   digitalWrite(digPin4, digValB);
   delayMicroseconds(dlyVal);
}
//---------------------------------------------------------|
void lev_point()
// Levitation point fine tune with the switches;
{
     // Increase the value of levitation point X axis;
   if (digitalRead(addPin1) == LOW) 
   {
      levValX++;
      value_log();
      delay(250);
   }
   // Decrease the value Of levitation point X axis;
   if (digitalRead(subPin1) == LOW) 
   {
      levValX--;
      value_log();
      delay(250);
   }
     // Increase the value of levitation point Y axis;
   if (digitalRead(addPin2) == LOW) 
   {
      levValY++;
      value_log();
      delay(250);
   }
   // Decrease the value of levitation point Y axis;
   if (digitalRead(subPin2) == LOW) 
   {
      levValY--;
      value_log();
      delay(250);
   }
}
//---------------------------------------------------------|
void value_log()
// Analog/Digital/Levitation values print;
{
   // Show the hall effect sensor value for X;
   Serial.print("anaValX=[");
   Serial.print(anaValX); 
   Serial.print("]-");
   // Show the hall effect sensor value for Y;
   Serial.print("anaValY=[");
   Serial.print(anaValY); 
   Serial.print("]-");
   // Show the electromagnet Right state On=1/Off=0;
   Serial.print("digValR=[");
   Serial.print(digValR);
   Serial.print("]-");
   // Show the electromagnet Left state On=1/Off=0;
   Serial.print("digValL=[");
   Serial.print(digValL);
   Serial.print("]-");
   // Show the electromagnet Front state On=1/Off=0;
   Serial.print("digValF=[");
   Serial.print(digValF);
   Serial.print("]-");
   // Show the electromagnet Back state On=1/Off=0;
   Serial.print("digValB=[");
   Serial.print(digValB);
   Serial.print("]-");
   // Show the levitation point value X axis;
   Serial.print("levValX=[");
   Serial.print(levValX);
   Serial.print("]-");
   // Show the levitation point value Y axis;
   Serial.print("levValY=[");
   Serial.print(levValY);
   Serial.println("];");
}
//=========================================================|
