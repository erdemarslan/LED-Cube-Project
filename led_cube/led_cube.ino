#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN    3
#define BUTTON 2


#define LED_COUNT 6

volatile int ledModu = 0;
volatile bool ledYandi = false;

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------



void setup() {

  Serial.begin(9600);
  pinMode(BUTTON, INPUT_PULLUP);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  attachInterrupt(digitalPinToInterrupt(BUTTON),mode, RISING);

  ledModu = 0;
}


void mode() {
  ledModu++;
  ledYandi = false;
  if(ledModu > 10) {
    ledModu = 0;
  }

  Serial.println(ledModu);
}

// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {

  if (ledModu == 0) {
    // Fill along the length of the strip in various colors...
    colorWipe(strip.Color(255,   0,   0), 50); // Red
    colorWipe(strip.Color(  0, 255,   0), 50); // Green
    colorWipe(strip.Color(  0,   0, 255), 50); // Blue
    colorWipe(strip.Color(  255,   255, 255), 50); // White
  }
  else if(ledModu == 1) {
    // Do a theater marquee effect in various colors...
    theaterChase(strip.Color(255, 255, 255), 50); // White, half brightness
    theaterChase(strip.Color(255,   0,   0), 50); // Red, half brightness
    theaterChase(strip.Color(  0,   0, 255), 50); // Blue, half brightness
    theaterChase(strip.Color(  0,   255, 0), 50); // Blue, half brightness
  }
  else if(ledModu == 2) {
    rainbow(10);
  }
  else if(ledModu == 3) {
    theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
  }
  else if(ledModu == 4) {
    // beyaz
    if(!ledYandi) {
      for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 255));
      }
      strip.show();
      ledYandi = true;
    }
  }
  else if(ledModu == 5) {
    // kırmızı
    if(!ledYandi) {
      for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
      }
      strip.show();
      ledYandi = true;
    }
  }
  else if(ledModu == 6) {
    // mavi
    if(!ledYandi) {
      for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 255));
      }
      strip.show();
      ledYandi = true;
    }
  }
  else if(ledModu == 7) {
    // yeşil
    if(!ledYandi) {
      for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0,   255, 0));
      }
      strip.show();
      ledYandi = true;
    }
  }
  else if(ledModu == 8) {
    // mor
    if(!ledYandi) {
      for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(190, 55, 240));
      }
      strip.show();
      ledYandi = true;
    }
  }
  else if(ledModu == 9) {
    // turuncu
    if(!ledYandi) {
      for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(240, 150, 55));
      }
      strip.show();
      ledYandi = true;
    }
  }
  else if(ledModu == 10) {
    // sarı
    if(!ledYandi) {
      for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(235, 240, 55));
      }
      strip.show();
      ledYandi = true;
    }
  }
}


void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    if(ledModu != 0) {
      break;
    }
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    if(ledModu != 1) {
      break;
    }
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      if(ledModu != 1) {
        break;
      }
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    if(ledModu != 2) {
      break;
    }
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      if(ledModu != 2) {
        break;
      }
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    if(ledModu != 3) {
      break;
    }
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      if(ledModu != 3) {
        break;
      }
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        if(ledModu != 3) {
          break;
        }
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
