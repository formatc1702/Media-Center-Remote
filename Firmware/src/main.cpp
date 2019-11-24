#include <Arduino.h>
#include <IRremote.h>
#include "LowPower.h"

#define ONKYO_POWER     0x4B20D32C
#define ONKYO_VOLUP     0x4BC040BF
#define ONKYO_VOLDN     0x4BC0C03F
#define ONKYO_MUTE      0x4BC0A05F
#define ONKYO_INPUTNEXT 0x4B207887
#define ONKYO_INPUTPREV 0x4B20F807

#define BENQ_POWER      0xC40BF
#define BENQ_ECOBLANK   0xC0CF3

#define PIN_STATUS   10
#define PIN_INTERRUPT 2 // used by attachInterrupt(0,...)
#define PIN_BTN_VOLDN     8
#define PIN_BTN_VOLUP     7
#define PIN_BTN_PWR1      6
#define PIN_BTN_PWR2      5

/*
fuse settings:
avrdude -c arduino -p m328p -P /dev/tty.SLAB_USBtoUART -b 19200 -U lfuse:w:0xc2:m -U hfuse:w:0xda:m -U efuse:w:0xfe:m

bootloader (Arduino Pro Mini 8MHz):
avrdude -c arduino -p m328p -P /dev/tty.SLAB_USBtoUART -b 19200 -U flash:w:/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/bootloaders/atmega/ATmegaBOOT_168_atmega328_pro_8MHz.hex -v
*/

IRsend irsend;

void wakeUp() {}

void setup()
{
  for (size_t i = 0; i < 20; i++) {
    pinMode(i, INPUT); // set all pins to high-Z
  }
  pinMode(PIN_INTERRUPT, INPUT_PULLUP);
  pinMode(PIN_BTN_VOLUP, INPUT_PULLUP);
  pinMode(PIN_BTN_VOLDN, INPUT_PULLUP);
  pinMode(PIN_BTN_PWR1, INPUT_PULLUP);
  pinMode(PIN_BTN_PWR2, INPUT_PULLUP);
  pinMode(PIN_STATUS, OUTPUT);
  digitalWrite(PIN_STATUS, LOW);

  digitalWrite(PIN_STATUS, HIGH); delay(50);
  digitalWrite(PIN_STATUS, LOW);  delay(100);
  digitalWrite(PIN_STATUS, HIGH); delay(50);
  digitalWrite(PIN_STATUS, LOW);  delay(100);
}

void loop() {

  // sleep
  delay(50);
  attachInterrupt(0, wakeUp, LOW);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  detachInterrupt(0);

  // send remote code
  digitalWrite(PIN_STATUS, HIGH);
  delay(50);
  if        (digitalRead(PIN_BTN_VOLDN) == LOW) {
    Serial.println("Vol down");
    irsend.sendNEC(ONKYO_VOLDN, 32);
  } else if (digitalRead(PIN_BTN_VOLUP) == LOW) {
    Serial.println("Vol up");
    irsend.sendNEC(ONKYO_VOLUP, 32);
  } else if (digitalRead(PIN_BTN_PWR1)  == LOW) {
    Serial.println("Onkyo on/off");
    irsend.sendNEC(ONKYO_POWER, 32);
  } else if (digitalRead(PIN_BTN_PWR2)  == LOW) {
    Serial.println("BenQ on/off");
    irsend.sendNEC(BENQ_POWER, 32);
  }
  delay(50);
  digitalWrite(PIN_STATUS, LOW);
}
