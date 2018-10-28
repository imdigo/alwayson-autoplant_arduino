/*
   1 : LED
   4 : water pump
   12 : humidifier
   3 : DHT
   2 : heater
   A0 : soil moisture
   A1 : Light


*/

#include <DHT11.h>

int rad = 0;
float temp = 0;
float humi = 0;
int soi = 0;
String command;
DHT11 dht11(3);

void setup() {
  

pinMode(1, OUTPUT);
pinMode(4, OUTPUT);
pinMode(12, OUTPUT);
pinMode(2, OUTPUT);


  Serial.begin(9600);
}

void loop() {

  if (Serial.available()) {
    command = Serial.readString();
    if (command == "W1") {
      digitalWrite(4, HIGH);
    }
    else if (command == "W0") {
      digitalWrite(4, LOW);
    }
    else if (command == "H1") {
      digitalWrite(2, HIGH);
    }
    else if (command == "H0") {
      digitalWrite(2, LOW);
    }
    else if (command == "U1") {
      digitalWrite(12, HIGH);
    }
    else if (command == "U0") {
      digitalWrite(12, LOW);
    }
    else if (command == "L1") {
      digitalWrite(1, HIGH);
    }
    else if (command == "L0") {
      digitalWrite(1, LOW);
    }

    else if (command == "DHT") {
      String s1;
      dht11.read(humi, temp);
      delay(DHT11_RETRY_DELAY); //온도
      sprintf(s1.c_str(), "DHT:temp%.2fhum%.2f", temp,humi);
      Serial.write(s1.c_str());

    }
    else if (command == "Soi") {
      soi = analogRead(0); //토양센서
      Serial.write("Soi:" + soi);
    }
    else if (command == "Rad") {
      rad = analogRead(1); //빛센서
      Serial.write("Rad:" + rad);
    }
  }


}
