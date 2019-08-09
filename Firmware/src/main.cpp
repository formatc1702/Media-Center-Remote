#include <Arduino.h>
#include <IRremote.h>
#include <avr/sleep.h>
#include <avr/power.h>

#define ONKYO_POWER     0x4B20D32C
#define ONKYO_VOLUP     0x4BC040BF
#define ONKYO_VOLDN     0x4BC0C03F
#define ONKYO_MUTE      0x4BC0A05F
#define ONKYO_INPUTNEXT 0x4B207887
#define ONKYO_INPUTPREV 0x4B20F807

#define BENQ_POWER      0xC40BF
#define BENQ_ECOBLANK   0xC0CF3

#define PIN_STATUS   13
#define PIN_INTERRUPT 2 // used by attachInterrupt(0,...)
#define PIN_BTN_VOLDN     5
#define PIN_BTN_VOLUP     6
#define PIN_BTN_PWR1      7
#define PIN_BTN_PWR2      8

IRsend irsend;

void wakeUp() {
}

void enterSleep() {
  // Serial.println("Good night!");
  digitalWrite(PIN_STATUS, LOW);

  delay(100);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(0, wakeUp, LOW);
  sleep_mode();
  // sleep happens here
  sleep_disable();
  detachInterrupt(0);
  // Serial.println("Good morning!");
}

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_STATUS, OUTPUT);
  pinMode(PIN_BTN_VOLUP, INPUT_PULLUP);
  pinMode(PIN_BTN_VOLDN, INPUT_PULLUP);
  pinMode(PIN_BTN_PWR1, INPUT_PULLUP);
  pinMode(PIN_BTN_PWR2, INPUT_PULLUP);
  digitalWrite(PIN_STATUS, LOW);
}

void loop() {
  enterSleep();
  digitalWrite(PIN_STATUS, HIGH);
  if        (digitalRead(PIN_BTN_VOLDN) == LOW) {
    Serial.println("Vol down");
    irsend.sendNEC(ONKYO_VOLDN, 32);
  } else if (digitalRead(PIN_BTN_VOLUP) == LOW) {
    Serial.println("Vol up");
    irsend.sendNEC(ONKYO_VOLUP, 32);
  } else if (digitalRead(PIN_BTN_PWR1) == LOW) {
    Serial.println("Onkyo on/off");
    irsend.sendNEC(ONKYO_POWER, 32);
  } else if (digitalRead(PIN_BTN_PWR2) == LOW) {
    Serial.println("BenQ on/off");
    irsend.sendNEC(BENQ_POWER, 32);
  }
  delay(100);
  digitalWrite(PIN_STATUS, LOW);
  // digitalWrite(PIN_STATUS, HIGH);
  // irsend.sendNEC(ONKYO_POWER, 32);
  // irsend.sendNEC(ONKYO_VOLUP, 32);
	// delay(200);
  // irsend.sendNEC(ONKYO_VOLUP, 32);
	// delay(200);
  // irsend.sendNEC(ONKYO_VOLUP, 32);
	// delay(200);
  // irsend.sendNEC(ONKYO_VOLUP, 32);
	// delay(1000);
  // irsend.sendNEC(ONKYO_VOLDN, 32);
	// delay(200);
  // irsend.sendNEC(ONKYO_VOLDN, 32);
	// delay(200);
  // irsend.sendNEC(ONKYO_VOLDN, 32);
	// delay(200);
  // irsend.sendNEC(ONKYO_VOLDN, 32);
	// delay(200);
  // irsend.sendNEC(ONKYO_VOLDN, 32);
	// delay(1000);
}
