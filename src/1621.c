#include <Arduino.h>
#include <stdbool.h>
#include <1621.h>



bool SendCmd_1621(unsigned char command, int CS)
{ 
  SetCS(CS,0);
  SendBit_1621(0x80,4);
  SendBit_1621(command,8);
  SetCS(CS,1);
 return 1;
}

void SendBit_1621(unsigned char sdata,unsigned char cnt){
  unsigned char i;
  for(i=0;i<cnt;i++)
  {
    WRLow;
    if(sdata&0x80) DATAHigh;
    else DATALow;
    WRHigh;
    sdata<<=1;
  }
}
 
void Write_1621(unsigned char addr,unsigned char sdata,int CS){
  addr<<=2;
  SetCS(CS,0);
  SendBit_1621(0xa0,3);
  SendBit_1621(addr,6);
  SendBit_1621(sdata,8);
  SetCS(CS,1);
}
void HT1621_all_off(unsigned char num)
{
  unsigned char i;
  unsigned char addr=0;
  for(i=0;i<num;i++)
  {
    Write_1621(addr,0x00,0);
    Write_1621(addr,0x00,1);
    addr+=2;
  }
  
}
 
void HT1621_all_on(unsigned char num)
{
  unsigned char i;
  unsigned char addr=0;
  for(i=0;i<num;i++)
  {
    Write_1621(addr,0xff,0);
    Write_1621(addr,0xff,1);
    addr+=2;
  }
}
 
void Init_1621(void)
{ 
  pinMode(WR, OUTPUT); 
  pinMode(DATA, OUTPUT);
  pinMode(CS0,OUTPUT);
  SendCmd_1621(Sys_en,0);
  SendCmd_1621(RCosc,0);
  SendCmd_1621(ComMode,0);
  SendCmd_1621(LCD_on,0);
  #ifdef CS1
  pinMode(CS1, OUTPUT);
  SendCmd_1621(Sys_en,1);
  SendCmd_1621(RCosc,1);
  SendCmd_1621(ComMode,1);
  SendCmd_1621(LCD_on,1);
  #endif
  #ifdef CS2
  pinMode(CS2, OUTPUT);         //aditional pin definitions follow, only compiled if pins are defined
  SendCmd_1621(Sys_en,2);
  SendCmd_1621(RCosc,2);
  SendCmd_1621(ComMode,2);
  SendCmd_1621(LCD_on,2);
  #endif
  #ifdef CS3
  pinMode(CS3, OUTPUT);
  SendCmd_1621(Sys_en,3);
  SendCmd_1621(RCosc,3);
  SendCmd_1621(ComMode,3);
  SendCmd_1621(LCD_on,3);
  #endif
  #ifdef CS4
  pinMode(CS4, OUTPUT);
  SendCmd_1621(Sys_en,4);
  SendCmd_1621(RCosc,4);
  SendCmd_1621(ComMode,4);
  SendCmd_1621(LCD_on,4);
  #endif
  #ifdef CS5
  pinMode(CS5, OUTPUT);
  SendCmd_1621(Sys_en,5);
  SendCmd_1621(RCosc,5);
  SendCmd_1621(ComMode,5);
  SendCmd_1621(LCD_on,5);
  #endif
  #ifdef CS6
  pinMode(CS6, OUTPUT);
  SendCmd_1621(Sys_en,6);
  SendCmd_1621(RCosc,6);
  SendCmd_1621(ComMode,6);
  SendCmd_1621(LCD_on,6);
  #endif
  #ifdef CS7
  pinMode(CS7, OUTPUT);
  SendCmd_1621(Sys_en,7);
  SendCmd_1621(RCosc,7);
  SendCmd_1621(ComMode,7);
  SendCmd_1621(LCD_on,7);
  #endif
  #ifdef CS8
  pinMode(CS8, OUTPUT);
  SendCmd_1621(Sys_en,8);
  SendCmd_1621(RCosc,8);
  SendCmd_1621(ComMode,8);
  SendCmd_1621(LCD_on,8);
  #endif
  #ifdef CS9
  pinMode(CS9, OUTPUT);
  SendCmd_1621(Sys_en,9);
  SendCmd_1621(RCosc,9);
  SendCmd_1621(ComMode,9);
  SendCmd_1621(LCD_on,9);
  #endif
}
 
bool SetCS(int CS, bool state)      //sets CS state, if additional 1621's are added add an additional CS pin definition 
{                                   //DATA&WR pins can be shared, returns true if provided CS is correct
  switch (CS)
  {
  case 0:
   if(state){
     digitalWrite(CS0, HIGH);
   }else{
     digitalWrite(CS0, LOW);
   }
    break;
  #ifdef CS1
  case 1:
    if(state){
      digitalWrite(CS1, HIGH);
    }else{
      digitalWrite(CS1, LOW);
    }
    break;
  #endif
  #ifdef  CS2                 //aditional pin definitions follow, only compiled if pins are defined
  case 2:
    if(state){
      digitalWrite(CS2, HIGH);
    }else{
      digitalWrite(CS2, LOW);
    }
    break;
  #endif
  #ifdef  CS3
  case 3:
    if(state){
      digitalWrite(CS3, HIGH);
    }else{
      digitalWrite(CS3, LOW);
    }
    break;
  #endif
  #ifdef  CS4
  case 4:
    if(state){
      digitalWrite(CS4, HIGH);
    }else{
      digitalWrite(CS4, LOW);
    }
    break;
  #endif
  #ifdef  CS5
  case 4:
    if(state){
      digitalWrite(CS5, HIGH);
    }else{
      digitalWrite(CS5, LOW);
    }
    break;
  #endif
  #ifdef  CS6
  case 4:
    if(state){
      digitalWrite(CS6, HIGH);
    }else{
      digitalWrite(CS6, LOW);
    }
    break;
  #endif
  #ifdef  CS7
  case 4:
    if(state){
      digitalWrite(CS7, HIGH);
    }else{
      digitalWrite(CS7, LOW);
    }
    break;
  #endif
  #ifdef  CS8
  case 4:
    if(state){
      digitalWrite(CS8, HIGH);
    }else{
      digitalWrite(CS8, LOW);
    }
    break;
  #endif
  #ifdef  CS9
  case 4:
    if(state){
      digitalWrite(CS9, HIGH);
    }else{
      digitalWrite(CS9, LOW);
    }
    break;
  #endif
  default:
    return 0;
  }
  return 1;
}
