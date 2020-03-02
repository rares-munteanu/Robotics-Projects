const int soundPin = A0;
const int ledPin = 8;
const int barrier = 1000;
int soundValue;
int numberOfClaps;
bool ledOn = false;

int clapTime = 500;
unsigned long long lastClapTime = 0;

int delayTime = 80;
unsigned long long lastDelayTime = 0;
bool clapped = false;

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
  if (soundValue > barrier) {
    lastDelayTime = millis();
    return true;
  }
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
  clapped = false;
}


void setup() {

  Serial.begin(9600);
  pinMode(soundPin, INPUT);
  pinMode(ledPin, OUTPUT);

}

void loop() {

  readSound();
  debug();
  if (bigSound() or clapped) {
    if (millis() - lastDelayTime > delayTime)
      manageLed();
  }
}
