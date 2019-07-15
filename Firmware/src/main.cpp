#include <Arduino.h>
#include <IRremote.h>

#define OKNYO_POWER     0x4B20D32C
#define ONKYO_VOLUP     0x4BC040BF
#define ONKYO_VOLDN     0x4BC0C03F
#define ONKYO_MUTE      0x4BC0A05F
#define ONKYO_INPUTNEXT 0x4B207887
#define ONKYO_INPUTPREV 0x4B20F807

#define BENQ_POWER      0xC40BF
#define BENQ_ECOBLANK   0xC0CF3

IRsend irsend;

void setup()
{

}

void loop() {
  irsend.sendNEC(ONKYO_VOLUP, 32);
	delay(200);
  irsend.sendNEC(ONKYO_VOLUP, 32);
	delay(200);
  irsend.sendNEC(ONKYO_VOLUP, 32);
	delay(200);
  irsend.sendNEC(ONKYO_VOLUP, 32);
	delay(200);
  irsend.sendNEC(ONKYO_VOLUP, 32);
	delay(1000);
  irsend.sendNEC(ONKYO_VOLDN, 32);
	delay(200);
  irsend.sendNEC(ONKYO_VOLDN, 32);
	delay(200);
  irsend.sendNEC(ONKYO_VOLDN, 32);
	delay(200);
  irsend.sendNEC(ONKYO_VOLDN, 32);
	delay(200);
  irsend.sendNEC(ONKYO_VOLDN, 32);
	delay(1000);
}
