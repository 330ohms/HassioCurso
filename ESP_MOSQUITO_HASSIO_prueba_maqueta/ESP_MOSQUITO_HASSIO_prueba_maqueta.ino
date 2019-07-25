#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define wifi_ssid "raspiCurso"
#define wifi_password "raspberry330"

#define mqtt_server "hassio.local"
#define mqtt_user "admin"
#define mqtt_password "12341234"

#define recamara1_topic_sta "demo/light-mqtt-recamara1/status"
#define recamara1_topic_com "demo/light-mqtt-recamara1/command"
#define recamara1_brillo_sta "demo/light-mqtt-recamara1/brightness-status"
#define recamara1_brillo_com "demo/light-mqtt-recamara1/brightness-command"

#define recamara2_topic_sta "demo/light-mqtt-recamara2/status"
#define recamara2_topic_com "demo/light-mqtt-recamara2/command"
#define recamara2_brillo_sta "demo/light-mqtt-recamara2/brightness-status"
#define recamara2_brillo_com "demo/light-mqtt-recamara2/brightness-command"

#define sala_topic_sta "demo/light-mqtt-sala/status"
#define sala_topic_com "demo/light-mqtt-sala/command"
#define sala_brillo_sta "demo/light-mqtt-sala/brightness-status"
#define sala_brillo_com "demo/light-mqtt-sala/brightness-command"

#define bano_topic_sta "demo/light-mqtt-bano/status"
#define bano_topic_com "demo/light-mqtt-bano/command"

#define comedor_topic_sta "demo/light-mqtt-comedor/status"
#define comedor_topic_com "demo/light-mqtt-comedor/command"

#define cocina_topic_sta "demo/light-mqtt-cocina/status"
#define cocina_topic_com "demo/light-mqtt-cocina/command"

#define pp_topic_sta "demo/lock-mqtt-puerta-principal/status"
#define pp_topic_com "demo/lock-mqtt-puerta-principal/command"

#define pt_topic_sta "demo/lock-mqtt-puerta-trasera/status"
#define pt_topic_com "demo/lock-mqtt-puerta-trasera/command"

#define refri_topic_sta "demo/switch-refrigerador/status"
#define refri_topic_com "demo/switch-refrigerador/command"

#define temperatura_topic "demo/sensor-mqtt/temperatura"


WiFiClient espClient;
PubSubClient client(espClient);

int  recamara1_pin=5;
bool recamara1_status=0;
bool recamara1_status_bandera=0;
int  recamara1_brillo=255;

int  recamara2_pin=4;
bool recamara2_status=0;
bool recamara2_status_bandera=0;
int  recamara2_brillo=255;

int  sala_pin=0;
bool sala_status=0;
bool sala_status_bandera=0;
int  sala_brillo=255;

int  comedor_pin=2;
bool comedor_status=0;
bool comedor_status_bandera=0;

int  cocina_pin=14;
bool cocina_status=0;
bool cocina_status_bandera=0;

int  bano_pin=12;
bool bano_status=0;
bool bano_status_bandera=0;

int  refri_pin=13;
bool refri_status=0;
bool refri_status_bandera=13;

int  pt_pin=15;
bool pt_status=0;
bool pt_status_bandera=0;

int  pp_pin=16;
bool pp_status=0;
bool pp_status_bandera=0;

int temperatura = 0;
int contadorT =0 ;

