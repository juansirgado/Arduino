// -----------------------------------------------------------------------------
// constants

const int                                 PinCLK   = 7;     // Used for generating interrupts using CLK signal
const int                                 PinDT    = 8;     // Used for reading DT signal
const int                                 PinSW    = 9;     // Used for the push button switch

// -----------------------------------------------------------------------------
// global vars

volatile int                             virtualPosition    = 0;

// -----------------------------------------------------------------------------
// forward decls

// -----------------------------------------------------------------------------

void setup() {
    Serial.begin(9600);

    pinMode(PinCLK,INPUT);
    pinMode(PinDT, INPUT);
    pinMode(PinSW, INPUT);

    attachInterrupt(0, isr, FALLING);   // interrupt 0 is always connected to pin 2 on Arduino UNO

    Serial.println("Start");

    } // setup

// -----------------------------------------------------------------------------

void loop() {

    int                                    lastCount = 0;

    while (true) {
        if (!(digitalRead(PinSW))) {        // check if pushbutton is pressed
            virtualPosition = 0;            // if YES, then reset counter to ZERO
            while (!digitalRead(PinSW)) {}  // wait til switch is released
            delay(10);                      // debounce
            Serial.println("Reset");        // Using the word RESET instead of COUNT here to find out a buggy encoder
            }
        if (virtualPosition != lastCount) {
            lastCount = virtualPosition;
            Serial.print("Count;
            Serial.println(virtualPosition);
            }
        } // while
    } //loop
    
// -----------------------------------------------------------------------------
// Interrupt service routine is executed when a HIGH to LOW transition is detected on CLK

void isr ()  {

    static unsigned long                lastInterruptTime = 0;
    unsigned long                       interruptTime = millis();

    // If interrupts come faster than 5ms, assume it's a bounce and ignore
    if (interruptTime - lastInterruptTime > 5) {
        if (!digitalRead(PinDT))
            virtualPosition = (virtualPosition + 1);
        else
            virtualPosition = virtualPosition - 1;
        }
    lastInterruptTime = interruptTime;
    } // ISR

// -----------------------------------------------------------------------------

