

#include <Triangle.h>
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


 int ledPin = 13;
 int joyPin1 = 0;                 // slider variable connecetd to analog pin 0
 int joyPin2 = 1;                 // slider variable connecetd to analog pin 1
 int value1 = 0;                  // variable to read the value from the analog pin 0
 int value2 = 0;                  // variable to read the value from the analog pin 1
int c1randomNum1 = random(1,4);
int c2randomNum1 = random(1,4);
int c3randomNum1 = random(1,4);
void setup() {
  // put your setup code here, to run once:
pinMode(ledPin, OUTPUT);              // initializes digital pins 0 to 7 as outputs
tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  Serial.println("Initialized");

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);//MAKE THE SCREEN BLACK
  
 Serial.begin(9600);//BEGIN SERIAL OUTPUT


 fillCircle(15, 120, 5, 0x001F);//COP 1

 fillCircle(115, 60, 5, 0x001F);//COP 2

 fillCircle(55, 10, 5, 0x001F);//COP3
    
  //cop_1(randomNum1,1);//RANDOM FLASHLIGHT
}

int triangle_count1 = 0;//START TRIANGLE COUNT
int triangle_count2 = 0;//START TRIANGLE COUNT
int triangle_count3 = 0;//START TRIANGLE COUNT
int X_value = 115;
int Y_value = 155;
int c1randomNum2;
int c2randomNum2;
int c3randomNum2;
void loop() {

  //RANDOM COP-1 LOOKING
if(triangle_count1 > 85){
  c1randomNum1 = random(1,4);
  while(c1randomNum1 == c1randomNum2){
    c1randomNum1 = random(1,4);
  }
  cop_1(c1randomNum1,c1randomNum2);
  triangle_count1 = 0;
  c1randomNum2 = c1randomNum1;
}
if(triangle_count2 > 70){
  c2randomNum1 = random(1,4);
    while(c2randomNum1 == c2randomNum2){
    c2randomNum1 = random(1,4);
  }
  cop_2(c2randomNum1,c2randomNum2);
  triangle_count2 = 0;
  c2randomNum2 = c2randomNum1;
}
if(triangle_count3 > 60){
  c3randomNum1 = random(1,4);
    while(c3randomNum1 == c3randomNum2){
    c3randomNum1 = random(1,4);
  }
  cop_3(c3randomNum1,c3randomNum2);
  triangle_count3 = 0;
  c3randomNum2 = c3randomNum1;
}
  triangle_count1 = triangle_count1 + 1;
  triangle_count2 = triangle_count2 + 1;
  triangle_count3 = triangle_count3 + 1;
  //START MOVEMENT CHECK OF BLOCK
int components[1];
components[0] = treatValue(analogRead(joyPin1));//CHECK THUMBSTICK X VALUE
components[1] = treatValue(analogRead(joyPin2));//CHECK THUMBSTICK Y VALUE
int x = components[0];
int y = components[1];
Serial.print(analogRead(joyPin1));
Serial.print(" ");
Serial.println(analogRead(joyPin2));
Serial.print(x);
Serial.print(" ");
Serial.println(y);
Moveblock(y,-x, X_value, Y_value);//MOVE BLOCK (INVERT X AND Y VALUES)
//END MOVEMENT CHECK OF BLOCK

//ADJUST NEW LOCATION VALUES
X_value = X_value + y;
Y_value = Y_value + -x;
Serial.print(X_value);
Serial.print(" ");
Serial.println(Y_value);
//CHECK IF BLOCK IS OFF SCREEN
 if(X_value + 2 > 119){
  X_value = 119;
 }
 if(X_value < 0){
  X_value = 1;
 }
 if(( Y_value + 2)> 160){
  Y_value = Y_value;
 }
 if(Y_value < 0){
    tft.fillScreen(ST77XX_BLACK);//MAKE THE SCREEN BLACK
  while(1){

  printText(60, 40,0xFFFF,"YOU WIN!!");
 }
 }
 //END CHECK IF BLOCK IS OFF SCREEN

 //CHECK COLLISIONS FOR COP 1

 //
  //LEFT

 if(c1randomNum1 == 1){
  int i = 0;
  
  for(int i = 0;i<35;i++){
    if( (Y_value > (17/4) * i + 63) && (X_value == i) && (Y_value > 126)){
      tft.fillScreen(ST77XX_RED);
    }
  }
 }
  //DOWN
 if(c1randomNum1 == 2){
  int k;
  
  for( k = 21; k<56;k++){
    int Y_left_check = ((4*k)/17) + 115;
    int Y_right_check = ((-4*k)/17) + 125;
    if( (Y_value <= Y_left_check) && ((Y_value +5)  >= Y_right_check) && (X_value < 55 )){
      tft.fillScreen(ST77XX_RED);
    }
    else{
      
    }
  }
 }
  //RIGHT
  if(c1randomNum1 == 3){
    int j;
    for( j = 15; j<24;j++){
      int Y_top_check = ( (-17*j)/4) + 178;
      if( (Y_value <= Y_top_check) && ((Y_value + 5) >= 80) && (X_value <= 23)){
        tft.fillScreen(ST77XX_RED);
      }
    }
  }

 //END CHECK COLLISIONS COP 1

}// END LOOP


  void fillRect(int x0, int y0, int w, int h, uint16_t color){//FILL RECTANGLE SHAPE
    tft.fillRect(x0,y0,w,h,color);
}
  void moveRect(int currX, int currY,int w,int h,uint16_t color){// MOVE RECTANGLE
    fillRect(currX,currY, w,h,color);
}

  int treatValue(int data) {//THUMBSTICK ELECTRICAL SIGNAL INTERPRETER
    return (data * 9 / 1024) - 4  ;
}
  void Moveblock(int Xcomp, int Ycomp, int XCurrVal, int YCurrVal){//MOVE ANIMATION
    if(Xcomp != 0 || Ycomp != 0){
      moveRect(XCurrVal,YCurrVal,5,5, 0xF800);//BLOCK AT CURRENT VALUE
      moveRect((XCurrVal + Xcomp),(YCurrVal + Ycomp),5,5, 0xF800);//ADD BLOCK TO NEW SPACE
      delay(5);
      moveRect(XCurrVal,YCurrVal,5,5, 0x0000);//BLACK OUT BLOCK FROM PREVIOUS SPACE
      moveRect((XCurrVal + Xcomp),(YCurrVal + Ycomp),5,5, 0xF800);//RE-UPDATE NEW BLOCK SPACE
      delay(75);
    }
}

    void setCursor(uint16_t x0, uint16_t y0){
      tft.setCursor(x0,y0);
    }
    void setTextColor(uint16_t color){
      tft.setTextColor(color);
    }
    void print(String text){
      tft.print(text);
    }

