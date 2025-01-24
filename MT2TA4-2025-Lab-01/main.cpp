#include "mbed.h"

Ticker tick1; 

InterruptIn userButton(BUTTON1);

DigitalOut ledG(PG_13);
DigitalOut ledR(PG_14);

int state = 0; // default state on startup
int tracker = 0; // used to cycle through phases

void SetState() {
  if (state != 1) {
    state = 1;
  } else {
    state = 2;
  }

  // resets tracker with every state switch
  tracker = 0; 
}

void stateToggle() {
    if(state == 0) { // Red Led blink on and off every 1s 
        ledR = !ledR; 
    } else if (state == 1) { // Red <-> Green every 1s
        if(tracker == 0) {
            ledR = 1; 
            ledG = 0; 
        } else if (tracker == 1) {
            ledR = 0; 
            ledG = 1; 
        }

        tracker = (tracker + 1) % 2; // cycle between two phases 
    } else { // state 2: Red on 1s, red off and wait 1s and repeat for green
        if (tracker == 0) {
            ledR = 1; 
            ledG = 0; 
        } else if (tracker == 1) {
            ledR = 0; 
            ledG = 0; 
        } else if (tracker == 2) {
            ledG = 1; 
            ledR = 0; 
        } else {
            ledR = 0; 
            ledG = 0; 
        }

        tracker = (tracker + 1) % 4; // cycle through 4 phases; 
    }
}

int main() {
  userButton.fall(&SetState);
  __enable_irq();
  tick1.attach(&stateToggle, 1s);  // run stateToggle function every 1s

  while (true) {}
}


