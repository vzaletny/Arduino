#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 30
#define DELAY 30

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 12
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];
CRGB colors [] = {CRGB::Red, CRGB::Blue, CRGB::OrangeRed, CRGB::Aqua, CRGB::Gold, CRGB::DarkMagenta, CRGB::Green};

void setup() { 
      // Uncomment/edit one of the following lines for your leds arrangement.
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  	  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); //.setCorrection(TypicalSMD5050);
}

void garmoshka(int wait) {
  CRGB clr;  
  for(byte clr = 0; clr < sizeof(colors)/sizeof(colors[0]); clr++){
    for(byte i = 0; i < NUM_LEDS; i++){ 
      /*
      leds[i].r = 142; //96
      leds[i].g = 32; //64
      leds[i].b = 0;
      leds[NUM_LEDS - 1 - i].r = 142; //96
      leds[NUM_LEDS - 1 - i].g = 32; //64
      leds[NUM_LEDS - 1 - i].b = 0;
      */
      leds[i] = leds[NUM_LEDS - 1 - i] = colors[clr];
      FastLED.show();
      delay(wait);
      if (i == NUM_LEDS / 2 || i == 0 || i == NUM_LEDS - 1){
        delay(wait + 10);
      }
      leds[i] = leds[NUM_LEDS - 1 - i] = CRGB::Black;
      FastLED.show();
    }
  } 
}

void runnig_lights(int wait) {
  for(int num = 0; num < NUM_LEDS; num++){
    //for(int clr = 0; clr < sizeof(colors)/sizeof(colors[0]); clr++){
      for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = colors[num % 7];
        FastLED.show();
        delay(wait);
        if (i >= num){
          leds[i - num] = CRGB::Black;
          FastLED.show();                         
        }        
      }
      for(int i = num; i > 0; i--){
        delay(wait);
        leds[NUM_LEDS - i] = CRGB::Black;
        FastLED.show();        
      }
    //}
  }
  for(int num = 0; num < NUM_LEDS; num++){
    //for(int clr = 0; clr < sizeof(colors)/sizeof(colors[0]); clr++){
      for(int i = NUM_LEDS - 1; i >=0; i--){
        leds[i] = colors[num % 7];
        FastLED.show();
        delay(wait);
        if (i <= NUM_LEDS -1 - num){
          leds[i + num] = CRGB::Black;
          FastLED.show();                                        
        }  
      }
      for(int i = num; i >= 0; i--){        
        leds[i] = CRGB::Black;
        FastLED.show();       
        delay(wait); 
      }
    //}
  }         
}

void runnig_lights_reverse(int wait) {
  for(int num = 0; num < NUM_LEDS; num++){
    //for(int clr = 0; clr < sizeof(colors)/sizeof(colors[0]); clr++){
      for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = colors[num % 7];
        FastLED.show();
        delay(wait);
        if (i >= num){
          leds[i - num] = CRGB::Black;
          FastLED.show();                         
        }        
      }
      for(int i = num; i > 0; i--){
        delay(wait);
        leds[NUM_LEDS - i] = CRGB::Black;
        FastLED.show();        
      }
      delay(wait);
      for(int i = NUM_LEDS - 1; i >=0; i--){
        leds[i] = colors[num % 7];
        FastLED.show();
        delay(wait);
        if (i <= NUM_LEDS -1 - num){
          leds[i + num] = CRGB::Black;
          FastLED.show();                                        
        }  
      }
      for(int i = num; i >= 0; i--){        
        leds[i] = CRGB::Black;
        FastLED.show();       
        delay(wait); 
      }
    //}
  }
}  

