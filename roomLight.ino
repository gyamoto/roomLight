#include "types.h"

//========================================================
// Config
//========================================================
#define IR_OUT                (13)
#define LED_OUT               (12)
#define SW_ON                 (3)
#define SW_OFF                (2)

#define DATA_SIZE             (67)

//========================================================
// Program
//========================================================
u2 PATTERN_ON[67] = { 8155, 4619, 516, 1729, 517, 653, 485, 632, 504, 661, 473, 655, 483, 621, 515, 653, 483, 648, 495, 651, 485, 651, 488, 648, 487, 660, 473, 1733, 517, 656, 483, 1728, 517, 1728, 523, 1719, 527, 661, 476, 653, 485, 660, 476, 660, 475, 1729, 519, 655, 484, 655, 487, 661, 476, 1731, 520, 1728, 520, 1731, 517, 1728, 519, 664, 473, 1727, 521, 1713, 527 };
u2 PATTERN_OFF[67] = { 8123, 4591, 548, 1719, 517, 669, 471, 668, 465, 652, 487, 668, 468, 667, 468, 671, 468, 669, 471, 668, 471, 667, 467, 669, 468, 668, 471, 1745, 503, 676, 460, 1741, 507, 1749, 504, 1737, 511, 1747, 501, 669, 471, 675, 461, 668, 468, 1744, 504, 667, 471, 681, 460, 665, 469, 665, 468, 1747, 501, 1748, 501, 1745, 504, 668, 465, 1745, 508, 1745, 503 };

void sendSignal(u2 data[]) {
  u2 time = 0;
  u4 index = DATA_SIZE;
  u4 count = 0;
  u4 us = micros();

  for (count = 0; count < index; count++) {
    time = data[count];
    us = micros();
    do {
      digitalWrite(IR_OUT, !(count & 1));
      delayMicroseconds(8);
      digitalWrite(IR_OUT, 0);
      delayMicroseconds(7);
    } while (s4(us + time - micros()) > 0);
  }

  digitalWrite(LED_OUT, HIGH);
  delay(300);
  digitalWrite(LED_OUT, LOW);
  delay(700);
}

void setup() {
  pinMode(IR_OUT, OUTPUT);
  pinMode(SW_ON, INPUT_PULLUP);
  pinMode(SW_OFF, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(SW_ON) == LOW) {
      sendSignal(PATTERN_ON);
    } else if (digitalRead(SW_OFF) == LOW) {
      sendSignal(PATTERN_OFF);
    }
}

