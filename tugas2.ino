#include <LiquidCrystal.h>
#include <dht11.h>

#define DHT11_PIN 8
#define BUTTON_PIN 7
#define PIR_PIN 6
#define YELLOW_LED_PIN 9
#define RED_LED_PIN 10

dht11 DHT11;
int count = 0;
bool is_on = false;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
String line1;
String line2;
bool is_Kipas;
bool is_Lampu;

void setup()
{
  Serial.begin(1200);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("ikan");

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void setLines(bool state, float temp, bool kipas, bool lampu)
{
  String stateStr;
  if (state == 1)
  {
    stateStr = "BERISI";
  }
  else
  {
    stateStr = "KOSONG";
  }

  String kipasStr = kipas ? "ON" : "OFF";
  String lampuStr = lampu ? "ON" : "OFF";

  line1 = "R:" + stateStr + " T:" + String(temp, 0) + "C";
  line2 = "KIP:" + kipasStr + " LAMP:" + lampuStr;
}

void loop()
{
  count += 1;
  if (!is_on)
  {
    scan(&is_on);
    count = 0;
  }

  if (!digitalRead(BUTTON_PIN))
  {
    scan(&is_on);
    count = 0;
  }

  delay(100);
  if (count == 100)
  {
    scan(&is_on);
    count = 0;
  }

  delay(700);

  // lcd.clear();
}

void scan(bool *is_on)
{
  lcd.clear();
  int pir = digitalRead(PIR_PIN);

  int chk = DHT11.read(DHT11_PIN);
  float temp = (float)DHT11.temperature;
  float tempThreshold = 30.0;

  Serial.print("Scanning PIR: ");
  Serial.println(pir);
  if (pir == HIGH)
  {
    digitalWrite(RED_LED_PIN, HIGH);
    is_Lampu = true;
    if (temp >= tempThreshold)
    {
      digitalWrite(YELLOW_LED_PIN, HIGH);
      is_Kipas = true;
    }
    *is_on = true;
  }
  else
  {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    is_Lampu = false;
    is_Kipas = false;
    *is_on = false;
  }

  setLines(pir, temp, is_Kipas, is_Lampu);

  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);

  Serial.print("TEMP: ");
  Serial.println(temp);
}
