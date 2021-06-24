#ifndef GLCD_H
#define GLCD_H
#include <Arduino.h>
#define GLCD_displayON 0x3e
#define GLCD_Xaddress 0xb8
#define GLCD_Yaddress 0x40
#define GLCD_starline 0xc0

class GLCD
{
  public:
  GLCD(int bl,int di, int rw, int e, int res, int cs1, int cs2,
  int db0, int db1, int db2, int db3,
  int db4, int db5, int db6, int db7);
  void enable();
  void setside(int side);
  void setDisplay(uint8_t on);
  void setY(uint8_t col);
  void setX(uint8_t line);
  void writeData(uint8_t data);
  void init();
  void gotoXY(uint8_t line,uint8_t col);
  void clr();
  void printbmp(uint8_t *data);
  void setData();
  void putChar(uint8_t line, uint8_t col, uint16_t chr);
  void printChar(uint8_t line, uint8_t col, char* str);
  void backLight( bool onOff ) { digitalWrite(bl_pin,onOff?HIGH:LOW); }
  
  char font7x8[679]={
   0,   0,   0,   0,   0,   0,   0,
   0,   0,  95,  95,   0,   0,   0,
   0,   7,   7,   0,   7,   7,   0, 
   20, 127, 127,  20, 127, 127,  20, 
   36,  46, 107, 107,  58,  18,   0, 
   70, 102,  48,  24,  12, 102,  98,
   48, 122,  79,  93,  55, 122,  72,
   4,   7,   3,   0,   0,   0,   0, 
   0,  28,  62,  99,  65,   0,   0, 
   0,  65,  99,  62,  28,   0,   0, 
   8,  42,  62,  28,  28,  62,  42, 
   8,   8,  62,  62,   8,   8,   0,
   0, 128, 224,  96,   0,   0,   0, 
   8,   8,   8,   8,   8,   8,   0, 
   0,   0,  96,  96,   0,   0,   0, 
  96,  48,  24,  12,   6,   3,   1, 
  62, 127, 113,  89,  77, 127,  62, 
  64,  66, 127, 127,  64,  64,   0, 
  98, 115,  89,  73, 111, 102,   0, 
  34,  99,  73,  73, 127,  54,   0, 
  24,  28,  22,  83, 127, 127,  80, 
  39, 103,  69,  69, 125,  57,   0, 
  60, 126,  75,  73, 121,  48,   0, 
   3,   3, 113, 121,  15,   7,   0,
  54, 127,  73,  73, 127,  54,   0, 
   6,  79,  73, 105,  63,  30,   0, 
   0,   0, 102, 102,   0,   0,   0, 
   0, 128, 230, 102,   0,   0,   0, 
   8,  28,  54,  99,  65,   0,   0, 
  36,  36,  36,  36,  36,  36,   0, 
   0,  65,  99,  54,  28,   8,   0, 
   2,   3,  81,  89,  15,   6,   0, 
  62, 127,  65,  93,  93,  31,  30, 
  124, 126,  19,  19, 126, 124,   0, 
  65, 127, 127,  73,  73, 127,  54, 
  28,  62,  99,  65,  65,  99,  34, 
  65, 127, 127,  65,  99,  62,  28, 
  65, 127, 127,  73,  93,  65,  99, 
  65, 127, 127,  73,  29,   1,   3,
  28,  62,  99,  65,  81, 115, 114,
  127, 127,   8,   8, 127, 127,   0,
   0,  65, 127, 127,  65,   0,   0, 
  48, 112,  64,  65, 127,  63,   1,
  65, 127, 127,   8,  28, 119,  99, 
  65, 127, 127,  65,  64,  96, 112,
  127, 127,  14,  28,  14, 127, 127,
  127, 127,   6,  12,  24, 127, 127,
  28,  62,  99,  65,  99,  62,  28, 
  65, 127, 127,  73,   9,  15,   6, 
  30,  63,  33, 113, 127,  94,   0, 
  65, 127, 127,   9,  25, 127, 102,
  38, 111,  77,  89, 115,  50,   0, 
   3,  65, 127, 127,  65,   3,   0,
  127, 127,  64,  64, 127, 127,   0, 
  31,  63,  96,  96,  63,  31,   0, 
  127, 127,  48,  24,  48, 127, 127, 
  67, 103,  60,  24,  60, 103,  67, 
   7,  79, 120, 120,  79,   7,   0, 
  71,  99, 113,  89,  77, 103, 115, 
   0, 127, 127,  65,  65,   0,   0, 
   1,   3,   6,  12,  24,  48,  96, 
   0,  65,  65, 127, 127,   0,   0, 
   8,  12,   6,   3,   6,  12,   8, 
  128, 128, 128, 128, 128, 128, 128, 
   0,   0,   3,   7,   4,   0,   0, 
  32, 116,  84,  84,  60, 120,  64, 
  65, 127,  63,  72,  72, 120,  48, 
  56, 124,  68,  68, 108,  40,   0, 
  48, 120,  72,  73,  63, 127,  64, 
  56, 124,  84,  84,  92,  24,   0, 
  72, 126, 127,  73,   3,   2,   0,
  56, 188, 164, 164, 252, 120,   0, 
  65, 127, 127,   8,   4, 124, 120, 
   0,  68, 125, 125,  64,   0,   0, 
  96, 224, 128, 128, 253, 125,   0, 
  65, 127, 127,  16,  56, 108,  68, 
   0,  65, 127, 127,  64,   0,   0, 
  120, 124,  28,  56,  28, 124, 120, 
  124, 124,   4,   4, 124, 120,   0, 
  56, 124,  68,  68, 124,  56,   0, 
  0, 252, 252, 164,  36,  60,  24, 
  24,  60,  36, 164, 248, 252, 132, 
  68, 124, 120,  76,   4,  28,  24, 
  72,  92,  84,  84, 116,  36,   0, 
   0,   4,  62, 127,  68,  36,   0, 
  60, 124,  64,  64,  60, 124,  64, 
  28,  60,  96,  96,  60,  28,   0, 
  60, 124, 112,  56, 112, 124,  60, 
  68, 108,  56,  16,  56, 108,  68, 
  60, 188, 160, 160, 252, 124,   0, 
  76, 100, 116,  92,  76, 100,   0, 
   8,   8,  62, 119,  65,  65,   0, 
   0,   0,   0, 127, 127,   0,   0, 
  65,  65, 119,  62,   8,   8,   0, 
   2,   3,   1,   3,   2,   3,   1, 
  255, 129,  129,  129,  129, 129, 255,
  14, 159, 145, 177, 251,  74,   0};

  private:
  int bl_pin;
  int di_pin;
  int rw_pin;
  int e_pin;
  int res_pin;
  int cs1_pin;
  int cs2_pin;
  
  uint8_t _data_pins[8];
  uint8_t _data;
  int di;
  int rw;
  int side;
  

};

#endif
