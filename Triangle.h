#ifndef Triangle_h
#define Triangle_h
#include <Arduino.h>


class Triangle{
  
  public:
  Triangle();
  void makeTriangle(char Dir, uint16_t color, int x1, int y1);
};
#endif