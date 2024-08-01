#include <dht11.h>

#include <LiquidCrystal.h>

#define DHT11_PIN 8
#define RED_LED_PIN 9
#define YELLOW_LED_PIN 10
#define GREEN_LED_PIN 11

dht11 DHT11;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  // put your setup code here, to run once:
  // Serial.begin(1200);

  lcd.begin(16, 2);
  analogWrite(6, 75);
  lcd.clear();

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  int chk = DHT11.read(DHT11_PIN);
  // Serial.println((float) DHT11.temperature);
  // Serial.println((float) DHT11.humidity);

  float temp = (float)DHT11.temperature;
  float humid = (float)DHT11.humidity;

  float tempThreshold = 31.0;
  float humidThreshold = 57.0;

  if (temp >= tempThreshold && humid >= humidThreshold)
  {
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
  }
  else if (temp >= tempThreshold || humid >= humidThreshold)
  {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
  }
  else
  {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
  }

  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
