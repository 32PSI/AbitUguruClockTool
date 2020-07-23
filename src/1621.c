#include <Arduino.h>
#include <stdbool.h>
#include <1621.h>

static struct CSList EnabledCS; 

struct CSList _getEnabledCS(void)
{
  struct CSList EnabledCS={0};
  #ifdef CS0
  EnabledCS.pickCS0=1;
  #endif
  #ifdef CS1
  EnabledCS.pickCS1=1;
  #endif
  #ifdef CS2
  EnabledCS.pickCS2=1;
  #endif
  #ifdef CS3
  EnabledCS.pickCS3=1;
  #endif
  #ifdef CS4
  EnabledCS.pickCS4=1;
  #endif
  #ifdef CS5
  EnabledCS.pickCS5=1;
  #endif
  #ifdef CS6
  EnabledCS.pickCS6=1;
  #endif
  #ifdef CS7
  EnabledCS.pickCS7=1;
  #endif
  #ifdef CS8
  EnabledCS.pickCS8=1;
  #endif
  #ifdef CS9
  EnabledCS.pickCS9=1;
  #endif
  return EnabledCS;
}


bool isCSListValid(struct CSList input){
  if(EnabledCS.pickCS0==false&&input.pickCS0==true){return 0;}
  if(EnabledCS.pickCS1==false&&input.pickCS1==true){return 0;}
  if(EnabledCS.pickCS2==false&&input.pickCS2==true){return 0;}
  if(EnabledCS.pickCS3==false&&input.pickCS3==true){return 0;}
  if(EnabledCS.pickCS4==false&&input.pickCS4==true){return 0;}
  if(EnabledCS.pickCS5==false&&input.pickCS5==true){return 0;}
  if(EnabledCS.pickCS6==false&&input.pickCS6==true){return 0;}
  if(EnabledCS.pickCS7==false&&input.pickCS7==true){return 0;}
  if(EnabledCS.pickCS8==false&&input.pickCS8==true){return 0;}
  if(EnabledCS.pickCS9==false&&input.pickCS9==true){return 0;}
  return 1;
}

bool SendCmd_1621(unsigned char command, int CS)      //sends command to specified 1621 controller, returns true if provided CS is valid, false if CS is invalid
{ 
  bool IsValidCS=SetCS(0,CS);
  if(IsValidCS==true)
  {
    SendByte_1621(0x80,4);
    SendByte_1621(command,8);
    SetCS(1,CS);
  }
 return IsValidCS;
}
bool multiSetCS(bool state, struct CSList value)
{
  if (value.pickCS0==1){SetCS(state,0);}
  if (value.pickCS1==1){SetCS(state,1);}
  if (value.pickCS2==1){SetCS(state,2);}
  if (value.pickCS3==1){SetCS(state,3);}
  if (value.pickCS4==1){SetCS(state,4);}
  if (value.pickCS5==1){SetCS(state,5);}
  if (value.pickCS6==1){SetCS(state,6);}
  if (value.pickCS7==1){SetCS(state,7);}
  if (value.pickCS8==1){SetCS(state,8);}
  if (value.pickCS9==1){SetCS(state,9);}
  return 1;
}
void _multiSendCMD1621(unsigned char command)
{
    SendByte_1621(0x80,4);
    SendByte_1621(command,8);
}

