#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define wifi_ssid "makerspace"
#define wifi_password "W#z5rdSu31*tZXV7m%"

#define mqtt_server "hassio3b1.local"
#define mqtt_user "admin"
#define mqtt_password "12341234"

#define switch1_topic_sta "hb31/switch1/status"
#define switch1_topic_com "hb31/switch1/command"

#define switch2_topic_sta "hb31/switch2/status"
#define switch2_topic_com "hb31/switch2/command"

WiFiClient espClient;
PubSubClient client(espClient);

bool switch1_status=0;
bool switch1_status_bandera=0;
bool switch2_status=0;
bool switch2_status_bandera=0;
const int ms = 50;

void callback(char* topic, byte* payload, unsigned int length) {
  String topicS = topic;
  String payloadS = "";

  for (int i=0;i<length;i++) {
    payloadS = payloadS + (char)payload[i];
  }
  Serial.println();
  Serial.println(topicS);
  Serial.println(payloadS);

  if (topicS.equals(switch1_topic_com)){
    
    if(payloadS.equals("1")){//payloadS.equals("ON") 
      switch1_status = 1;
      switch1_status_bandera = 1;
      Serial.println("se recibio 1");
    }
    if(payloadS.equals("0") ){
      switch1_status = 0;
      switch1_status_bandera = 1;
      Serial.println("se recibio 0");
    }
  }
  else if (topicS.equals(switch2_topic_com)){
    
    if(payloadS.equals("1")){//payloadS.equals("ON") 
      switch2_status = 1;
      switch2_status_bandera = 1;
      Serial.println("se recibio 1");
    }
    if(payloadS.equals("0") ){
      switch2_status = 0;
      switch2_status_bandera = 1;
      Serial.println("se recibio 0");
    }
  }

  Serial.println("");
}

void setup() {
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);//resolver porque no se reconecta solo 
  client.setCallback(callback);
}

void loop() {
  //attachInterrupt(digitalPinToInterrupt(btn_pin), btnHandler(), RISING);
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  if(switch1_status_bandera == 1){
    //digitalWrite(recamara1_pin,recamara1_status);
    switch1_status_bandera =0;
    if (switch1_status) {
      //digitalWrite(switch1_pin,1);
      //turn relay 1 on
        Serial.write(0xA0);
        Serial.write(0x01);
        Serial.write(0x01);
        Serial.write(0xA2);
        delay(ms);
      client.publish(switch1_topic_sta, "1");
    }
    else {
      //digitalWrite(switch1_pin,0);
      //turn relay 1 off
        Serial.write(0xA0);
        Serial.write(0x01);
        Serial.write(0x00);
        Serial.write(0xA1);
        delay(ms); 
      client.publish(switch1_topic_sta, "0");
    }
  }
  if(switch2_status_bandera == 1){
    //digitalWrite(recamara1_pin,recamara1_status);
    switch2_status_bandera =0;
    if (switch2_status) {
      //digitalWrite(switch1_pin,1);
      //turn relay 2 on
        Serial.write(0xA0);
        Serial.write(0x02);
        Serial.write(0x01);
        Serial.write(0xA3);
        delay(ms);
      client.publish(switch2_topic_sta, "1");
    }
    else {
      //digitalWrite(switch1_pin,0);
      //turn relay 2 off
        Serial.write(0xA0);
        Serial.write(0x02);
        Serial.write(0x00);
        Serial.write(0xA2);
        delay(ms); 
      client.publish(switch2_topic_sta, "0");
    }
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
    /*
    setup_wifi();
    client.setServer(mqtt_server, 1883);//intento de resolver porque no se reconecta solo 
    client.setCallback(callback);//mismo intento
    delay(2);*/
    
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.subscribe(switch1_topic_com);
      client.subscribe(switch2_topic_com);
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

