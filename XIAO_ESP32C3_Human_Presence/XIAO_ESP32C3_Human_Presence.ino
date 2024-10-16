#include "Arduino.h"
#include <humanstaticLite.h>
#include <U8x8lib.h>
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

U8X8_SSD1306_128X64_NONAME_HW_I2C display(/* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display
//int led = D0;
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);
uint8_t brightness = 100;

void setup() {

  Serial.begin(115200);
  UART.begin(115200, SERIAL_8N1, -1, -1); 

  
  pixels.begin();
  pixels.setBrightness(100);
  setRingColor(255, 255, 255);
  delay(5000);
  

}



void setRingColor(uint8_t r, uint8_t g, uint8_t b){
  pixels.clear();
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(r, g, b));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(25); // Pause before next pass through loop
  }
  
}


void loop() {

  
  
  // // put your main code here, to run repeatedly:
  radar.HumanStatic_func(false);    //Turn off printing of human movement sign parameters
  int radarStatus = radar.radarStatus ;
  pixels.setBrightness(255);

  if(radarStatus != 0x00){
    switch(radar.radarStatus){
      Serial.println(radar.radarStatus);
      case SOMEONE:
        Serial.println("Someone is here.");
        Serial.println("---------------------------------");
        setRingColor(0, 255, 0); //green
        break;
      case NOONE:
        Serial.println("Nobody here.");
        Serial.println("---------------------------------");
        setRingColor(255, 255, 255); //white
        break;
      case NOTHING:
        Serial.println("No human activity messages.");
        Serial.println("---------------------------------");
        setRingColor(255, 255, 255); //white
        break;
      case SOMEONE_STOP:
        Serial.println("Someone stop");
        Serial.println("---------------------------------");
        setRingColor(255, 0, 0); //red
        break;
      case SOMEONE_MOVE:
        Serial.println("Someone moving");
        Serial.println("---------------------------------");
        setRingColor(255,255,0); //yellow
        break;
      case HUMANPARA:
        Serial.print("The parameters of human body signs are: ");
        Serial.println(radar.bodysign_val, DEC);
        Serial.println("---------------------------------");
        
        pixels.setBrightness(5);
        setRingColor(0, 255, 0); //light green
        
        break;
      case SOMEONE_CLOSE:
        Serial.println("Someone is closing");
        Serial.println("---------------------------------");
        setRingColor(0, 0, 255); //blue
        break;
      case SOMEONE_AWAY:
        Serial.println("Someone is staying away");
        Serial.println("---------------------------------");
        pixels.setBrightness(5);
        setRingColor(0,0,255); //light blue
        
        break;
      case DETAILMESSAGE:
        Serial.print("Spatial static values: ");
        Serial.println(radar.static_val, DEC);
        Serial.print("Distance to stationary object: ");
        Serial.println(radar.dynamic_val, DEC);
        Serial.print("Spatial dynamic values: ");
        Serial.println(radar.dis_static, DEC);
        Serial.print("Distance from the movement object: ");
        Serial.println(radar.dis_move, DEC);
        Serial.print("Speed of moving object: ");
        Serial.println(radar.speed, DEC);
        Serial.println("---------------------------------");
        setRingColor(0, 0, 0); //cyan
        break;
    }
  }else{
    
  }
  delay(200);


}