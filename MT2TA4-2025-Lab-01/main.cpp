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
        ledR = (((tracker + 1) % 2) == 1);
        ledG = (((tracker + 1) % 2) == 0);

        tracker = (tracker + 1) % 2; // cycle between two phases 
    } else { // state 2: Red on 1s, red off and wait 1s and repeat for green
        ledR = (((tracker + 1) % 4) == 1);
        ledG = (((tracker + 1) % 4) == 3);
       
        tracker = (tracker + 1) % 4; // cycle through 4 phases; 
    }
}

int main() {
  userButton.fall(&SetState);
  __enable_irq();
  tick1.attach(&stateToggle, 1s);  // run stateToggle function every 1s

  while (true) {}
}


