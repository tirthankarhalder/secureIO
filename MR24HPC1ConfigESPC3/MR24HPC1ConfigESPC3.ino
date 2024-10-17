#include "Arduino.h"
#include <humanstaticLite.h>
// #include <U8x8lib.h>
#include <Wire.h>
#include<HardwareSerial.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif


#define PIN        D0 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 8 // Popular NeoPixel ring size



HardwareSerial UART(0);
HumanStaticLite radar = HumanStaticLite(&UART);

const unsigned char scene_buff[10] = {0x53, 0x59, 0x05, 0x07, 0x00, 0x01, 0x02, 0xBB, 0x54, 0x43}; 
const unsigned char sensitivity_buff[10] = {0x53, 0x59, 0x05, 0x08, 0x00, 0x01, 0x02, 0xBC, 0x54, 0x43}; 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

void setup() {

  Serial.begin(115200);
  //Serial1.begin(115200);
  UART.begin(115200, SERIAL_8N1, -1, -1); 

  
  pixels.begin();
  pixels.setBrightness(100);
  setRingColor(255, 255, 255);
  delay(10000);


  //first reset the radar
  radar.reset_func();
  setRingColor(255, 0, 0);
  delay(5000);
  setRingColor(255, 255, 255);
  delay(5000);


  //set scene to object detection
  radar.checkSetMode_func(scene_buff, 10, false);
  delay(1000);   //Do not set the delay time too long, as this may affect the reception of the data frames returned by the radar.
  setRingColor(0, 0, 255);
  delay(5000);
  setRingColor(255, 255, 255);
  delay(5000);

  //set sensitivity to 2
  radar.checkSetMode_func(sensitivity_buff, 10, false);
  delay(1000);   //Do not set the delay time too long, as this may affect the reception of the data frames returned by the radar.
  setRingColor(0, 255, 0);
  delay(5000);

  

}

void blink(){
  
}

void setRingColor(uint8_t r, uint8_t g, uint8_t b){
  pixels.clear();
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(r, g, b));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(50); // Pause before next pass through loop
  }
  
}


void loop() {

  



}