void printText(uint16_t x0, uint16_t y0, uint16_t color, String text){
      setCursor(x0, y0);
      setTextColor(color);
      print(text);
}
  void fillCircle(int x0, int y0, int r, int color){//MAKE A CIRCLE
  tft.fillCircle(x0,y0,r,color);
  }
void fillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){//MAKE A TRIANGLE
  tft.fillTriangle(x0,y0,x1,y1,x2,y2,color);
}

  Triangle cop1_Triangle_Left = Triangle();
  Triangle cop1_Triangle_Bottom = Triangle();
  Triangle cop1_Triangle_Right = Triangle();
void cop_1(int rand1, int randOld){//FLASHLIGHT MOVEMENT CHECK

  if(randOld == 1){//IF PREVIOUS FLASHLIGHT IS 1
    cop1_Triangle_Left.makeTriangle('L',0x0000,15,120);
  }
  else if(randOld == 2){
    cop1_Triangle_Bottom.makeTriangle('B',0x0000,15,120);
  }
  else if(randOld == 3){
    cop1_Triangle_Right.makeTriangle('R',0x0000,15,120);
  }
  if(rand1 == 1){//IF CURRENT FLASHLIGHT IS 1
    cop1_Triangle_Left.makeTriangle('L',0xFFFF,15,120);
    delay(300);//DELAY 300 MILLISECONDS

  }
  else if(rand1 == 2){
    cop1_Triangle_Bottom.makeTriangle('B',0xFFFF,15,120);
    delay(300);

  }
  else if(rand1 == 3){
    cop1_Triangle_Right.makeTriangle('R',0xFFFF,15,120);
    delay(300);

  }
}

  Triangle cop2_Triangle_Left = Triangle();
  Triangle cop2_Triangle_Top = Triangle();
  Triangle cop2_Triangle_Right = Triangle();
void cop_2(int rand1, int randOld){//FLASHLIGHT MOVEMENT CHECK

  if(randOld == 1){//IF PREVIOUS FLASHLIGHT IS 1
    cop2_Triangle_Left.makeTriangle('L',0x0000,115, 60);
  }
  else if(randOld == 2){
    cop2_Triangle_Top.makeTriangle('T',0x0000,115, 60);
  }
  else if(randOld == 3){
    cop2_Triangle_Right.makeTriangle('R',0x0000,115, 60);
  }
  if(rand1 == 1){//IF CURRENT FLASHLIGHT IS 1
    cop2_Triangle_Left.makeTriangle('L',0xFFFF,115, 60);
    delay(300);//DELAY 300 MILLISECONDS
  }
  else if(rand1 == 2){
    cop2_Triangle_Top.makeTriangle('T',0xFFFF,115, 60);
    delay(300);
  }
  else if(rand1 == 3){
    cop2_Triangle_Right.makeTriangle('R',0xFFFF,115, 60);
    delay(300);
  }
}

  Triangle cop3_Triangle_Top = Triangle();
  Triangle cop3_Triangle_Left = Triangle();
  Triangle cop3_Triangle_Bottom = Triangle();
void cop_3(int rand1, int randOld){//FLASHLIGHT MOVEMENT CHECK

  if(randOld == 1){//IF PREVIOUS FLASHLIGHT IS 1
    cop3_Triangle_Top.makeTriangle('T',0x0000,55, 10);
  }
  else if(randOld == 2){
    cop3_Triangle_Left.makeTriangle('L',0x0000,55, 10);
  }
  else if(randOld == 3){
    cop3_Triangle_Bottom.makeTriangle('B',0x0000,55, 10);
  }
  if(rand1 == 1){//IF CURRENT FLASHLIGHT IS 1
    cop3_Triangle_Top.makeTriangle('T',0xFFFF,55, 10);
    delay(200);//DELAY 300 MILLISECONDS
  }
  else if(rand1 == 2){
    cop3_Triangle_Left.makeTriangle('L',0xFFFF,55, 10);
    delay(200);
  }
  else if(rand1 == 3){
    cop3_Triangle_Bottom.makeTriangle('B',0xFFFF,55, 10);
    delay(200);
  }
}
