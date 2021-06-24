
#include <GLCD.h>

GLCD::GLCD(int bl_pin,int di_pin,  int rw_pin,  int e_pin, int res_pin,
int cs1_pin, int cs2_pin, int db0, int db1, int db2, int db3, int db4, int db5,
int db6, int db7)
{
  this->bl_pin = bl_pin;
  this->di_pin = di_pin;
  this->rw_pin = rw_pin;
  this->e_pin  = e_pin;
  this->res_pin = res_pin;
  this->cs1_pin = cs1_pin;
  this->cs2_pin = cs2_pin;
  _data_pins[0] = db0;
  _data_pins[1] = db1;
  _data_pins[2] = db2;
  _data_pins[3] = db3;
  _data_pins[4] = db4;
  _data_pins[5] = db5;
  _data_pins[6] = db6;
  _data_pins[7] = db7;
  pinMode(bl_pin,  OUTPUT);
  pinMode(di_pin,  OUTPUT);
  pinMode(rw_pin,  OUTPUT);
  pinMode(e_pin,   OUTPUT);
  pinMode(res_pin, OUTPUT);
  pinMode(cs1_pin, OUTPUT);
  pinMode(cs2_pin, OUTPUT);
  for(int i = 0; i < 8; i++){
    pinMode(_data_pins[i], OUTPUT);
    digitalWrite(_data_pins[i], HIGH);
  }
  digitalWrite(bl_pin,   LOW);
  digitalWrite(e_pin,    LOW);
  digitalWrite(di_pin,   LOW);
  digitalWrite(rw_pin,   LOW);
  digitalWrite(res_pin,  LOW);
  digitalWrite(cs1_pin,  LOW);
  digitalWrite(cs2_pin,  LOW);
}
void GLCD::enable()
{
  
  setData();
  digitalWrite(e_pin,HIGH);
  digitalWrite(e_pin,LOW);
}

void GLCD::setside(int side )
{
  if(side==0)
  {
    digitalWrite(cs1_pin,HIGH);
    digitalWrite(cs2_pin,LOW);
  }
  else
  {
    digitalWrite(cs1_pin,LOW);
    digitalWrite(cs2_pin,HIGH);
  }
}

void GLCD::setDisplay(uint8_t on)
{
  digitalWrite(di_pin,LOW);
  digitalWrite(rw_pin,LOW);
  _data=GLCD_displayON|on;
  enable();
}

void GLCD::setY(uint8_t col)
{
  digitalWrite(di_pin,LOW);
  digitalWrite(rw_pin,LOW);
  _data=GLCD_Yaddress|col;
  enable();
}

void GLCD::setX(uint8_t line)
{
  digitalWrite(di_pin,LOW);
  digitalWrite(rw_pin,LOW);
  _data=GLCD_Xaddress|line;
  enable();
}

void GLCD::writeData(uint8_t data)
{
  digitalWrite(di_pin,HIGH);
  digitalWrite(rw_pin,LOW);
  _data=data;
  enable();
}

void GLCD::setData()
{
 for(int i = 0; i < 8; i++){
    digitalWrite(_data_pins[i], (_data>>i)&1);
  }
}

void GLCD::init()
{
  setside(0);
  setDisplay(1);
  setY(0);
  setX(0);

  setside(1);
  setDisplay(1);
  setY(0);
  setX(0);
}

void GLCD::gotoXY(uint8_t line,uint8_t col)
{
  uint8_t side;
  side=col/64;
  setside(side);
  if(side==1){col=col-64;}
  setY(col);
  setX(line);
}

void GLCD::clr()
{
  uint8_t line,col,side;
  for(side=0;side<8;side++){
   setside(side);
    for(line=0;line<8;line++){
    setX(line);
       for(col=0;col<64;col++){
       setDisplay(1);
       setY(col);
       writeData(0x00);
    }
  }
 }
}

void GLCD::printbmp(uint8_t *data)
{
  uint8_t line,col;
  uint16_t i;
  for(line=0;line<8;line++){
    gotoXY(line,0);
    for(col=0;col<64;col++){
      i=128*line+col;
      writeData(data[i]);
      }
    }
   for(line=0;line<8;line++){
    gotoXY(line,64);
    for(col=64;col<128;col++){
      i=128*line+col;
      writeData(data[i]);
    }
   }
}

void GLCD::putChar(uint8_t line, uint8_t col, uint16_t chr)
{
  uint16_t i;
  if ((col>57) && (col<64)){
    gotoXY(line, col); 
    for(i=0;i<64-col;i++)             
      writeData(font7x8[((chr - 32) * 7) + i]);        
    gotoXY(line, 64); 
    for(i=64-col;i<7;i++)                         
      writeData(font7x8[((chr - 32) * 7) + i]);        
  }
  else{
    gotoXY(line, col);
    for(i=0;i<7;i++)             
      writeData(font7x8[((chr - 32) * 7) + i]);
        
  }
}

void GLCD::printChar(uint8_t line, uint8_t col, char* str)
{
  uint8_t i, x;
  x=col;
  for (i=0; str[i]!=0; i++)
  {
    if (x>=128)
    {
      col=0;
      x=col;
      line++;
    }
    putChar(line, x , str[i]);  
    x+=8;
  }
}