void SendByte_1621(unsigned char sdata,unsigned char cnt){  //sends a byte to 1621 controllers that have their CS set to 0
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
 
bool Write_1621(unsigned char addr,unsigned char sdata,int CS){ //Write data sdata into address addr on Chip CS
  bool IsValidCS=SetCS(0,CS);
  if(IsValidCS==true)
  {
    addr<<=2;
    SendByte_1621(0xa0,3);
    SendByte_1621(addr,6);
    SendByte_1621(sdata,8);
    SetCS(1,CS);
  }
  return IsValidCS;
}
void HT1621_all_off(unsigned char num)
{
  unsigned char i;
  unsigned char addr=0;
  for(i=0;i<num;i++)
  {
    Write_1621(addr,0x00,0);
    #ifdef CS1
    Write_1621(addr,0x00,1);
    #endif
    #ifdef CS2
    Write_1621(addr,0x00,2);
    #endif
    #ifdef CS3
    Write_1621(addr,0x00,3);
    #endif
    #ifdef CS4
    Write_1621(addr,0x00,4);
    #endif
    #ifdef CS5
    Write_1621(addr,0x00,5);
    #endif
    #ifdef CS6
    Write_1621(addr,0x00,6);
    #endif
    #ifdef CS7
    Write_1621(addr,0x00,7);
    #endif
    #ifdef CS8
    Write_1621(addr,0x00,8);
    #endif
    #ifdef CS9
    Write_1621(addr,0x00,9);
    #endif
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
    #ifdef CS1
    Write_1621(addr,0xff,1);
    #endif
    #ifdef CS2
    Write_1621(addr,0xff,2);
    #endif
    #ifdef CS3
    Write_1621(addr,0xff,3);
    #endif
    #ifdef CS4
    Write_1621(addr,0xff,4);
    #endif
    #ifdef CS5
    Write_1621(addr,0xff,5);
    #endif
    #ifdef CS6
    Write_1621(addr,0xff,6);
    #endif
    #ifdef CS7
    Write_1621(addr,0xff,7);
    #endif
    #ifdef CS8
    Write_1621(addr,0xff,8);
    #endif
    #ifdef CS9
    Write_1621(addr,0xff,9);
    #endif
    addr+=2;
  }
}
 
void Init_1621(void)
{ 
  EnabledCS=_getEnabledCS(); 
  pinMode(WR, OUTPUT); 
  pinMode(DATA, OUTPUT);
  pinMode(CS0,OUTPUT);
  SendCmd_1621(Sys_en,0);
  SendCmd_1621(RCosc,0);
  SendCmd_1621(ComMode,0);
  SendCmd_1621(LCD_on,0);
  SetCS(1,0);
  #ifdef CS1
  pinMode(CS1, OUTPUT);
  SendCmd_1621(Sys_en,1);
  SendCmd_1621(RCosc,1);
  SendCmd_1621(ComMode,1);
  SendCmd_1621(LCD_on,1);
  SetCS(1,1);
  #endif
  #ifdef CS2
  pinMode(CS2, OUTPUT);         //aditional pin definitions follow, only compiled if pins are defined
  SendCmd_1621(Sys_en,2);
  SendCmd_1621(RCosc,2);
  SendCmd_1621(ComMode,2);
  SendCmd_1621(LCD_on,2);
  SetCS(1,2);
  #endif
  #ifdef CS3
  pinMode(CS3, OUTPUT);
  SendCmd_1621(Sys_en,3);
  SendCmd_1621(RCosc,3);
  SendCmd_1621(ComMode,3);
  SendCmd_1621(LCD_on,3);
  SetCS(1,3);
  #endif
  #ifdef CS4
  pinMode(CS4, OUTPUT);
  SendCmd_1621(Sys_en,4);
  SendCmd_1621(RCosc,4);
  SendCmd_1621(ComMode,4);
  SendCmd_1621(LCD_on,4);
  SetCS(1,4);
  #endif
  #ifdef CS5
  pinMode(CS5, OUTPUT);
  SendCmd_1621(Sys_en,5);
  SendCmd_1621(RCosc,5);
  SendCmd_1621(ComMode,5);
  SendCmd_1621(LCD_on,5);
  SetCS(1,5);
  #endif
  #ifdef CS6
  pinMode(CS6, OUTPUT);
  SendCmd_1621(Sys_en,6);
  SendCmd_1621(RCosc,6);
  SendCmd_1621(ComMode,6);
  SendCmd_1621(LCD_on,6);
  SetCS(1,6);
  #endif
  #ifdef CS7
  pinMode(CS7, OUTPUT);
  SendCmd_1621(Sys_en,7);
  SendCmd_1621(RCosc,7);
  SendCmd_1621(ComMode,7);
  SendCmd_1621(LCD_on,7);
  SetCS(1,7);
  #endif
  #ifdef CS8
  pinMode(CS8, OUTPUT);
  SendCmd_1621(Sys_en,8);
  SendCmd_1621(RCosc,8);
  SendCmd_1621(ComMode,8);
  SendCmd_1621(LCD_on,8);
  SetCS(1,8);
  #endif
  #ifdef CS9
  pinMode(CS9, OUTPUT);
  SendCmd_1621(Sys_en,9);
  SendCmd_1621(RCosc,9);
  SendCmd_1621(ComMode,9);
  SendCmd_1621(LCD_on,9);
  SetCS(1,9);
  #endif
  DATAHigh;
  WRHigh;
  delay(50);
}
 
bool SetCS( bool state,int CS)      //sets CS state, if additional 1621's are added add an additional CS pin definition 
{                                   //DATA&WR pins are be shared, returns true if provided CS is correct
  switch (CS)
  {
  case 0:
   if(state==true){
     digitalWrite(CS0, HIGH);
   }else{
     digitalWrite(CS0, LOW);
   }
    break;
  #ifdef CS1
  case 1:
    if(state==true){
      digitalWrite(CS1, HIGH);
    }else{
      digitalWrite(CS1, LOW);
    }
    break;
  #endif
  #ifdef  CS2                 //aditional pin definitions follow
  case 2:
    if(state==true){
      digitalWrite(CS2, HIGH);
    }else{
      digitalWrite(CS2, LOW);
    }
    break;
  #endif
  #ifdef  CS3
  case 3:
    if(state==true){
      digitalWrite(CS3, HIGH);
    }else{
      digitalWrite(CS3, LOW);
    }
    break;
  #endif
  #ifdef  CS4
  case 4:
    if(state==true){
      digitalWrite(CS4, HIGH);
    }else{
      digitalWrite(CS4, LOW);
    }
    break;
  #endif
  #ifdef  CS5
  case 5:
    if(state==true){
      digitalWrite(CS5, HIGH);
    }else{
      digitalWrite(CS5, LOW);
    }
    break;
  #endif
  #ifdef  CS6
  case 6:
    if(state==true){
      digitalWrite(CS6, HIGH);
    }else{
      digitalWrite(CS6, LOW);
    }
    break;
  #endif
  #ifdef  CS7
  case 7:
    if(state==true){
      digitalWrite(CS7, HIGH);
    }else{
      digitalWrite(CS7, LOW);
    }
    break;
  #endif
  #ifdef  CS8
  case 8:
    if(state==true){
      digitalWrite(CS8, HIGH);
    }else{
      digitalWrite(CS8, LOW);
    }
    break;
  #endif
  #ifdef  CS9
  case 9:
    if(state==true){
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
