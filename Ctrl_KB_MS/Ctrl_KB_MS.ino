void setup() 
{
   // Start Keyboard
   Keyboard.begin();
   // Start Mouse
   Mouse.begin();

   pinMode(2, INPUT_PULLUP);
   // Make pin 2 an input pullup switch connected to ground:
}
 
void loop() 
{

   while (digitalRead(2) == LOW) 
   {
      keytyper();
      delay(1000);
      mousemover();
      delay(1000);
   }
}
  
void keytyper()
{
   Keyboard.write(KEY_RETURN);
   Keyboard.print("teste 1234...");
   delay(1500);

   Keyboard.write(KEY_RETURN);
   Keyboard.write(KEY_CAPS_LOCK);
   Keyboard.print("teste 1234...");
   Keyboard.write(KEY_CAPS_LOCK);
   delay(1500);

   Keyboard.write(KEY_RETURN);
   Keyboard.press(KEY_LEFT_SHIFT);
   Keyboard.print("teste 1234...");
   Keyboard.releaseAll();
   delay(1500);

   Keyboard.write(KEY_RETURN);
   delay(1500);
}

void mousemover()
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
   // perform mouse left click
   Mouse.click(MOUSE_LEFT);
   delay(1500);
   // perform mouse right click
   Mouse.click(MOUSE_RIGHT);
   delay(1500);
}
