#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11   // DHT 11

#define wifi_ssid "makerspace"
#define wifi_password "CursoDom"

#define mqtt_server "ingresa_tu_ip"
#define mqtt_user "admin"
#define mqtt_password "12341234"

#define temperatura_topic "sensor/temperatura"
#define humedad_topic "sensor/humedad"

DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);



void setup() {
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);//resolver porque no se reconecta solo 
  dht.begin();
}


int contador=0;
void loop() {
  //attachInterrupt(digitalPinToInterrupt(btn_pin), btnHandler(), RISING);
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int h = dht.readHumidity();
  int t = dht.readTemperature();

  Serial.println(h);
  Serial.println(t);
  Serial.println("");


  if(contador > 30000 ){
  client.publish(temperatura_topic, String(t).c_str());
  client.publish(humedad_topic, String(h).c_str());
  contador=0;
  }
  else{
    contador++;
  }
}


void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
    
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
    
  }
  
}

