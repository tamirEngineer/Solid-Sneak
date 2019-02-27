
#include "Triangle.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

//const int x1;
//const int y1;

#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
                       // in which case, set this #define pin to -1!
#define TFT_DC     8

// For 1.44" and 1.8" TFT with ST7735 use
Adafruit_ST7735 tff = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

Triangle::Triangle(){
	
}
void Triangle::makeTriangle(char Dir, uint16_t color, int x1, int y1){
switch(Dir){
      case 'L':
        tff.fillTriangle(x1,(y1 + 5),(x1 + 8),(y1 + 34),(x1 - 8),(y1 + 34), color);
        break;
      case 'R':
        tff.fillTriangle(x1,(y1 - 5),(x1 + 8),(y1 - 34),(x1 - 8),(y1 - 34), color);
        break;
      case 'T':
        tff.fillTriangle((x1 - 5), y1,(x1 - 34),(y1 + 8), (x1 - 34), (y1 - 8), color);
        break;
      case 'B':
        tff.fillTriangle((x1 + 5), y1,(x1 + 34),(y1 + 8), (x1 + 34), (y1 - 8), color);
        break;
      default:
        Serial.println("bad Triangle");
    }
}