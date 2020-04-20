/*
 * Encoding 32 bits samsug
*/
#define CODE_ON        0xE0E040BF 
#define CODE_COLORS    0xE0E0738C
#define CODE_123       0xE0E04BB4
#define CODE_MIDDLE    0xE0E016E9
#define CODE_LEFT      0xE0E0A659
#define CODE_RIGHT     0xE0E046B9
#define CODE_UP        0xE0E006F9
#define CODE_DOWN      0xE0E08679
#define CODE_BACK      0xE0E01AE5
#define CODE_HOME      0xE0E09E61
#define CODE_PAUSE     0xE0E09D62
#define CODE_VOL_UP   0xE0E0E01F
#define CODE_VOL_DOWN  0xE0E0D02F
#define CODE_CHAN_UP   0xE0E048B7
#define CODE_CHAN_DOWN 0xE0E008F7
#define CODE_MUDE      0xE0E0F00F
#define CODE_GUIDE     0xE0E0F20D
#define CODE_TV        0xE0E0D827
#define CODE_CHAN      0xE0E0D629


#include <IRremote.h>
#include <avr/sleep.h>
IRsend irsend;

const int buttonRed = 8;
const int buttonBlack = 9;
const int buttonGreen = 10;
const int buttonWhite = 11;
const int buttonBlue = 12;
const int buttonYellow = 13;
const int irLED = 3;

void setup() {
  pinMode(buttonRed, INPUT_PULLUP);
  pinMode(buttonBlack, INPUT_PULLUP);
  pinMode(buttonGreen, INPUT_PULLUP);
  pinMode(buttonWhite, INPUT_PULLUP);
  pinMode(buttonBlue, INPUT_PULLUP);
  pinMode(buttonYellow, INPUT_PULLUP);
  pinMode(irLED, OUTPUT);

  //Enable pin change interrupt on pins 8 thru 13
  PCMSK0 |= (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2) | (1 << PCINT3) | (1 << PCINT4) | (1 << PCINT5);

  // Enable pin change interrupt 0 using the Pin Change Interrrupt Control Register (PCICR)
  PCICR |= _BV(PCIE0);
}

ISR(PCINT0_vect) {
  //just wakes up the chip
}

void goSleep(void) {
  //goes to power down mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  cli();
  sleep_enable();
  sei();
  sleep_cpu();// MCU sleeps and wake ups here
  sleep_disable();
}

void loop() {
  goSleep(); // goes to sleep and only sends code bursts if woken up

  if (digitalRead(buttonRed) == LOW) {
    for (int i = 0; i < 1; i++) {
      irsend.sendSAMSUNG(CODE_ON, 32);
      delay(40);
    }
    delay(500);
  }
  if (digitalRead(buttonBlack) == LOW) {
    for (int i = 0; i < 1; i++) {
      irsend.sendSAMSUNG(CODE_CHAN, 32);
      delay(40);
    }
    delay(500);
  }
  if (digitalRead(buttonGreen) == LOW) {
    for (int i = 0; i < 1; i++) {
      irsend.sendSAMSUNG(CODE_VOL_UP, 32);
      delay(40);
    }
    delay(500);
  }
  if (digitalRead(buttonWhite) == LOW) {
    for (int i = 0; i < 1; i++) {
      irsend.sendSAMSUNG(CODE_CHAN_UP, 32);
      delay(40);
    }
    delay(500);
  }
  if (digitalRead(buttonBlue) == LOW) {
    for (int i = 0; i < 1; i++) {
      irsend.sendSAMSUNG(CODE_VOL_DOWN, 32);
      delay(40);
    }
    delay(500);
  }
  if (digitalRead(buttonYellow) == LOW) {
    for (int i = 0; i < 1; i++) {
      irsend.sendSAMSUNG(CODE_CHAN_DOWN, 32);
      delay(40);
    }
    delay(500);
  }

}
