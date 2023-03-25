// Rotary Encoder

// PIN configuration:
// G left -> Arduino GND
// V left -> Arduino +5V
// SB -> Arduino D3 (Digital PIN 7)
// G right -> Arduino GND
// V right -> Arduino +5V
// SA -> Arduino D4 (Digital PIN 8)
 
// Clockwise increment pins value 
// Invert the pins value 3/4 for decrement
int encoder0PinA = 8;
int encoder0PinB = 7;
// Rotary encoder relative position.
int encoder0Pos = -1;
// Last value for PIN A
int encoder0PinALast = LOW;
// Current value for PIN A
int encoder0ValA = LOW;
// Current value for PIN B
int encoder0ValB = LOW;

void setup() 
{ 
   pinMode (encoder0PinA,INPUT);
   pinMode (encoder0PinB,INPUT);
   Serial.begin (9600);
   Serial.println ("Starting program...");
} 

void loop() 
{ 
   encoder0ValA = digitalRead(encoder0PinA);
   if ((encoder0PinALast == LOW) && (encoder0ValA == HIGH)) 
   {
      encoder0ValB = digitalRead(encoder0PinB);
      if (encoder0ValB == LOW) 
      {
         encoder0Pos--;
      } else {
         encoder0Pos++;
      }
      write_log();
   }  
   encoder0PinALast = encoder0ValA;
}

void write_log()
{
/*
    Serial.print ("Value A: ");
    Serial.print (encoder0ValA);
    Serial.print (" Value B: ");
    Serial.print (encoder0ValB);
    Serial.println (" ");
*/
    Serial.print ("Rotary encoder position: ");
    Serial.print (encoder0Pos);
    Serial.println (" ");
}
