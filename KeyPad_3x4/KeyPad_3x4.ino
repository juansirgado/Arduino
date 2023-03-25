//---------------------------------------------------------/
//          JSyA IT Innovation.
//       All rights reserved 2015.
//           www.jsya.com.br
//       KeyPad Keyboard and Mouse 
//---------------------------------------------------------/
#include "Arduino.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Keypad.h"
//---------------------------------------------------------/
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

char keys[ROWS][COLS] = 
{
   {'1', '2', '3'},
   {'4', '5', '6'},
   {'7', '8', '9'},
   {'*', '0', '#'}
};

byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2};    //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//---------------------------------------------------------/
void setup() 
{
   // Start Serial
   Serial.begin(9600);
   // Start Keyboard
   Keyboard.begin();
   // Start Mouse
   Mouse.begin();

   // keypad.addEventListener(keypadEvent);  // Add an event listener.
   keypad.setHoldTime(150);              // Default is 1000mS
   keypad.setDebounceTime(50);           // Default is 50mS
}
//---------------------------------------------------------/
void loop() 
{

  char key = keypad.getKey();
   // char key = keypad.waitForKey();

   if (key == '*' || key == '#')
   {
      int  state =  PRESSED; // IDLE, PRESSED, RELEASED or HOLD
//      while(state == PRESSED)
      {
         run_command(key);
         state = keypad.getState();
      }
      Serial.print("Key = [");
      Serial.print(key);
      Serial.println("];");
      Serial.print("State = [");
      Serial.print(state);
      Serial.println("];");
   }
   else if (key != NO_KEY)
   {
      run_command(key); 
      // key_type();
      // mouse_move();
   }
}
//---------------------------------------------------------/
void run_command(char key)
{
   if (key == '1')
   {
      Keyboard.print("sirgadoa");
      Keyboard.write(KEY_RETURN);
      delay(100);
      Keyboard.press(71+136);
      Keyboard.release(71+136);
   }
   if (key == '2')
   {
      Keyboard.print("antico09");
      Keyboard.write(KEY_RETURN);
   }
   if (key == '3')
   {
      Keyboard.print("segredo0987");
      Keyboard.write(KEY_RETURN);
   }
   if (key == '4')
   {
      Keyboard.print("jsirgado");
      Keyboard.write(KEY_TAB);
   }
   if (key == '5')
   {
      Keyboard.print("juan.sirgado");
      Keyboard.write(KEY_TAB);
   }
   if (key == '6')
   {
      Keyboard.print("juan.sirgado@gmail.com");
      Keyboard.write(KEY_TAB);
      delay(100);
      Keyboard.print("sirgadoa");
      Keyboard.write(KEY_RETURN);
   }
   if (key == '7')
   {
      Keyboard.print("juan.sirgado");
      Keyboard.write(KEY_TAB);
      delay(100);
      Keyboard.print("jusian09");
      Keyboard.write(KEY_RETURN);
   }
   if (key == '8')
   {
      Keyboard.print("juan.sirgado");
      Keyboard.write(KEY_RETURN);
      delay(2000);
      Keyboard.print("jusian09");
      Keyboard.write(KEY_RETURN);
   }
   if (key == '9')
   {
      Keyboard.print("juan.sirgado@hotmail.com");
      Keyboard.write(KEY_RETURN);
      delay(1000);
      Keyboard.print("jusian09");
      Keyboard.write(KEY_RETURN);
   }
   if (key == '*')
   {
      Mouse.click(MOUSE_LEFT);
      delay(100);
   }
   if (key == '0')
   {
      Keyboard.print("sirgadoa");
      Keyboard.write(KEY_RETURN);
   }
   if (key == '#')
   {
      Mouse.click(MOUSE_RIGHT);
      delay(100);
   }
   if (key == '?')
   {
      int state = keypad.getState(); // IDLE, PRESSED, RELEASED or HOLD
      boolean change = keypad.keyStateChanged();
      digitalWrite(13, HIGH);        // Turns the LED on.
      Serial.print("Key = [");
      Serial.print(key);
      Serial.println("];");
      Serial.print("State = [");
      Serial.print(state);
      Serial.println("];");
      Serial.print("Change = [");
      Serial.print(change);
      Serial.println("];");
      digitalWrite(13, LOW);         // Turns the LED off.
   }
}
//---------------------------------------------------------/
void key_type()
{
   // type test normal
   Keyboard.write(KEY_RETURN);
   Keyboard.print("teste 1234...");
   delay(1500);

   // type test caps_lock
   Keyboard.write(KEY_RETURN);
   Keyboard.write(KEY_CAPS_LOCK);
   Keyboard.print("teste 1234...");
   Keyboard.write(KEY_CAPS_LOCK);
   delay(1500);

   // type test shift
   Keyboard.write(KEY_RETURN);
   Keyboard.press(KEY_LEFT_SHIFT);
   Keyboard.print("teste 1234...");
   Keyboard.releaseAll();
   delay(1500);

   // type test new line
   Keyboard.write(KEY_RETURN);
   delay(1500);
}
//---------------------------------------------------------/
void mouse_move()
{
   // move mouse up
   Mouse.move(0,-40,0);
   delay(1500);

   // move mouse down
   Mouse.move(0,40,0);
   delay(1500);

   // move mouse left
   Mouse.move(-40,0,0);
   delay(1500);

   // move mouse right
   Mouse.move(40,0,0);
   delay(1500);

   // mouse left click
   Mouse.click(MOUSE_LEFT);
   delay(1500);

   // mouse right click
   Mouse.click(MOUSE_RIGHT);
   delay(1500);
}
//---------------------------------------------------------/
