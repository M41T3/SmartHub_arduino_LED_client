#include "FastLED.h"

#define NUM_LEDS 39
#define DATA_PIN 3
CRGB leds[NUM_LEDS];

int incomingByte = 0;  
int byteNum = 0;  // 0 red 1 green 2 blue 3 byteNum
float lastData = 0;

int red = 0;
int green = 0;
int blue = 0;
int mode = 0;

void setup() {
        FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
        Serial.begin(115200);
}

void loop() {

        // send data only when you receive data:

        if(byteNum != 0 && millis() - lastData >= 1000){
          byteNum = 0;
          Serial.println("lost data..");
          }

        
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();
   
                if(byteNum == 0){
                    lastData = millis();
                    red = incomingByte;
                    byteNum++;
                  }
                 else if(byteNum == 1){
                    lastData = millis();
                    green = incomingByte;
                    byteNum++;
                  }
                  else if(byteNum == 2){
                    lastData = millis(); 
                    blue = incomingByte;
                    byteNum++; 
                  }
                  else if(byteNum == 3){
                    lastData = millis(); 
                    mode = incomingByte;
                    byteNum = 0; 
                    setLEDs();
                  }  
              
        }

        
}

void setLEDs(){

  for(int i = 0; i < NUM_LEDS; i++){
    leds[i].setRGB( red, green, blue);
    }

  FastLED.show();
  }
 
