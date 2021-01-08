#include <ESP8266WiFi.h>
#include "DHT.h"
#include "ThingSpeak.h"

// Set sensor (DHT) type
#define DHTTYPE DHT11   // DHT 11

/*Put your SSID & Password*/
const char* ssid = "ssid";  // Enter SSID here
const char* password = "password";  //Enter Password here
WiFiClient  client;

/* ThingSpeak creds */
unsigned long channelNumber = channelNo;
const char * writeAPIid = "writeAPIid";

// DHT Sensor
uint8_t DHTPin = D1; 
               
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity;

// Interval between updates (alternate temp & hum)
int interval = 60000; // 60 seconds
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(DHTPin, INPUT);

  dht.begin();              

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);

}
void loop() {


  // Get temp and write to channel
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Serial.println(Temperature);

  // Write value to Field 1 of a ThingSpeak Channel
  int httpCodeTemp = ThingSpeak.writeField(channelNumber, 1, Temperature, writeAPIid);

  if (httpCodeTemp == 200) {
    Serial.println("Temp write successful.");
  }
  else {
    Serial.println("Problem writing Temp to channel. HTTP error code " + String(httpCodeTemp));
  }

  // Wait 30 seconds to update the channel again
  delay(interval);

  // Get hum and write to channel
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  Serial.println(Humidity);

  // Write to field 2
  int httpCodeHum = ThingSpeak.writeField(channelNumber, 2, Humidity, writeAPIid);

  if (httpCodeHum == 200) {
    Serial.println("Hum write successful.");
  }
  else {
    Serial.println("Problem writing Hum to channel. HTTP error code " + String(httpCodeHum));
  }

  // Wait 30 seconds to go around again
  delay(interval);
}
