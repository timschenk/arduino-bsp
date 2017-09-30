/**
* a simple breakout box for Arturia Beatstep Pro
*
* it uses
*
* https://github.com/wizard97/ArduinoRingBuffer
*
* @author tim schenk http://www.tim-schenk.de/
*/

#include <MIDI.h>
#include <RingBufCPP.h>

MIDI_CREATE_DEFAULT_INSTANCE();



// define midi channels
#define SEQ1 3                   // Midi Channel Sequencer 1
#define SEQ2 5                   // Midi Channe Sequencer 2
#define DRUM 10                  // Midi Cannel Drum Sequencer

#define isActiveChannel(channel) (channel==SEQ1 || channel==SEQ2 || channel==DRUM)

// define outputs
#define LED 10                   // LED pin on Arduino Uno

#define CLOCK 10                 // Clock out
// SEQ1
#define SEQ1_VEL A0               // Velocity
#define SEQ1_PITCH A1             // Pitch
#define SEQ1_GATE A2              // Gate / Trigger
// SEQ2
#define SEQ2_VEL A3               // Velocity
#define SEQ2_PITCH A4             // Pitch
#define SEQ2_GATE A5              // Gate / Trigger
// DRUM
#define DRUM_1 2                 // Gate / Trigger
#define DRUM_2 3                 // Gate / Trigger
#define DRUM_3 4                 // Gate / Trigger
#define DRUM_4 5                 // Gate / Trigger
#define DRUM_5 6                // Gate / Trigger
#define DRUM_6 7                // Gate / Trigger
#define DRUM_7 8                // Gate / Trigger
#define DRUM_8 9                // Gate / Trigger
// Drum Notes
#define DRUMNOTE_1 35                // Gate / Trigger
#define DRUMNOTE_2 36                // Gate / Trigger
#define DRUMNOTE_3 37                // Gate / Trigger
#define DRUMNOTE_4 41                // Gate / Trigger
#define DRUMNOTE_5 39                // Gate / Trigger
#define DRUMNOTE_6 40                // Gate / Trigger
#define DRUMNOTE_7 43                // Gate / Trigger
#define DRUMNOTE_8 42                // Gate / Trigger



/**
* a midi event for fast storage in ringbuffer
*/
struct Event{
  //int index = 0;
  byte channel = 0;
  byte pitch = 0;
  byte velocity = 0;  
};

/*
* Maximum events in ringbuffer
*/
#define MAX_NUM_ELEMENTS 20

// Stack allocate the buffer to hold event structs
RingBufCPP<struct Event, MAX_NUM_ELEMENTS> buf;

/**
* count loops for blinking led instead of delay() function
*/
int ledCounter = 0;
byte ledOn = LOW;

/**
* blink led without calling delay
*/
void BlinkLed()         // Basic blink function
{
    if(ledOn && --ledCounter <= 0){
          ledOn = LOW;
          ledCounter = 10;
    }

    digitalWrite(LED, ledOn);
}

/**
* midi callback for noteOn events
*/
void handleNoteOn(byte inChannel, byte inNote, byte inVelocity)
{
    switch(inChannel){
      case SEQ1:  /* FALLTHROUGH */
      case SEQ2:  /* FALLTHROUGH */
      case DRUM:  /* FALLTHROUGH */
            {
                struct Event e;
                //e.index = index++;
                e.channel = inChannel;
                e.pitch = inNote;
                e.velocity = inVelocity;
                // Add it to the buffer
                buf.add(e);
                return;
                break;
            }
      default:/* FALLTHROUGH */
            return;
            break;
    }

    //BlinkLed();
    
}

/**
* midi callback for noteOff events
*/
void handleNoteOff(byte inChannel, byte inNote, byte inVelocity)
{
    switch(inChannel){
         case SEQ1:  /* FALLTHROUGH */
         case SEQ2:  /* FALLTHROUGH */
         case DRUM:  /* FALLTHROUGH */
               {
                   struct Event e;
                   //e.index = index++;
                   e.channel = inChannel;
                   e.pitch = inNote;
                   e.velocity = 0;
                   // Add it to the buffer
                   buf.add(e);
                   return;
                   break;
               }
         default:
               return;
               break;
       }
}

// -----------------------------------------------------------------------------

void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(SEQ1_GATE, OUTPUT);
    pinMode(SEQ1_VEL, OUTPUT);
    pinMode(SEQ1_PITCH, OUTPUT);
    pinMode(SEQ2_GATE, OUTPUT);
    pinMode(SEQ2_VEL, OUTPUT);
    pinMode(SEQ2_PITCH, OUTPUT);
    pinMode(DRUM_1, OUTPUT);
    pinMode(DRUM_2, OUTPUT);
    pinMode(DRUM_3, OUTPUT);
    pinMode(DRUM_4, OUTPUT);
    pinMode(DRUM_5, OUTPUT);
    pinMode(DRUM_6, OUTPUT);
    pinMode(DRUM_7, OUTPUT);
    pinMode(DRUM_8, OUTPUT);

    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    
    MIDI.begin(MIDI_CHANNEL_OMNI);           // Launch MIDI, by default listening to channel 1.
//    BlinkLed();
}



//int noteCount = 0;

void loop()
{

    MIDI.read();
      //noteCount = 2;
    struct Event event;
      // Keep looping until pull() returns NULL
    while (buf.pull(&event))// && --noteCount)
    {
    //play a note
    switch(event.channel){
          case SEQ1:
          {
            analogWrite(SEQ1_VEL,  event.velocity * 2 );
            if(event.velocity > 0){
              analogWrite(SEQ1_PITCH,  event.pitch * 2 );
            }else{
              analogWrite(SEQ1_PITCH,  0 );
            }
            digitalWrite(SEQ1_GATE, ( event.velocity > 0) );
            ledOn = HIGH;
            break;
          }
          case SEQ2:
          {
            analogWrite(SEQ2_VEL,  event.velocity * 2 );
            if(event.velocity > 0){
              analogWrite(SEQ2_PITCH,  event.pitch * 2 );
            }else{
              analogWrite(SEQ2_PITCH,  0 );
            }
            digitalWrite(SEQ2_GATE, ( event.velocity > 0) );
            ledOn = HIGH;
            break;
          }
          case DRUM:
          {
                switch( event.pitch){
                    case DRUMNOTE_1:
                        digitalWrite(DRUM_1, ( event.velocity > 0) );
                        break;
                    case DRUMNOTE_2:
                        digitalWrite(DRUM_2, ( event.velocity > 0) );
                        break;
                    case DRUMNOTE_3:
                        digitalWrite(DRUM_3, ( event.velocity > 0) );
                        break;
                    case DRUMNOTE_4:
                        digitalWrite(DRUM_4, ( event.velocity > 0) );
                        break;
                    case DRUMNOTE_5:
                        digitalWrite(DRUM_5, ( event.velocity > 0) );
                        break;
                    case DRUMNOTE_6:
                        digitalWrite(DRUM_6, ( event.velocity > 0) );
                        break;
                    case DRUMNOTE_7:
                        digitalWrite(DRUM_7, ( event.velocity > 0) );
                        break;
                    case DRUMNOTE_8:
                        digitalWrite(DRUM_8, ( event.velocity > 0) );
                        break;
                    default:
                    break;
                }
                ledOn = HIGH;
            }
            break;
            default:
                break;
        }
    }

    BlinkLed();

}

/* function for using shift registers, not used at the moment */
// the heart of the program
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first,
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights.
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}
