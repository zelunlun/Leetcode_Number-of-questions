#include <LWiFi.h>
#include "DHT.h"
#include <PubSubClient.h>
#include <Grove_LED_Bar.h>

#define DHTPIN A0 
#define DHTTYPE DHT22

Grove_LED_Bar bar(9, 8, 0); 
DHT dht(DHTPIN, DHTTYPE);

// WiFi AP ssid / password here
//char ssid[] = ".1. Free Wi-Fi";      //  your network SSID (name)
//char pass[] = "easonlin0921";  // your network password (use for WPA, or use as key for WEP)
char ssid[] = "3715";
char pass[] = "12345678";

// MQTT Broker info
//IPAddress server(140, 127, 196, 119);
char server[] = "broker.hivemq.com";
int port = 1883;
char str[3];


// MQTT Client info
// Client ID.
// Note that a broker allows an individual client to create only on session.
// If a session is created by another client with same cliend ID, the former one will be disconnected.
// Thus, each sensor node's client must be different from each other. 
char client_id[] = "isu10903027a"; 

// MQTT topics
#define TOPIC_INFO  "isu10903027a/info"
#define TOPIC_RANGEINCENTIMETERS  "isu10903103a/sensor/RangeInCentimeters"
//#define TOPIC_HUM   "10903095A/sensor/hum"
//#define TOPIC_LED_CONTROL "10903095A/control/led"

// Clients for MQTT
WiFiClient wifiClient;
PubSubClient client(wifiClient);

// LED Control info
//#define LED_PIN LED_BUILTIN
//typedef enum {
//  LED_OFF = 0,
//  LED_ON,
//  LED_FLASH
//} LEDStatus;
//LEDStatus led_status = LED_OFF;

// Timer info
//#define TEMP_PERIOD 10000
//#define LED_FLASH_PERIOD 200
//unsigned long temp_last_time, led_last_time;
//
//void led_on(){
//  digitalWrite(LED_PIN, HIGH);
//}
//
//void led_off(){
//  digitalWrite(LED_PIN, LOW);
//}
//
//void led_toggle() {
//  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
//}

void callback(char* topic, byte* payload, unsigned int length) {
  // Output incoming message to serial terminal
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    str[i] = char(payload[i]);
  }
  int distance = atoi(str);
  Serial.println(distance);

  // If LED Control command is incoming, change LED status
//這裡
//  if(!strcmp(topic, TOPIC_DISTANCE)) {
//    distance = payload[0];
//    Serial.println("Hi, ");
//    Serial.println(distance);

//這裡
  if (distance >= 50){
    bar.setBits(0);
    }
  else if (45 <= distance && distance < 50){
    bar.setBits(1);
    } 
  else if (40 <= distance && distance < 45){
    bar.setBits(3);
    }
  else if (35 <= distance && distance < 40){
    bar.setBits(7);
    }
  else if (30 <= distance && distance < 35){
    bar.setBits(15);
    }
  else if (25 <= distance && distance < 30){
    bar.setBits(31);
    }
  else if (20 <= distance && distance < 25){
    bar.setBits(63);
    }
  else if (15 <= distance && distance < 20){
    bar.setBits(127);
    }
  else if (10 <= distance && distance < 15){
    bar.setBits(255);
    }
  else if (5 <= distance && distance < 10){
    bar.setBits(511);
    }
  else if (0 <= distance && distance < 5){
    bar.setBits(1023);
    }
  memset(str, 0, sizeof(str));
//    
//  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(client_id)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(TOPIC_INFO,"sensor node ready ...");
      // ... and resubscribe
      client.subscribe(TOPIC_RANGEINCENTIMETERS);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // setup Serial output at 9600
  Serial.begin(9600);
  bar.begin();

  // Set MQTT broker
  client.setServer(server, port);
  client.setCallback(callback);

  // start up DHT sensor
//  dht.begin();

  // setup LED/Button pin
//  pinMode(LED_PIN, OUTPUT);
//  led_off();
  
  // setup Wifi connection
  while(WL_CONNECTED != WiFi.status())
  {
    Serial.print("WiFi.begin(");
    Serial.print(ssid);
    Serial.print(",");
    Serial.print(pass);
    Serial.println(")...");
    WiFi.begin(ssid, pass);
  }
  Serial.println("WiFi connected !!");
  printWifiStatus();

//  led_last_time = millis();
//  temp_last_time = millis();
}

void loop() {
  unsigned long current_time;

  // Check MQTT broker connection status
  // If it is disconnected, reconnect to the broker
  if (!client.connected()) {
    reconnect();
  }

  // Get temperature & humidity and publish them
  current_time = millis();
//  if( TEMP_PERIOD < (current_time - temp_last_time) ) {
//    // Read Humidity & Temperature (Celsius)
//    float h = dht.readHumidity();
//    float t = dht.readTemperature();
//    // Output to serial terminal
//    Serial.print("Humidity: ");
//    Serial.print(h);
//    Serial.print(" %\t");
//    Serial.print("Temperature: ");
//    Serial.print(t);
//    Serial.println(" *C ");
//    // pubilsh to MQTT broker
//    char buf[10];
//    sprintf(buf,"%s", String((float)t, 2).c_str());
//    client.publish(TOPIC_TEMP, buf);
//    sprintf(buf,"%s", String((float)h, 2).c_str());
//    client.publish(TOPIC_HUM, buf);
//    // update last time value
//    temp_last_time = current_time;
//  }
  
  // Control LED according to led_status
//  switch (led_status) {
//    case LED_OFF:
//      led_off();
//      break;
//    case LED_ON:
//      led_on();
//      break;
//    case LED_FLASH:
//      current_time = millis();
//      if (LED_FLASH_PERIOD < (current_time - led_last_time)) {
//        led_toggle();
//        led_last_time = current_time;
//      }
//      break;
//    default: {}
//  }
  
  // Keep MQTT process on going
  client.loop();
}

void printWifiStatus() {
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}
