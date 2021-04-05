int ldrPin = 27;
int val = 0;
void setup() {
  pinMode(ldrPin, INPUT);
  Serial.begin(9600);
}
 
void loop() {
  int val = digitalRead(ldrPin);
  Serial.println(val);

  delay(1000);
 
}
