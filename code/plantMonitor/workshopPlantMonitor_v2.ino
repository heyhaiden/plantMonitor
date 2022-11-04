/*  PLANT MONITOR 
    0014 CONNECTED ENVIRONMENTS
    HAIDEN MCGILL
    31 OCTOBER 2022

    BASED ON: 
*/

// External libraries
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ezTime.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE DHT22  // DHT 22  (AM2302), AM2321

// DHT22 and Moisture Sensor
uint8_t DHTPin = 12;  // on Pin 12 of the Huzzah
uint8_t soilPin = 0;  //one nail goes to +5V, the other nail goes to this analogue pin
float Temperature;
float Humidity;
int Moisture = 1;  //initial value in case web page loaded before readMoisture function called
int sensorVCC = 13;
DHT dht(DHTPin, DHTTYPE);  // Initialize DHT sensor.

//ADD DISTURB COUNTER CODE HERE
//boolean Disturb = false;

// Wifi and MQTT
#include "arduino_secrets.h"

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;

ESP8266WebServer server(80);
const char* mqtt_server = "mqtt.cetools.org";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

// Date and time
Timezone GB;

void setup() {

  // turn on onboard LED
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);

  // start Moisture sensor
  pinMode(sensorVCC, OUTPUT);
  digitalWrite(sensorVCC, LOW);
  pinMode(blueLED, OUTPUT);
  digitalWrite(blueLED, HIGH);

  Serial.begin(115200);  //open serial port
  delay(100);

  // start DHT sensor
  pinMode(DHTPin, INPUT);
  dht.begin();

  // run initialisation functions
  startWifi();
  startWebserver();
  syncDate();

  // start MQTT server
  client.setServer(mqtt_server, 1884);
  client.setCallback(callback);
}

void loop() {
  // handler for receiving requests to webserver
  server.handleClient();

  if (minuteChanged()) {
    readMoisture();
    sendMQTT();
    Serial.println(GB.dateTime("H:i:s"));  // UTC.dateTime("l, d-M-y H:i:s.v T")
  }

  client.loop();
}

void readMoisture() {

  // power the sensor
  digitalWrite(sensorVCC, HIGH);
  digitalWrite(blueLED, LOW);
  delay(100);
  // read the value from the sensor:
  Moisture = analogRead(soilPin);
  Serial.print("Wet pre mapping");
  Serial.println(Moisture);  // read the value from the nails
  Moisture = map(analogRead(soilPin), 0, 400, 0, 100);
  //stop power
  digitalWrite(sensorVCC, LOW);
  digitalWrite(blueLED, HIGH);
  delay(100);
  Serial.print("Wet ");
  Serial.println(Moisture);  // read the value from the nails
}


void startWifi() {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // check to see if connected and wait until you are
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void syncDate() {
  // get real date and time
  waitForSync();
  Serial.println("UTC: " + UTC.dateTime());
  GB.setLocation("Europe/London");
  Serial.println("London time: " + GB.dateTime());
}

void sendMQTT() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  Temperature = dht.readTemperature();  // Gets the values of the temperature
  snprintf(msg, 50, "%.1f", Temperature);
  Serial.print("Publish message for t: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnhmc/temperature", msg);

  Humidity = dht.readHumidity();  // Gets the values of the humidity
  snprintf(msg, 50, "%.0f", Humidity);
  Serial.print("Publish message for h: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnhmc/humidity", msg);

  //Moisture = analogRead(soilPin);   // moisture read by readMoisture function
  snprintf(msg, 50, "%.0i", Moisture);
  Serial.print("Publish message for m: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnhmc/moisture", msg);

  //Disturb mode
  //Disturb = dht.readDisturb();  // Checks if plant has been disturbed
  //snprintf(msg, 50, "%.0f", Disturb);
  //Serial.print("Publish message for d: ");
  //Serial.println(msg);
  //client.publish("student/CASA0014/plant/ucfnhmc/disturb", msg);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if a 1 was received as a first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);
  } else {
    digitalWrite(BUILTIN_LED, HIGH);
  }
}

void reconnect() {
    //Loop until we're reconnected
    while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
      // Create a random client ID
      String clientID = "ESP8266Client-";
      clientID += String(random(0xfff), HEX);

      // Attempt to connect
      if (client.connect(clientID.c_str(), mqttuser, mqttpass)) {
        Serial.println("connected");
        // ... and subscribe to messages on broker
        client.subscribe("student/CASA0014/plant/ucfnhmc/inTopic");
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");

        //Wait 5 seconds before retrying
        delay(5000);
      }
    }
}

void startWebserver() {

    // when connected and IP address obtained start HTTP server
    server.on("/", handle_OnConnect);
    server.onNotFound(handle_NotFound);
    server.begin();
    Serial.println("HTTP server started");
}


void handle_OnConnect() {
    Temperature = dht.readTemperature();  // Gets the values of the temperature
    Humidity = dht.readHumidity();        // Gets the values of the humidity
    server.send(200, "text/html", SendHTML(Temperature, Humidity, Moisture));
}

void handle_NotFound() {
    server.send(404, "text/plain", "Not found");
}

// Static webpage with live data feeds
String SendHTML(float Temperaturestat, float Humiditystat, int Moisturestat) {
    String ptr = "<!DOCTYPE html> <html>\n";
    ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    ptr += "<title>ESP8266 DHT22 Report</title>\n";
    ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
    ptr += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
    ptr += "</style>\n";
    ptr += "</head>\n";
    ptr += "<body>\n";
    ptr += "<div id=\"webpage\">\n";
    ptr += "<h1>ESP8266 Huzzah DHT22 Report</h1>\n";

    ptr += "<p>Temperature: ";
    ptr += (int)Temperaturestat;
    ptr += " C</p>";
    ptr += "<p>Humidity: ";
    ptr += (int)Humiditystat;
    ptr += "%</p>";
    ptr += "<p>Moisture: ";
    ptr += Moisturestat;
    ptr += "</p>";
    ptr += "<p>Sampled on: ";
    ptr += GB.dateTime("l,");
    ptr += "<br>";
    ptr += GB.dateTime("d-M-y H:i:s T");
    ptr += "</p>";

    ptr += "</div>\n";
    ptr += "</body>\n";
    ptr += "</html>\n";
    return ptr;
}
