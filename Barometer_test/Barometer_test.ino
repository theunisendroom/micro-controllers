#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

float temperature, humidity, pressure, altitude;


ESP8266WebServer server(80);              
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  bme.begin(0x76);   

}
void loop() {
  handle_OnConnect();
  delay(2000);
}

void handle_OnConnect() {
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);

  Serial.print("Temp: ");
  Serial.println(temperature);

  Serial.print("humidity: ");
  Serial.println(humidity);

  Serial.print("pressure: ");
  Serial.println(pressure);

  Serial.print("altitude: ");
  Serial.println(altitude);
  
}
