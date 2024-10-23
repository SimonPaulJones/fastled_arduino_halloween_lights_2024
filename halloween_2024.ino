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
  {CRGB(128, 255, 0), 10, 6000}, // Bright orange
  {CRGB(25, 50, 0), 600, 1000},  // Mid brightness orange
  {CRGB(10, 20, 0), 600, 1000},  // Low brightness orange
  {CRGB(0, 255, 0), 5000, 5000},  // Red
  {CRGB::Black, 10, 2000}        // Off
};

// Define weights for each state
int weights[] = {40, 25, 24, 1, 10}; // Red has a very low weight

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  // Calculate the total weight
  int totalWeight = 0;
  for (int i = 0; i < 4; i++) {
    totalWeight += weights[i];
  }

  // Generate a random number within the total weight
  int randomWeight = random(0, totalWeight);

  // Select the state based on the random weight
  int stateIndex = 0;
  int cumulativeWeight = weights[0];
  while (randomWeight >= cumulativeWeight) {
    stateIndex++;
    cumulativeWeight += weights[stateIndex];
  }

  LEDState currentState = states[stateIndex];
  
  // Apply the selected state
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = currentState.color;
  }
  FastLED.show();
  
  // Wait for a random interval within the selected state's time range
  delay(random(currentState.minTime, currentState.maxTime));
}