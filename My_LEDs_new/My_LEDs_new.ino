#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 30
#define DELAY 70

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 12
#define CLOCK_PIN 13
#define RIGHT 1
#define LEFT 2

// Define the array of leds
CRGB leds[NUM_LEDS];
CRGB colors[] = {CRGB::Red, CRGB::Blue, CRGB::OrangeRed, CRGB::LightSkyBlue, CRGB::Green, CRGB::DarkMagenta, CRGB::Gold, CRGB::Black};
#define num_clr sizeof(colors)/sizeof(colors[0])
int prevRndNum = 0;
int randNumber = 0;
uint8_t slice[] = {0, 1, 2, 3, 5, 10, 15}; 

void setup() 
{ 
      // Uncomment/edit one of the following lines for your leds arrangement.
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  	  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); //.setCorrection(TypicalSMD5050);
}


void one_by_one(CRGB fg_clr, CRGB bg_clr, uint8_t num_on, uint8_t dir, bool fill, uint16_t wait)
{
  uint8_t num = num_on - 1;  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = bg_clr;    
  }
  //FastLED.show();
  if (dir == RIGHT) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = fg_clr;
      FastLED.show();
      FastLED.delay(wait);
      if (i >= num) {
        leds[i - num] = bg_clr;
        FastLED.show();                         
      }        
    }
    for (int i = num; i > 0; i--) {      
      leds[NUM_LEDS - i] = bg_clr;
      FastLED.show();
      FastLED.delay(wait);        
    }
  } else if (dir == LEFT) {
      for (int i = NUM_LEDS - 1; i >= 0; i--) {
        leds[i] = fg_clr;
        FastLED.show();
        FastLED.delay(wait);
        if (i <= NUM_LEDS - 1 - num) {
          leds[i + num] = bg_clr;
          FastLED.show();                                        
        }
      }
      for (int i = num; i >= 0; i--) {               
        leds[i] = bg_clr;
        FastLED.show();       
        FastLED.delay(wait);          
      }
    }
}


void garmoshka(int wait) 
{  
  for (byte clr = 0; clr < num_clr; clr++) {
    for (byte i = 0; i < NUM_LEDS; i++) { 
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
      if (i == NUM_LEDS / 2 || i == 0 || i == NUM_LEDS - 1) {
        delay(wait + 10);
      }
      leds[i] = leds[NUM_LEDS - 1 - i] = CRGB::Black;
      FastLED.show();
    }
  } 
}

void stack(CRGB fg_clr, CRGB bg_clr, uint16_t wait)
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = bg_clr;    
  }
  for (int s = 0; s < NUM_LEDS; s++) {
    for (int i = 0; i < NUM_LEDS - s; i++) {
      leds[i] = fg_clr;
      FastLED.show();
      FastLED.delay(wait);
      if (i < NUM_LEDS - s - 1) {
        leds[i] = bg_clr;
        //FastLED.show();        
      }    
    }
  }
  FastLED.delay(wait);
  for (int s = NUM_LEDS; s >= 0; s--) {
    for (int i = NUM_LEDS - s; i >= 0 ; i--) {
      leds[i] = fg_clr;
      FastLED.show();
      FastLED.delay(wait);
      if (i < NUM_LEDS - s) {
        leds[i] = bg_clr;
        //FastLED.show();        
      }    
    }
  }  
}  

void slices(uint8_t num_on, uint8_t dir, bool offset, uint16_t wait)
{
  int offset_ = 0;
  for (int i = 0; i < 2; i++) {
    if (offset && num_on > 1) {
      offset_ = num_on - 1;
    }
    if (dir == LEFT) {
      for (int clr = 1; clr < num_clr; clr++) {
        for (int off = 0; off <= offset_; off++) {
          for (int led = 0;led < NUM_LEDS; led++) {
            leds[led] = colors[((led + off) / num_on + clr) % 7];
          }
          FastLED.show();
          FastLED.delay(wait);
        }    
      }
    } else if (dir == RIGHT) {
      for (int clr = num_clr - 1; clr > 0; clr--) { 
        for (int off = 0; off <= offset_; off++) {       
          for (int led = NUM_LEDS -1; led >= 0; led--) {
              leds[led] = colors[((led - off + num_on) / num_on + clr) % 7];
          }
          FastLED.show();
          FastLED.delay(wait);
        }
      }      
    }
  }
}

void loop() 
{   
  for (int k = num_clr; k > 0; k--) {
    //for (int n = 1; n <= 7; n++) {
      randomSeed(analogRead(0));
      do {
        randNumber=random(num_clr);
      } while (randNumber == prevRndNum || randNumber == k);                 
      //CRGB clr = colors[randNumber];
      //one_by_one(colors[randNumber], colors[prevRndNum], 30, LEFT, false, DELAY);
      //one_by_one(colors[randNumber], colors[prevRndNum], 30, LEFT, false, DELAY);
      //one_by_one(colors[randNumber], colors[k%8], randNumber+1, randNumber%2+1, false, DELAY);
      //one_by_one(colors[randNumber], colors[k%8], randNumber+1, prevRndNum%2+1, false, DELAY);
      //stack(colors[randNumber], colors[k], DELAY);
      prevRndNum = randNumber;
    //}
  }
  
  for (int i = 0; i < num_clr - 1; i++) {
    //one_by_one(colors[i], CRGB::Green, 1, RIGHT, true, DELAY);
    //one_by_one(colors[i], CRGB::DeepPink, 2, LEFT, false, DELAY);
  }
  
  for (int i = 0; i < 30; i++) {
    slices(i, LEFT, true, DELAY-i);
    slices(i, RIGHT, true, DELAY-i);
  }

  garmoshka(DELAY);  
  
  
  /*
  int wait = DELAY;
  uint8_t c = 50;
  */ 
}
