#include <FastLED.h>

#define NUM_LEDS 50
#define DATA_PIN 3

CRGB leds[NUM_LEDS];

// Define a struct to hold color and time range
struct LEDState {
  CRGB color;
  int minTime;
  int maxTime;
};

// Create an array of LEDState objects
LEDState states[] = {
  {CRGB(240, 255, 0), 1000, 4000}, // Bright orange
  {CRGB(30, 50, 0), 600, 800},  // Mid brightness orange
//  {CRGB(10, 20, 0), 600, 1000},  // Low brightness orange
  {CRGB::Black, 50, 100}        // Off
};

// Define weights for each state
int weights[] = {40, 30, 20}; 

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {

  int number_of_yellow_on_off_changes_before_heartbeat = 20;
  int number_of_heartbeats = 15;

  for (int k = 0; k < number_of_yellow_on_off_changes_before_heartbeat; k++) {
    int totalWeight = 0;
    for (int i = 0; i < 3; i++) {
      totalWeight += weights[i];
    }
    int randomWeight = random(0, totalWeight);
    int stateIndex = 0;
    int cumulativeWeight = weights[0];
    while (randomWeight >= cumulativeWeight) {
      stateIndex++;
      cumulativeWeight += weights[stateIndex];
    }
    LEDState currentState = states[stateIndex];
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = currentState.color;
    }
    FastLED.show();
    delay(random(currentState.minTime, currentState.maxTime));
  }

  // Heartbeat
  CRGB lightRed = CRGB(0, 255, 0);
  CRGB midRed = CRGB(0, 110, 0);
  CRGB deepRed = CRGB(0, 40, 0);

  for (int k = 0; k < number_of_heartbeats; k++) {

    for (int j = 16; j >= 0; j--) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = blend(midRed, deepRed, j * 16);
      }
      FastLED.show();
      delay(0);
    }
    for (int j = 0; j < 128; j++) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = blend(midRed, deepRed, j * 2);
      }
      FastLED.show();
      delay(1.8);
    }
    for (int j = 16; j >= 0; j--) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = blend(lightRed, deepRed, j * 16);
      }
      FastLED.show();
      delay(0.00); 
    }
    for (int j = 0; j < 128; j++) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = blend(lightRed, deepRed, j * 2);
      }
      FastLED.show();
      delay(4); 
    }
    
  } 
}