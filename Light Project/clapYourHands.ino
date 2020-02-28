const int soundPin = A0;
const int ledPin = 8;
const int barrier = 1023;
int soundValue;
int numberOfClaps;
bool ledOn = false;

int clapTime = 500;
unsigned long long lastClapTime = 0;

int i = 0;

void readSound() {
  soundValue = analogRead(soundPin);
}

void debug() {
  if (soundValue > 100) {
    Serial.print(++i);
    Serial.print(": ");
    Serial.println(soundValue);
    Serial.println("");
  }
}

bool bigSound() {
  if (soundValue > 1000)
    return true;
  return false;
}

void manageLed() {
  numberOfClaps++;
  if (numberOfClaps == 1) {
    lastClapTime = millis();
  }
  else if (numberOfClaps == 2) {
    if (millis() - lastClapTime < clapTime) {
      ledOn = !ledOn;
      digitalWrite(ledPin, ledOn);
      numberOfClaps = 0;
    }
    else {
      lastClapTime = millis();
      numberOfClaps = 1;
    }
  }
}


void setup() {

  Serial.begin(9600);
  pinMode(soundPin, INPUT);
  pinMode(ledPin, OUTPUT);

}

void loop() {

  readSound();
  debug();
  if (bigSound()) {
    //    Serial.println("Am detectat sunet");
    //    Serial.println(ledOn);
    //    delay(500);
    //    ledOn = !ledOn;
    //    digitalWrite(ledPin, ledOn);
    delay(70);
    manageLed();
  }
}
