#include <OneWire.h>    // Библиотека для работы с DS18B20
#include <DallasTemperature.h> // Библиотека для работы с DS18B20

// Пины подключения
const int relayPin = 2;           // Пин для управления реле
const int tempPin = A0;           // Пин для подключения температурного датчика

// Настройки
const float maxTemperature = 50.0; // Максимальная температура вентилятора, при которой он будет выключен
const unsigned long relayOffTime = 60000; // Время выключения реле при превышении температуры в миллисекундах

// Переменные
unsigned long previousMillis = 0; // Последнее время переключения реле
bool relayState = HIGH;           // Состояние реле (включен/выключен)
bool cooldownMode = false;        // Режим ожидания

OneWire oneWire(tempPin);
DallasTemperature sensors(&oneWire);

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Начально реле включено
  
  sensors.begin();
  Serial.begin(9600);
}

void loop() {
  // Считываем температуру
  sensors.requestTemperatures();
  float currentTemperature = sensors.getTempCByIndex(0);

  // Получаем текущее время
  unsigned long currentMillis = millis();

  // Проверка на режим ожидания
  if (cooldownMode) {
    if (currentMillis - previousMillis >= relayOffTime) {
      cooldownMode = false;
      relayState = HIGH; // Включаем реле
      digitalWrite(relayPin, relayState);
      previousMillis = currentMillis; // Обновляем время переключения
    }
  } else {
    if (currentTemperature >= maxTemperature) {
      // Если температура превышает максимальное значение, выключаем реле
      cooldownMode = true;
      relayState = LOW; // Выключаем реле
      digitalWrite(relayPin, relayState);
      previousMillis = currentMillis; // Обновляем время переключения
    }
  }

  // Отображаем температуру в Serial Monitor
  Serial.print("Current Temperature: ");
  Serial.print(currentTemperature);
  Serial.println(" C");
}