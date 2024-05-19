//IN
int switchIn = 2;

//OUT
int startPin = 12;
int stopPin = 15;

//VARIABLES
boolean started;
boolean switched;
boolean button;

void setup() {

    pinMode(switchIn,INPUT);
    pinMode (startPin, OUTPUT);
    pinMode(stopPin, OUTPUT);

Serial.begin(115200);

}

void loop() {

  button = digitalRead(switchIn);
  if (not(button)) {
        digitalWrite(startPin, LOW);
        digitalWrite(stopPin, LOW);
        switched = false;
        delay(50);
  } else {
        if (not(switched)) {
              if (started) {
                  digitalWrite(startPin, LOW);
                  digitalWrite(stopPin, HIGH);
                  started = false;
              } else {
                  digitalWrite(startPin, HIGH);
                  digitalWrite(stopPin, LOW);
                  started = true;
              }
              switched = true;
              delay(50);
         }
  } 
  
}
