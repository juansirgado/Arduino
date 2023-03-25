//---------------------------------------------------------/
//          JSyA IT Innovation.
//       All rights reserved 2015.
//           www.jsya.com.br
//          Laser Module Test 
//---------------------------------------------------------/
const int lp = 13; // Laser Control Pin
// Morse code table configuration
const byte ROWS = 47; 
const byte COLS = 7;
// Morse code time configuration
// Users can adjuste DOT value
const int DOT          = 500;
// Do not alter values below 
// they are Morse standardized values 
const int DASH         = DOT * 3;
const int DOT_SPACE    = DOT;
const int LETTER_SPACE = DASH;
const int WORD_SPACE   = DASH * 3;
// Morse code values table
const char morse[ROWS][COLS] = 
{
   {'A', '0', '1'},
   {'B', '1', '0', '0', '0'},
   {'C', '1', '0', '1', '0'},
   {'D', '1', '0', '0'},
   {'E', '0'},
   {'F', '0', '0', '1', '0'},
   {'G', '1', '1', '0'},
   {'H', '0', '0', '0', '0'},
   {'I', '0', '0'},
   {'J', '0', '1', '1', '1'},
   {'K', '1', '0', '1'},
   {'L', '0', '1', '0', '0'},
   {'M', '1', '1'},
   {'N', '1', '0'},
   {'O', '1', '1', '1'},
   {'P', '0', '1', '1', '0'},
   {'Q', '1', '1', '0', '1'},
   {'R', '0', '1', '0'},
   {'S', '0', '0', '0'},
   {'T', '1'},
   {'U', '0', '0', '1'},
   {'V', '0', '0', '0', '1'},
   {'W', '0', '1', '1'},
   {'X', '1', '0', '0', '1'},
   {'Y', '1', '0', '1', '1'},
   {'Z', '1', '1', '0', '0'},
   {'0', '1', '1', '1', '1', '1'},
   {'1', '0', '1', '1', '1', '1'},
   {'2', '0', '0', '1', '1', '1'},
   {'3', '0', '0', '0', '1', '1'},
   {'4', '0', '0', '0', '0', '1'},
   {'5', '0', '0', '0', '0', '0'},
   {'6', '1', '0', '0', '0', '0'},
   {'7', '1', '1', '0', '0', '0'},
   {'8', '1', '1', '1', '0', '0'},
   {'9', '1', '1', '1', '1', '0'},
   {'.', '0', '1', '0', '1', '0', '1'},
   {',', '1', '1', '0', '0', '1', '1'},
   {'?', '0', '0', '1', '1', '0', '0'},
   {':', '1', '1', '1', '0', '0', '0'},
   {';', '1', '0', '1', '0', '1', '0'},
   {'\'', '0', '1', '1', '1', '1', '0'},
   {'-', '0', '1', '1', '1', '1', '0'},
   {'/', '1', '0', '0', '1', '0'},
   {'(', '1', '0', '1', '1', '0'},
   {')', '1', '0', '1', '1', '0', '1'}
};
//---------------------------------------------------------/
void setup() 
{
   // Pointing the laser to up/top we have:
   // Left   = S   = Signal conect to Pin 13 for control 
                         // or to 5V for allways ON
   // Center = 5V  = Optional / Not necessary 
   // Right  = GND = Ground
   pinMode(lp,OUTPUT);
}
//---------------------------------------------------------/
void loop() 
{
   String message = "TESTE 123...";
   for(int i = 0; i < message.length(); i++)
   {
      char l = message.charAt(i);
      Serial.println(l);
      for(int r = 0; r < ROWS; r++)
      {
         if(morse[r][0] == ' ')
         {
            delay(WORD_SPACE);
         }
         else if(morse[r][0] == l)
         {
            send_morse(r);
         }
      } 
   delay(LETTER_SPACE);
   }
   delay(WORD_SPACE);
}
//---------------------------------------------------------/
void send_morse(int r)
{
   String str_code = morse[r];
   int s = str_code.length();
   for(int c = 1; c < s; c++)
   {
      if(morse[r][c] == 0)
      {
         laser_ON(DOT);
         laser_OFF(DOT_SPACE);
      }
      else if (morse[r][c] == 1)
      {
         laser_ON(DASH);
         laser_OFF(DOT_SPACE);
      }
   } 
}
//---------------------------------------------------------/
void laser_ON(int ms)
{
   digitalWrite(lp, HIGH);
   delay(ms);
}
//---------------------------------------------------------/
void laser_OFF(int ms)
{
   digitalWrite(lp, LOW);
   delay(ms);
}
//---------------------------------------------------------/