void callback(char* topic, byte* payload, unsigned int length) {
  String topicS = topic;
  String payloadS = "";
  for (int i=0;i<length;i++) {
    payloadS = payloadS + (char)payload[i];
  }
  Serial.println();
  Serial.println(topicS);
  Serial.println(payloadS);
  
  if (topicS.equals(recamara1_topic_com)){
    
    if(payloadS.equals("ON")){//payloadS.equals("ON") 
      recamara1_status = 1;
      recamara1_status_bandera = 1;
      Serial.println("se recibio ON");
    }
    if(payloadS.equals("OFF") ){
      recamara1_status = 0;
      recamara1_status_bandera = 1;
      Serial.println("se recibio OFF");
    }
  }
  else if(topicS.equals(recamara1_brillo_com)){
 
      recamara1_brillo = payloadS.toInt();
      //recamara1_brillo_bandera = 1;
      Serial.println("se recibio brillo");
  }

  else if (topicS.equals(recamara2_topic_com)){
    
    if(payloadS.equals("ON")){//payloadS.equals("ON") 
      recamara2_status = 1;
      recamara2_status_bandera = 1;
      Serial.println("se recibio ON");
    }
    if(payloadS.equals("OFF") ){
      recamara2_status = 0;
      recamara2_status_bandera = 1;
      Serial.println("se recibio OFF");
    }
  }
  else if(topicS.equals(recamara2_brillo_com)){
 
      recamara2_brillo = payloadS.toInt();
      //recamara2_brillo_bandera = 1;
      Serial.println("se recibio brillo");
  }

  else if (topicS.equals(sala_topic_com)){
    
    if(payloadS.equals("ON")){//payloadS.equals("ON") 
      sala_status = 1;
      sala_status_bandera = 1;
      Serial.println("se recibio ON");
    }
    if(payloadS.equals("OFF") ){
      sala_status = 0;
      sala_status_bandera = 1;
      Serial.println("se recibio OFF");
    }
  }
  else if(topicS.equals(sala_brillo_com)){
 
      sala_brillo = payloadS.toInt();
      //recamara2_brillo_bandera = 1;
      Serial.println("se recibio brillo");
  }

  else if (topicS.equals(bano_topic_com)){
    
    if(payloadS.equals("ON")){//payloadS.equals("ON") 
      bano_status = 1;
      bano_status_bandera = 1;
      Serial.println("se recibio ON");
    }
    if(payloadS.equals("OFF") ){
      bano_status = 0;
      bano_status_bandera = 1;
      Serial.println("se recibio OFF");
    }
  }

  else if (topicS.equals(cocina_topic_com)){
    
    if(payloadS.equals("ON")){//payloadS.equals("ON") 
      cocina_status = 1;
      cocina_status_bandera = 1;
      Serial.println("se recibio ON");
    }
    if(payloadS.equals("OFF") ){
      cocina_status = 0;
      cocina_status_bandera = 1;
      Serial.println("se recibio OFF");
    }
  }

  else if (topicS.equals(comedor_topic_com)){
    
    if(payloadS.equals("ON")){//payloadS.equals("ON") 
      comedor_status = 1;
      comedor_status_bandera = 1;
      Serial.println("se recibio ON");
    }
    if(payloadS.equals("OFF") ){
      comedor_status = 0;
      comedor_status_bandera = 1;
      Serial.println("se recibio OFF");
    }
  }

  else if (topicS.equals(refri_topic_com)){
    
    if(payloadS.equals("1")){//payloadS.equals("ON") 
      refri_status = 1;
      refri_status_bandera = 1;
      Serial.println("se recibio 1");
    }
    if(payloadS.equals("0") ){
      refri_status = 0;
      refri_status_bandera = 1;
      Serial.println("se recibio 0");
    }
  }

  else if (topicS.equals(pp_topic_com)){
    
    if(payloadS.equals("LOCK")){//payloadS.equals("ON") 
      pp_status = 1;
      pp_status_bandera = 1;
      Serial.println("se recibio LOCK");
    }
    if(payloadS.equals("UNLOCK") ){
      pp_status = 0;
      pp_status_bandera = 1;
      Serial.println("se recibio OFF");
    }
  }

  else if (topicS.equals(pt_topic_com)){
    
    if(payloadS.equals("LOCK")){//payloadS.equals("ON") 
      pt_status = 1;
      pt_status_bandera = 1;
      Serial.println("se recibio LOCK");
    }
    if(payloadS.equals("UNLOCK") ){
      pt_status = 0;
      pt_status_bandera = 1;
      Serial.println("se recibio OFF");
    }
  }
  

  Serial.println("");
}


