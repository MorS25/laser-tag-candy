// This #include statement was automatically added by the Particle IDE.
#include "neopixel/neopixel.h"

#define INPUT_PIN D0

#define PIXEL_PIN D2
#define STRIP_LENGTH 12

#define PEAK_VALUE 60
#define LOW_VALUE 0
#define INCREMENT_VALUE 5

#define PIXEL_TYPE WS2812B

#define WITCHPIN D4

Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_LENGTH, PIXEL_PIN, PIXEL_TYPE);

uint8_t values[] = { 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55 };
bool trends[] = { true, true, true, true, true, true, true, true, true, true, true, true };


void setup() {
    pinMode(INPUT_PIN, INPUT);
    pinMode(WITCHPIN, OUTPUT);
    
    strip.begin();
    for (int i = 0; i < STRIP_LENGTH; i++) {
        strip.setPixelColor(i, 0, 0, values[i]);
    }
    strip.show();
}

void loop() {
    if (digitalRead(INPUT_PIN) == LOW) {
        int i = 0;
        for (; i < 15; i++) {
            if (digitalRead(INPUT_PIN) == HIGH) {
                break;
            }
            delay(1);
        }
        if (i > 5) {
            Particle.publish("Give_Candy", "Give_Candy");
            #ifdef WITCH
            analogWrite(WITCHPIN, 128);
            #endif
            
            bool witchTrend = false;
            int witchVal = 256;
            digitalWrite(WITCHPIN, HIGH);
            for (int i = 125; i >= 0; i-=1) {
                for (int j = 0; j < STRIP_LENGTH; j++) {
                    strip.setPixelColor(j, i, 0, 0);
                }
                strip.show();
                // analogWrite(WITCHPIN, witchVal);
                // if (witchVal == 128) {
                //     witchTrend = true;
                // } else if (witchVal >= 256) {
                //     witchTrend = false;
                // }
                // if (witchTrend) {
                //     witchVal += 16;
                // } else {
                //     witchVal -= 16;
                // }
                delay(25);
            }
            digitalWrite(WITCHPIN, LOW);
        }
    }
    delay(40);
    nextValues();
    for (int i = 0; i < STRIP_LENGTH; i++) {
        strip.setPixelColor(i, values[i], 0, values[i]);
    }
    strip.show();
}

void nextValues() {
  for (int i = 0; i < STRIP_LENGTH; i++) {
    if (values[i] == PEAK_VALUE) {
      trends[i] = false;
      values[i]-=INCREMENT_VALUE;
    } else if (values[i] == LOW_VALUE) {
      trends[i] = true;
      values[i]+=INCREMENT_VALUE;
    } else {
      if (trends[i]) {
        values[i]+=INCREMENT_VALUE;
      } else {
        values[i]-=INCREMENT_VALUE;
      }
    }
  }
}

