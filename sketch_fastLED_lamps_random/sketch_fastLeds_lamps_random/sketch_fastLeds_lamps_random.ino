/*
  суть программы - светодиоды загораются в рандомное время до 15 штук и у каждого светодиода своя яркость и длительность горения.
*/


#include <FastLED.h>

#define LED_PIN 2
#define NUM_LEDS 30

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  // выбираем случайное количество светодиодов для включения
  int num_leds = random(7, 20);
  
  // инициализируем переменные для каждого светодиода
  int led_indices[num_leds];
  int led_durations[num_leds];
  int led_brightnesses[num_leds];
  CRGB led_colors[num_leds];
  
  // случайным образом выбираем индекс, длительность, яркость и цвет для каждого светодиода
  for (int i = 0; i < num_leds; i++) {
    led_indices[i] = random(NUM_LEDS);
    led_durations[i] = random(120, 180);
    led_brightnesses[i] = random(10, 220);
    led_colors[i] = CHSV(random(256), 255, 255);
  }
  
  // зажигаем каждый светодиод на выбранную длительность и яркость с выбранным цветом
  unsigned long start_time = millis();
  while (millis() - start_time < led_durations[num_leds - 1]) {
    for (int i = 0; i < num_leds; i++) {
      int time_elapsed = millis() - start_time;
      if (time_elapsed < led_durations[i]) {
        leds[led_indices[i]] = led_colors[i];
        FastLED.setBrightness(led_brightnesses[i]);
      }
    }
    FastLED.show();
  }
  
  // выключаем все светодиоды
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}