# Environment Sensor
Code for a local environment sensor based on the ESP8266 NodeMCU and DHT11 (at the moment) sensor.

At the moment, this uses:
* ESP8266 NodeMCU microcontroller
* DHT11 Temp and Humidity sensor
* ThingSpeak.com for logging

Dependencies:
* DHT sensor library: https://github.com/adafruit/DHT-sensor-library
* ThingSpeak library (install through the Arduino IDE)
* ESP8266 WiFi library (installed through the Arduino IDE)

The code updates ThingSpeak every 60 seconds, alternating between the two variables (so temp and humidity are each updated every 2 minutes). This is fine for my purposes, but it should be possible to code for both to be updated at the same time by creating a string. I will probably do this if/when I add more sensors to the platform (e.g. for air quality). 

I have not included much if any error handling. This is not production quality code.
