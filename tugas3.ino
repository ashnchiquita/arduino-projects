#define TILTPIN 7
#define VIBPIN 8
#define FLAMEPIN A0
#define SMOKEPIN A1
#define BUZZER 10
#define BUTTON 6

const int flameMin = 0;
const int flameMax = 1024;
int smokeReading = 0;
int flameReading = 0;
bool isSerem = false;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(1200);
  pinMode(TILTPIN, INPUT);
  pinMode(VIBPIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
}

int currentState = LOW;

void loop()
{
  // put your main code here, to run repeatedly:
  currentState = digitalRead(BUTTON);

  // Flame
  flameReading = analogRead(FLAMEPIN);
  // int range = map(flameReading, flameMin, flameMax, 0, 3);
  // Serial.println("Flame: ");
  // Serial.println(flameReading);

  // range value:
  // switch (range) {
  // case 0:    //No fire detected
  //   Serial.println("** Νο Fire **");
  //   break;
  // case 1:    // A fire between 1-3 feet away.
  //   Serial.println("** Fire **");

  // }

  // Tilt
  int tiltReading = digitalRead(TILTPIN);
  // Serial.println(tiltReading);
  // if (tiltReading == HIGH){
  //   Serial.println("Tilted");
  // } else {
  //   Serial.println("Not tilted");
  // }

  // Vibration
  int vibReading = digitalRead(VIBPIN);
  // if (vibReading == HIGH) {
  //   Serial.println("Vibrated");
  // } else {
  //   Serial.println("Not vibrated");
  // }

  // Smoke
  smokeReading = analogRead(SMOKEPIN);
  // Serial.println("Smoke: ");
  // Serial.println(smokeReading);

  if (isSerem)
  {
    tone(BUZZER, 1000);
    delay(500);
    noTone(BUZZER);
    tone(BUZZER, 3000);
    delay(500);
    noTone(BUZZER);
    Serial.println("sinji");
  }

  if (currentState == HIGH)
  {
    if (isEarthquake(tiltReading, vibReading) && isFire(smokeReading, flameReading))
    {
      Serial.println("Earthquake and Fire!!");
      isSerem = true;
    }

    // Fire
    else if (isFire(smokeReading, flameReading))
    {
      Serial.println("Fire Detected!");
      tone(BUZZER, 1000);
      delay(500);
    }

    // Earthquake
    else if (isEarthquake(tiltReading, vibReading))
    {
      Serial.println("Earthquake Detected!");
      tone(BUZZER, 2000);
      delay(500);
    }
  }

  if (currentState != HIGH)
  {
    isSerem = false;
    noTone(BUZZER);
  }
}

bool isEarthquake(int tiltReading, int vibReading)
{
  return (tiltReading == HIGH) && (vibReading == HIGH);
}

bool isFire(int smokeReading, int flameReading)
{
  Serial.print("flame: ");
  Serial.println(flameReading);
  Serial.print("Gas: ");
  Serial.println(smokeReading);
  return (flameReading >= 191) && (smokeReading >= 55);
}
