#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
                       // in which case, set this #define pin to -1!
#define TFT_DC     8

// For 1.44" and 1.8" TFT with ST7735 use
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
const int buttonPinLeft = 3;
const int buttonPinRight = 2;     // the number of the pushbutton pin
     // the number of the LED pin
// variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonStateLeft;             // the current reading from the input pin
int buttonStateRight;             // the current reading from the input pin
boolean lastButton = LOW;   // the previous reading from the input pin
boolean current = LOW;
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
float p = 3.1415926;
int currstate = 0;
int columnNum = 1;
long randNum;
int y1 = 0;
int scoreNum = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);//start up console
  Serial.print("Hello! ST77xx TFT Test");

  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  Serial.println("Initialized");

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);
randomSeed(analogRead(0));

pinMode(buttonPinLeft, INPUT);
pinMode(buttonPinRight, INPUT);
 tft.fillScreen(ST77XX_BLACK);
 randNum = random(1,4);
  String newscoreNum = String(scoreNum);
drawChar(60,130,newscoreNum,0xFFFF,2);
}

void loop() {
  // put your main code here, to run repeatedly:

 buttonStateLeft = debounceLeft(current);
 buttonStateRight = debounceRight(current);
if(randNum == 1){
    moveRect(25,y1,5,5,0xF800);
delay(10);
moveRect(25,y1,5,5,0x0000);
}
else if(randNum == 2){
    moveRect(60,y1,5,5,0xF800);
delay(10);
moveRect(60,y1,5,5,0x0000);
}
else if(randNum == 3){
  moveRect(98,y1,5,5,0xF800);
delay(10);
moveRect(98,y1,5,5,0x0000);
}
else{
  
}
if(columnNum == 0){
  columnNum = 1;
  //left bucket start
  drawLine(20,120,35,120,0x07E0);
  drawLine(10,105,20,120,0x07E0);
  drawLine(35,120,45,105,0x07E0);
  //left bucket end
  //block out middle bucket
  drawLine(55,120,70,120,0x0000);
  drawLine(45,105,55,120,0x0000);
  drawLine(70,120,80,105,0x0000);
  //block out right bucket
  drawLine(90,120,105,120,0x0000);
  drawLine(80,105,90,120,0x0000);
  drawLine(105,120,115,105,0x0000);
  //block out right bucket
}
else if(columnNum == 1){
  //left bucket start
  drawLine(20,120,35,120,0x07E0);
  drawLine(10,105,20,120,0x07E0);
  drawLine(35,120,45,105,0x07E0);
  //left bucket end
  //block out middle bucket
  drawLine(55,120,70,120,0x0000);
  drawLine(45,105,55,120,0x0000);
  drawLine(70,120,80,105,0x0000);
  //block out right bucket
  drawLine(90,120,105,120,0x0000);
  drawLine(80,105,90,120,0x0000);
  drawLine(105,120,115,105,0x0000);
  //block out right bucket
}
else if(columnNum == 2){
  //block out left bucket
  drawLine(20,120,35,120,0x0000);
  drawLine(10,105,20,120,0x0000);
  drawLine(35,120,45,105,0x0000);
  //block out left bucket
  //middle bucket start
  drawLine(55,120,70,120,0x07E0);
  drawLine(45,105,55,120,0x07E0);
  drawLine(70,120,80,105,0x07E0);
  //middle bucket end
  //block out right bucket
  drawLine(90,120,105,120,0x0000);
  drawLine(80,105,90,120,0x0000);
  drawLine(105,120,115,105,0x0000);
}
else if(columnNum == 3){
  //block out left bucket
  drawLine(20,120,35,120,0x0000);
  drawLine(10,105,20,120,0x0000);
  drawLine(35,120,45,105,0x0000);
  //block out left bucket
  //block out middle bucket
  drawLine(55,120,70,120,0x0000);
  drawLine(45,105,55,120,0x0000);
  drawLine(70,120,80,105,0x0000);
  //right bucket start
  drawLine(90,120,105,120,0x07E0);
  drawLine(80,105,90,120,0x07E0);
  drawLine(105,120,115,105,0x07E0);
  //right bucket end
}
else if(columnNum == 4){
  columnNum = 3;
  //block out left bucket
  drawLine(20,120,35,120,0x0000);
  drawLine(10,105,20,120,0x0000);
  drawLine(35,120,45,105,0x0000);
  //block out left bucket
  //block out middle bucket
  drawLine(55,120,70,120,0x0000);
  drawLine(45,105,55,120,0x0000);
  drawLine(70,120,80,105,0x0000);
  //right bucket start
  drawLine(90,120,105,120,0x07E0);
  drawLine(80,105,90,120,0x07E0);
  drawLine(105,120,115,105,0x07E0);
  //right bucket end
}

if(buttonStateLeft == HIGH){
  columnNum = columnNum - 1; 
}
else if(buttonStateRight == HIGH){
  columnNum = columnNum + 1;
}
else{
  
}
y1 = y1 + 2;
if((y1 > 120) && (randNum == 1) && (columnNum == 1)){
  y1 = 0;
  scoreNum = scoreNum + 1;
    fillRect(0,130,120,20,0x0000);
  String newscoreNum = String(scoreNum);
drawChar(60,130,newscoreNum,0xFFFF,2);
  randNum = random(1,4);
}
else if((y1 > 120) && (randNum == 2) && (columnNum == 2)){
  y1 = 0;
  scoreNum = scoreNum + 1;
    fillRect(0,130,120,20,0x0000);
  String newscoreNum = String(scoreNum);
drawChar(60,130,newscoreNum,0xFFFF,2);
  randNum = random(1,4);
}
else if((y1 > 120) && (randNum == 3) && (columnNum == 3)){
  y1 = 0;
  scoreNum = scoreNum + 1;
  fillRect(0,130,120,20,0x0000);
  String newscoreNum = String(scoreNum);
drawChar(60,130,newscoreNum,0xFFFF,2);
  randNum = random(1,4);
}
else if((y1 > 120) && (randNum == 1) && ((columnNum == 2) || (columnNum == 3))){
  y1 = 0;
  randNum = random(1,4);
}
else if((y1 > 120) && (randNum == 2) && ((columnNum == 1) || (columnNum == 3))){
  y1 = 0;
  randNum = random(1,4);
}
else if((y1 > 120) && (randNum == 3) && ((columnNum == 1) || (columnNum == 2))){
  y1 = 0;
  randNum = random(1,4);
}
else{

}

}

