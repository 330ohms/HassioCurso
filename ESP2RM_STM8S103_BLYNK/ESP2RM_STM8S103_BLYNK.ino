const int ms = 20;

void setup() {    
  pinMode(2, OUTPUT);

  digitalWrite(2,LOW);
  Serial.begin(115200, SERIAL_8N1);
}

// the loop function runs over and over again forever
void loop() {
  
        //turn relay 1 on
        Serial.write(0xA0);
        Serial.write(0x01);
        Serial.write(0x01);
        Serial.write(0xA2);
        delay(ms);
        //turn relay 2 on
        Serial.write(0xA0);
        Serial.write(0x02);
        Serial.write(0x01);
        Serial.write(0xA3);
        delay(1000);                      // Wait for a second
        
        //turn relay 1 off
        Serial.write(0xA0);
        Serial.write(0x01);
        Serial.write(0x00);
        Serial.write(0xA1);
        delay(ms); 
        //turn relay 2 off
        Serial.write(0xA0);
        Serial.write(0x02);
        Serial.write(0x00);
        Serial.write(0xA2);
        delay(2000);                      // Wait for two seconds 
}
