#include <Adafruit_NeoPixel.h>

// Sketch is based off the NeoPixel example sketch "strandtest"

#define PIN 2

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Wipe various colours multiple times
  for (uint16_t i=0; i< 4; i++) {
    colorWipe(strip.Color(255, 0, 0), 75); // Red
    colorWipe(Wheel((146) & 255), 75);  // Purple
    colorWipe(strip.Color(0, 255, 0), 75); // Green
    colorWipe(strip.Color(255, 255, 255), 75); // White
    colorWipe(strip.Color(0, 0, 255), 75); // Blue
  }
  
  // Alternate between 2 red and 2 green and shift them along.
  unsigned short pattern = 0b1100110011001100;
  
  // Spread pattern along the strand before the shifting
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      if(pattern&(1 << i)) {
        strip.setPixelColor(i, strip.Color(255, 0, 0)); // Red if 1
      }
      else {
        strip.setPixelColor(i, strip.Color(0, 255, 0)); // Green if 0
      }
      strip.show();
      delay(100);
  }
  
  for (uint16_t i=0; i<20; i++) { // shift it 20 times!
    if ((pattern&0x01)^((pattern&0x02)>>1)) {
      pattern = (pattern&0x01) | (pattern << 1);
    } else {
      pattern = (!(pattern&0x01)) | (pattern << 1);
    }
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      if(pattern&(1 << i)) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
      }
      else {
        strip.setPixelColor(i, strip.Color(0, 255, 0));
      }
    }
    strip.show();
    delay(500);
  }
  
  // Spread the rainbow colour along the strand before cycling
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels())) & 255));
      strip.show();
      delay(100);
  }
  rainbowCycle(20);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