void drawChar(int x0, int y0, String c, uint16_t color, uint8_t size0){
  tft.setCursor(x0,y0);
  tft.setTextColor(color);
  tft.print(c);
  tft.setTextSize(size0);
}
void drawLine(int x0, int y0, int x1, int y1, int color){
  tft.drawLine(x0,y0,x1,y1,color);
}
void filltriangles(int x0, int y0, int x1, int y1, int x2, int y2, uint16_t color) {
  tft.fillTriangle(x0, y0, x1, y1, x2, y2,color);
  }
boolean debounceLeft(boolean last)
{
  boolean current = digitalRead(buttonPinLeft);
  if(last != current){
    delay(100);
    current = digitalRead(buttonPinLeft);
  }
  return current;
}
boolean debounceRight(boolean last)
{
  boolean current = digitalRead(buttonPinRight);
  if(last != current){
    delay(100);
    current = digitalRead(buttonPinRight);
  }
  return current;
}
void drawRect(int x0, int y0, int w, int h, uint16_t color){
    tft.drawRect(x0,y0,w,h,color);
}
  void fillRect(int x0, int y0, int w, int h, uint16_t color){
    tft.fillRect(x0,y0,w,h,color);
}
  void moveRect(int currX, int currY,int w,int h,uint16_t color){
    fillRect(currX,currY, w,h,color);
}

