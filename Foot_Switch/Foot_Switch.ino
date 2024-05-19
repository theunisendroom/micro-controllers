//IN
// D2 = GPIO4
//const int switchIn = 4;
const int switchIn = 27;

//OUT
//digital pin GPIO5 = D1
//int startPin = 5;
int startPin = 12;

//digital pin GPIO0 = D3
//int stopPin = 0;
int stopPin = 15;

boolean isOn = false;

void setup() {

    pinMode(switchIn,INPUT);
    pinMode (startPin, OUTPUT);
    pinMode(stopPin, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

}

void loop() {

  if (isOn) {
        digitalWrite(startPin, LOW);
        digitalWrite(stopPin, HIGH);
    isOn = false;
  } else {
        digitalWrite(startPin, HIGH);
        digitalWrite(stopPin, LOW);
    isOn = true;
  }

  if (isOn) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  delay(2000);

}
