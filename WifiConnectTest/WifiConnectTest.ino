#include <ESP8266WiFi.h>
#include <ESP8266TrueRandom.h>

const char* ssid="Beerkuil";
const char* password = "LetMeInPlease";

int ledPin = LED_BUILTIN;

int temperature = 19;

const char* host = "192.168.0.114";
const int hostPort = 3000;

WiFiClient client;

void setup() {
  // basic setup
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,HIGH);

  Serial.begin(115200);
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

  // connect to wifi
  WiFi.begin(ssid,password);

  Serial.println();
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");        
  }
  

  digitalWrite( ledPin , LOW);
  Serial.println();

  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );
}

void loop() {
  // put your main code here, to run repeatedly:
  
  generateAndSendNewNumber();
  
  delay(2000);

}

void generateAndSendNewNumber() {
  temperature = ESP8266TrueRandom.random(1,40);

  Serial.println("Temp = " + String(temperature));

  if(client.connect(host,hostPort)){

    client.println("POST / HTTP/1.1");
    client.println("Host: host");
    client.println("Connection: keep-alive");
    client.println("Cache-Control: no-cache");
    client.println("Content-Type: text/plain");
    client.print("Content-Length: ");
    client.println(String(temperature).length());
    client.println();
    client.println(String(temperature));
    
    delay(10);
    // Read all the lines of the response and print them to Serial
    Serial.println("Response: ");
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
}
