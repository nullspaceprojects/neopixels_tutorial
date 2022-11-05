#include <Adafruit_NeoPixel.h>


/********* LEDS NEO-PIXELS ************/
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, 6, NEO_GRB + NEO_KHZ800); //15 LEDS, 

//RUOTA RGB -> WheelPos=0 = strip.Color(255, 0, 0) ROSSO
//          -> WheelPos=40 = strip.Color(165, 90, 0) GIALLO
//          -> WheelPos=64 = strip.Color(63, 192, 0) VERDE
//          -> WheelPos=128 = strip.Color(0, 126, 129) CELESTE
//          -> WheelPos=225 = strip.Color(165, 0, 90) MAGENTA
//          -> WheelPos=255 = strip.Color(255, 0, 0) ROSSO
uint32_t Wheel(byte WheelPos) {
  //WheelPos da 0 a 255 [0 ; 2^8 -1]
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

uint32_t Wheel(uint16_t WheelPos) 
{
  //WheelPos da 0 a 65535 [0 ; 2^16 -1]
  return strip.ColorHSV(WheelPos,255,255);
}


void accensione_sequenziale(uint32_t c, uint16_t wait)
{
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
  //spegni tutti i leds
  strip.clear();
  strip.show();
  delay(wait);

}

void accensione_contemporanea_con_colori_diversi(uint16_t wait)
{

  for(uint16_t i=0; i<strip.numPixels(); i++) {
    //mappatura id-pixel [0-strip.numPixels()-1] in range [0-255] dello spazio dei colori RGB
    uint8_t rgb = (uint8_t)map(i, 0, strip.numPixels()-1, 0, 255);
    strip.setPixelColor(i, Wheel(rgb));
  }
  strip.show();
  delay(wait);
  //spegni tutti i leds
  strip.clear();
  strip.show();
}

void accensione_leds_per_id(uint16_t wait)
{
  //accendiamo solo 3 leds specifici
  //per scegliere il valore desiderato di RGB vedere: https://www.rapidtables.com/web/color/RGB_Color.html
  uint32_t color1 = strip.Color(0,0,255); //RED-GREEN-BLUE
  uint32_t color2 = strip.Color(0,255,0); //RED-GREEN-BLUE
  uint32_t color3 = strip.Color(255,0,0); //RED-GREEN-BLUE
  //gli id dei led partono da 0. id=0 -> primo led della catena
  int id1 = 3;
  int id2 = 18;
  int id3 = 22;

  strip.setPixelColor(id1, color1);
  strip.setPixelColor(id2, color2);
  strip.setPixelColor(id3, color3);

  strip.show();
  delay(wait);

  //accendiamo gli stessi leds ma cambiando il colore
  strip.setPixelColor(id1, color2);
  strip.setPixelColor(id2, color3);
  strip.setPixelColor(id3, color1);

  strip.show();
  delay(wait);

  //spegni tutti i leds
  strip.clear();
  strip.show();
}

void setup() {
  //SETUP LEDS NEOPIXELS
  strip.begin();
  strip.setBrightness(100); //[0-255]
  strip.clear(); // metti ad off tutti i leds
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {
  
  //ACCENSIONE DI SOLO 3 LEDS
  accensione_leds_per_id(5000);

  delay(2000);

  //ACCENSIONE SEQUENZIALE CON COLORE FISSO
  uint32_t color = strip.Color(0,0,255); //RED-GREEN-BLUE
  accensione_sequenziale(color, 200);

  delay(2000);

  //ACCENSIONE CONTEMPORANEA CON COLORI DIVERSI
  accensione_contemporanea_con_colori_diversi(10000);


}
