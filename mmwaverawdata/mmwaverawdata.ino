#include "Arduino.h"
#include <humanstaticLite.h>
// #include <SoftwareSerial.h>
// Choose any two pins that can be used with SoftwareSerial to RX & TX
// #define RX_Pin D6
// #define TX_Pin D7

// SoftwareSerial mySerial = SoftwareSerial(RX_Pin, TX_Pin);

// we'll be using software serial
// HumanStaticLite radar = HumanStaticLite(&mySerial);

// can also try hardware serial with
HumanStaticLite radar = HumanStaticLite(&Serial1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  
  //  mySerial.begin(115200);

  while(!Serial);   //When the serial port is opened, the program starts to execute.

  Serial.println("Readly");
}

void loop() {
  // put your main code here, to run repeatedly:
  radar.recvRadarBytes();           //Receive radar data and start processing
  radar.showData();    
  Serial.println("Starting program");             //Serial port prints a set of received data frames
  delay(200);                       //Add time delay to avoid program jam
}