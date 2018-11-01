/*
   1 : LED
   4 : water pump
   3 : DHT
   2 : heater
   A0 : soil moisture
   A1 : Light


*/

#include "DHT.h"

#define DHTPIN 3     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11


String command;
float h;
float t;
String soil;
String rad;
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  

pinMode(1, OUTPUT);
pinMode(4, OUTPUT);
pinMode(12, OUTPUT);
pinMode(2, OUTPUT);

  dht.begin();
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
    else if (command == "L1") {
      digitalWrite(1, HIGH);
    }
    else if (command == "L0") {
      digitalWrite(1, LOW);
    }
    else if (command == "data") {
      delay(1000);
      h = dht.readHumidity();
      t = dht.readTemperature();
      
      if(analogRead(A0)<=999){
        soil="0"+String(analogRead(A0));
      }
      else{
        soil=String(analogRead(A0));
      }
      if(analogRead(A1)<=999){
        rad="0"+String(analogRead(A1));
      }else{
        rad=String(analogRead(A1));
      }
      Serial.println(String(dht.computeHeatIndex(t, h, false))+String(h)+soil+rad+";");
      Serial.flush();
    } 
  }
}