void setup() {
  pinMode(recamara1_pin,OUTPUT);
  pinMode(recamara2_pin,OUTPUT);
  pinMode(sala_pin,OUTPUT);
  pinMode(bano_pin,OUTPUT);
  pinMode(cocina_pin,OUTPUT);
  pinMode(comedor_pin,OUTPUT);
  pinMode(refri_pin,OUTPUT);
  pinMode(pp_pin,OUTPUT);
  pinMode(pt_pin,OUTPUT);
  
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
  
  if(recamara1_status_bandera == 1){
    //digitalWrite(recamara1_pin,recamara1_status);
    recamara1_status_bandera =0;
    if (recamara1_status) {
      analogWrite(recamara1_pin,recamara1_brillo);
      client.publish(recamara1_brillo_sta, String(recamara1_brillo).c_str());
      client.publish(recamara1_topic_sta, "ON");
    }
    else {
      analogWrite(recamara1_pin,0);
      client.publish(recamara1_topic_sta, "OFF");
    }
  }

  if(recamara2_status_bandera == 1){
    //digitalWrite(recamara1_pin,recamara1_status);
    recamara2_status_bandera =0;
    if (recamara2_status) {
      analogWrite(recamara2_pin,recamara2_brillo);
      client.publish(recamara2_brillo_sta, String(recamara2_brillo).c_str());
      client.publish(recamara2_topic_sta, "ON");
    }
    else {
      analogWrite(recamara2_pin,0);
      client.publish(recamara2_topic_sta, "OFF");
    }
  }

  if(sala_status_bandera == 1){
    //digitalWrite(recamara1_pin,recamara1_status);
    sala_status_bandera =0;
    if (sala_status) {
      analogWrite(sala_pin,sala_brillo);
      client.publish(sala_brillo_sta, String(sala_brillo).c_str());
      client.publish(sala_topic_sta, "ON");
    }
    else {
      analogWrite(sala_pin,0);
      client.publish(sala_topic_sta, "OFF");
    }
  }

  if(bano_status_bandera == 1){
    //digitalWrite(recamara1_pin,recamara1_status);
    bano_status_bandera =0;
    if (bano_status) {
      digitalWrite(bano_pin,1);
      client.publish(bano_topic_sta, "ON");
    }
    else {
      digitalWrite(bano_pin,0);
      client.publish(bano_topic_sta, "OFF");
    }
  }

  if(cocina_status_bandera == 1){
    //digitalWrite(recamara1_pin,recamara1_status);
    cocina_status_bandera =0;
    if (cocina_status) {
      digitalWrite(cocina_pin,1);
      client.publish(cocina_topic_sta, "ON");
    }
    else {
      digitalWrite(cocina_pin,0);
      client.publish(cocina_topic_sta, "OFF");
    }
  }

  if(comedor_status_bandera == 1){
    //digitalWrite(recamara1_pin,recamara1_status);
    comedor_status_bandera =0;
    if (comedor_status) {
      digitalWrite(comedor_pin,1);
      client.publish(comedor_topic_sta, "ON");
    }
    else {
      digitalWrite(comedor_pin,0);
      client.publish(comedor_topic_sta, "OFF");
    }
  }

  if(refri_status_bandera == 1){
    //digitalWrite(recamara1_pin,recamara1_status);
    refri_status_bandera =0;
    if (refri_status) {
      digitalWrite(refri_pin,1);
      client.publish(refri_topic_sta, "1");
    }
    else {
      digitalWrite(refri_pin,0);
      client.publish(refri_topic_sta, "0");
    }
  }

  if(pp_status_bandera == 1){
    //digitalWrite(recamara1_pin,recamara1_status);
    pp_status_bandera =0;
    if (pp_status) {
      digitalWrite(pp_pin,1);
      client.publish(pp_topic_sta, "LOCK");
    }
    else {
      digitalWrite(pp_pin,0);
      client.publish(pp_topic_sta, "UNLOCK");
    }
  }

  if(pt_status_bandera == 1){
    //digitalWrite(recamara1_pin,recamara1_status);
    pt_status_bandera =0;
    if (pt_status) {
      digitalWrite(pt_pin,1);
      client.publish(pt_topic_sta, "LOCK");
    }
    else {
      digitalWrite(pt_pin,0);
      client.publish(pt_topic_sta, "UNLOCK");
    }
  }

  if(contadorT > 50000){
  temperatura = map(analogRead(0), 0, 1023, 0, 330) -50;
  client.publish(temperatura_topic,String(temperatura).c_str());
  Serial.println(temperatura);
  contadorT =0;
  }
  else{
    contadorT++;
  }
  
  
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
      client.subscribe(recamara1_topic_com);
      client.subscribe(recamara1_brillo_com);
      client.subscribe(recamara2_topic_com);
      client.subscribe(recamara2_brillo_com);
      client.subscribe(sala_topic_com);
      client.subscribe(sala_brillo_com);
      client.subscribe(bano_topic_com);
      client.subscribe(cocina_topic_com);
      client.subscribe(comedor_topic_com);
      client.subscribe(refri_topic_com);
      client.subscribe(pp_topic_com);
      client.subscribe(pt_topic_com);
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
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