void shadow(int wait){
  for(int num = 0; num < 5; num++){
    //for(int clr = 0; clr < sizeof(colors)/sizeof(colors[0]); clr++){
    for (int i = 0; i < NUM_LEDS; i++){
      leds[i] = colors[num % 7];
    }
      for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB::Black;
        FastLED.show();
        delay(wait);
        if (i >= num){
          leds[i - num] = colors[num % 7];
          FastLED.show();                         
        }        
      }
      for(int i = num; i > 0; i--){
        delay(wait);
        leds[NUM_LEDS - i] = colors[num % 7];
        FastLED.show();        
      }
    //}
  }
  for(int num = 0; num < 5; num++){    
    //for(int clr = 0; clr < sizeof(colors)/sizeof(colors[0]); clr++){
    for (int i = 0; i < NUM_LEDS; i++){
      leds[i] = colors[num % 7];
    }
      for(int i = NUM_LEDS - 1; i >=0; i--){
        leds[i] = CRGB::Black;
        FastLED.show();
        delay(wait);
        if (i <= NUM_LEDS -1 - num){
          leds[i + num] = colors[num % 7];
          FastLED.show();                                        
        }  
      }
      for(int i = num; i >= 0; i--){        
        leds[i] = colors[num % 7];
        FastLED.show();       
        delay(wait); 
      }
    //}
  }         
}


void shadow_reverse(int wait){
  for(int num = 0; num < 5; num++){
    //for(int clr = 0; clr < sizeof(colors)/sizeof(colors[0]); clr++){
    for (int i = 0; i < NUM_LEDS; i++){
      leds[i] = colors[num % 7];
    }
      for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB::Black;
        FastLED.show();
        delay(wait);
        if (i >= num){
          leds[i - num] = colors[num % 7];
          FastLED.show();                         
        }        
      }
      for(int i = num; i > 0; i--){
        delay(wait);
        leds[NUM_LEDS - i] = colors[num % 7];
        FastLED.show();        
      }      
      for(int i = NUM_LEDS - 1; i >=0; i--){
        leds[i] = CRGB::Black;
        FastLED.show();
        delay(wait);
        if (i <= NUM_LEDS -1 - num){
          leds[i + num] = colors[num % 7];
          FastLED.show();                                        
        }  
      }
      for(int i = num; i >= 0; i--){        
        leds[i] = colors[num % 7];
        FastLED.show();       
        delay(wait); 
      }
    //}
  } 
}

void stack(int wait){
  CRGB clr;
  for(int clr = 0; clr < sizeof(colors)/sizeof(colors[0]); clr++){
    for (int s = 0; s < NUM_LEDS; s++){
      for(int i = 0; i < NUM_LEDS - s; i++){
        leds[i] = colors[clr];
        FastLED.show();
        delay(wait);
        if (i < NUM_LEDS - s - 1){
          leds[i] = CRGB::Black;
          FastLED.show();        
        }    
      }
    }
    delay(wait);
    for (int s = NUM_LEDS; s >= 0; s--){
      for(int i = NUM_LEDS - s; i >= 0 ; i--){
        leds[i] = colors[clr];
        FastLED.show();
        delay(wait);
        if (i < NUM_LEDS - s){
          leds[i] = CRGB::Black;
          FastLED.show();        
        }    
      }
    }  
  }
}  
void loop() { 

  garmoshka(DELAY);  
  runnig_lights_reverse(DELAY);
  shadow_reverse(DELAY);  
  runnig_lights(DELAY);
  shadow(DELAY);
  stack(DELAY);
  /*
  int wait = DELAY;
  uint8_t c = 50;
  CRGB clr;
  for(byte clr = 0; clr < sizeof(colors)/sizeof(colors[0]); clr++){
    for(byte i = 0; i < NUM_LEDS; i++){
      leds[i] = colors[clr] / c;
      // leds[i].r = 64; //96
      // leds[i].g = 0; //64
      // leds[i].b = 0; //96
      FastLED.show();
      delay(wait);
    }
    
    // Now turn the LED off, then pause
    for(byte i = 0; i < NUM_LEDS; i++){ 
      leds[i] = CRGB::Black;
      FastLED.show();
      delay(wait);
    }
  }
  */ 
}
