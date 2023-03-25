

#include <avr/io.h>
 
void  Encoder_san();
// Definicao dos Pinos
const int Encoder_A =  3;            // Incremental Encoder singal A is PD3 
const int Encoder_B =  2;            // Incremental Encoder singal B is PD2 
const int ledPin    =  13; 
int Encoder_number=0;
int state=0;
 
void setup(){
  PORTD |=((1<<Encoder_A)|(1<<Encoder_B));          //Pull up Encoder singal A and Bsignals
  attachInterrupt(1, Encoder_san, FALLING);        //interrupts: numbers 0 (on digital pin 2) and 1 (on digital pin 3).
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(Encoder_A, INPUT); 
  pinMode(Encoder_B, INPUT); 
}
 
void loop(){
  if(state==1){  
    for(int i=0;i<Encoder_number;i++){
      digitalWrite(ledPin,HIGH);
      delay(500);
      digitalWrite(ledPin,LOW);
      delay(500);
    }
    state=0;
  }
}
void Encoder_san()
{  
 
        if(digitalRead(Encoder_B))
          {
             Encoder_number++;
          }
        else
          {  
            Encoder_number--;
          }     
          state=1;
}


