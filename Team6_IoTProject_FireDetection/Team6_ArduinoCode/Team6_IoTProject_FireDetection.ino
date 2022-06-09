#University of Information Technology
#Team6_IoTSolutionForFireDetection
#Member
#Nguyễn Thanh Dũng - 19521397
#Huỳnh Quốc Huy - 19520594
#Võ Phú Thịnh - 19522289
#Trịnh Duy Khương - 19521715


#include <LiquidCrystal.h>
//LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
LiquidCrystal lcd(13,12,14,2,0,4);
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
String text = "";
const char *ssid = "UiTiOt-E3.1";
const char *password = "UiTiOtAP";
const char *mqtt_server = "172.31.250.214";
//int BUILTIN_LED;
//#define LED LED_BUILTIN;
byte LED1=16;
byte LED2=5;
byte buzzer=15;
WiFiClient espClient;
PubSubClient client(espClient); // hỗ trợ gửi nhận với giao thức mqtt

void setup_wifi();
void callback(char *topic, byte *payload, unsigned int length);
void reconnect();
void setup_mqtt();

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  setup_wifi();
  setup_mqtt();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();
}

void setup_mqtt() {
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void reconnect() {
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("fire");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  String text = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    text += (char)payload[i];
  }
  Serial.println();
  Serial.println("-----------------------");
    if (String(topic) == "fire") {
    Serial.print("Changing output to ");
//    if(text == "on"){
//      Serial.println("on");
//      digitalWrite(led, HIGH);
//    }
//    else if(text == "off"){
//      Serial.println("off");
//      digitalWrite(led, LOW);
//    }

     if(text == "p" )
      { 
        lcd.clear();
        lcd.print(" Fire Detected ");
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        tone(buzzer,220,125);
        delay(125);
        tone(buzzer,2093,250);
        delay(250);
        Serial.print("fire");
        delay(10000);
      }
      
    else if(text == "s")
     {
        lcd.clear();
        lcd.print(" NoThing        ");
        digitalWrite(LED2, HIGH);
        digitalWrite(LED1, LOW);
        Serial.print("nothing ");
   }
}
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
