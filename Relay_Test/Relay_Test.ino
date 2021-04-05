#include <ESP8266WiFi.h>

char* ssid = "Thyme Events";
char* password =  "pierre@home";

WiFiServer server(80);

int relayPin = 5;

void setup() {
 
  Serial.begin(115200);

  connectToWifi();
 
  pinMode (relayPin, OUTPUT);

  digitalWrite (relayPin, LOW);
 
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    connectToWifi();
  }
  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("Request Received");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  hanldeRequest(request);
  
  client.stop();
}

void connectToWifi(){
  WiFi.begin(ssid, password);

  Serial.println("");
  Serial.print("Connecting to WiFi.");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected to the WiFi network");

  // Start the server
  server.begin();
  Serial.println("Server started");
  
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void hanldeRequest(String request){
  // Match the request
  int value = LOW;
  if (request.indexOf("/relay/on") != -1) {
    Serial.println("Switching ON relay!");
    digitalWrite(relayPin, HIGH);
    value = HIGH;
  } else if (request.indexOf("/relay/off") != -1){
    Serial.println("Switching OFF relay!");
    digitalWrite(relayPin, LOW);
    value = LOW;
  } else {
    Serial.println("Unknown request received: " + request);
  }
}
