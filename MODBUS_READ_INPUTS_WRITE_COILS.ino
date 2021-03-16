/*
  Modbus-Arduino Example - Test Analog Input (Modbus IP ESP8266)
  Read Analog sensor on Pin ADC (ADC input between 0 ... 1V)
  Original library
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino

  Current version
  (c)2017 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
*/

#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else //ESP32
 #include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>

//Modbus Registers Offsets
//const int LED_COIL = 100;
//const int SENSOR_IREG = 200;

int REG1, REG2, REG3, REG4, REG5, REGCOIL;



//Used Pins
const int ledPin = 2; //LED ESP8266 - MODELO WEMOS D1 MINI

//ModbusIP object
ModbusIP mb;

IPAddress ip(192, 168, 1, 119);            // IP address of the server
IPAddress gateway(192,168,1,1);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network

long ts;

void setup() {
    Serial.begin(115200);
    WiFi.config(ip, gateway, subnet);
    WiFi.begin("WExternal", "Romanos#83839");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    mb.server();		//Start Modbus IP
    // USO DE REGISTROS DE MODBUS TCP
    mb.addIreg(200); // EndereçoS de Registro Modbus TCP
    mb.addIreg(201);
    mb.addIreg(202);
    mb.addIreg(203);
    mb.addIreg(204);
    mb.addIreg(205);
    mb.addIreg(206);
    mb.addIreg(207);
    mb.addIreg(208);
 
    //pinMode(D1, INPUT_PULLUP);
    pinMode(D2, INPUT_PULLUP);
    pinMode(D3, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
    pinMode(D8, OUTPUT);
    digitalWrite(D0, HIGH);
    digitalWrite(D1, HIGH);
    digitalWrite(D5, HIGH);
    digitalWrite(D6, HIGH);
    digitalWrite(D7, HIGH);
    digitalWrite(D8, HIGH);
    mb.addCoil(100);
    mb.addCoil(101);
    mb.addCoil(102);
    mb.addCoil(103);
    mb.addCoil(104);
    mb.addCoil(105);
    mb.addCoil(106);
    mb.addCoil(107);
    //mb.addCoil(108);
    REG1 = 1;
    REG2 = 2;
    REG3 = 3;
    REG4 = 4;
    REG5 = 5;
    

    ts = millis();
}

void loop() {
   //Call once inside loop() - all magic here
   mb.task();
   //Attach ledPin to LED_COIL register
   //int ED1 = digitalRead(D1); //ENTRADA DIGITAL 1 - D1
   int ED2 = digitalRead(D2); //ENTRADA DIGITAL 1 - D2
   int ED3 = digitalRead(D3); //ENTRADA DIGITAL 2 - D3

   //Read each two seconds
   if (millis() > ts + 10) {
       ts = millis();
       //Setting raw value (0-1024)
       mb.Ireg(200, analogRead(A0));
       //mb.Ireg(201, not ED1);
       mb.Ireg(201, not ED2);
       mb.Ireg(202, not ED3);
  
       mb.Ireg(203, REG1);
       mb.Ireg(204, REG2);
       mb.Ireg(205, REG3);
       mb.Ireg(206, REG4);
       mb.Ireg(207, REG5);
       
       digitalWrite(ledPin, not mb.Coil(100));
       digitalWrite(D0,  not mb.Coil(101));
       digitalWrite(D1,  not mb.Coil(102));
       digitalWrite(D5, not mb.Coil(103));
       digitalWrite(D6, not mb.Coil(104));
       digitalWrite(D7, not mb.Coil(105));
       digitalWrite(D8, not mb.Coil(106));
       digitalWrite(REGCOIL,  mb.Coil(107));
   }
   delay(10);
}
