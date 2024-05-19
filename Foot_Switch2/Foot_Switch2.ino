//IN
int switchIn = 2;

//OUT
int startPin = 12;
int stopPin = 15;

//VARIABLES
boolean started;
boolean switched;
boolean button;
boolean single_clicked;
boolean double_clicked;
boolean long_clicked;
int pressed_time;
int released_time;
int longtime = 1500000;
int doubletime = 200000;
int debounce = 100;

void setup() {

    pinMode(switchIn,INPUT);
    pinMode (startPin, OUTPUT);
    pinMode(stopPin, OUTPUT);

Serial.begin(115200);
}

void loop() {

  button = digitalRead(switchIn);

  if (not(button)) {
        if (released_time < 10000000) {
              released_time = released_time + 1;
        }
        //wait for debounce time
        if (released_time > debounce) {
              if (released_time == debounce + 1) {
                  Serial.println("Pressed Time: " + String(pressed_time));
              }
              if ((released_time == doubletime + 1) and (not(long_clicked)) and (not(double_clicked)) and (not(switched))) {
                  single_clicked = true;
              }
              
              pressed_time = 0;
                  
              if (double_clicked) {
                  //maybe double clicked
                  //if () {
                  //    double_clicked = false;
                  //}
                  Serial.println("on release - double clicked!");
                  digitalWrite(startPin, HIGH);
                  digitalWrite(stopPin, HIGH);
                  delay(500);
                  digitalWrite(startPin, LOW);
                  digitalWrite(stopPin, LOW);
                  delay(500);
                  digitalWrite(startPin, HIGH);
                  digitalWrite(stopPin, HIGH);
                  delay(500);
                  digitalWrite(startPin, LOW);
                  digitalWrite(stopPin, LOW);
                  double_clicked = false;
                  switched = true;
              } else if (long_clicked) {
                  //long clicked
                  Serial.println("on release - long clicked!");
                  digitalWrite(startPin, HIGH);
                  digitalWrite(stopPin, HIGH);
                  delay(2000);
                  digitalWrite(startPin, LOW);
                  digitalWrite(stopPin, LOW);
                  delay(2000);
                  digitalWrite(startPin, HIGH);
                  digitalWrite(stopPin, HIGH);
                  delay(2000);
                  digitalWrite(startPin, LOW);
                  digitalWrite(stopPin, LOW);
                  long_clicked = false;
                  switched = true;
              } else if (single_clicked) {
                  Serial.println("on release - single clicked!");
                  single_clicked = false;
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
                        delay(1000);
                  }
              }
        }
        digitalWrite(startPin, LOW);
        digitalWrite(stopPin, LOW);
        
  } else {
        //button pressed
        if (pressed_time < 10000000) {
              pressed_time = pressed_time + 1;
        }
        //wait for debounce time
        if (pressed_time > debounce ) {
              if (pressed_time == debounce + 1) {
                  Serial.println("Released Time: " + String(released_time));
                  single_clicked = false;     
                  if ((released_time < doubletime) and (not(double_clicked))) {
                        double_clicked = true;
                        Serial.println("maybe double clicked! - released time: " + String(released_time));
                  }
              }
              switched = false;
              released_time = 0;
              
              if ((pressed_time > longtime) and (not(long_clicked))) {
                  long_clicked = true;
                  Serial.println("long clicked! - pressed time: " + String(pressed_time));
              }
        }
  } 
  
}
