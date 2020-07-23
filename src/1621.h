#ifndef HEADER_FILE_1621
#define HEADER_FILE_1621
#define CS0   2  //Pin 2 as chip select 0 output
#define CS1  5  //Pin 5 as chip select 1 output
#define WR   3  //Pin 3 as read clock output
#define DATA 4  //Pin 4 as Serial data output


#define WRHigh        digitalWrite(WR, HIGH) 
#define WRLow        digitalWrite(WR, LOW)
#define DATAHigh      digitalWrite(DATA, HIGH) 
#define DATALow      digitalWrite(DATA, LOW)
 
#define sbi(x, y)  (x |= (1 << y))  
#define cbi(x, y)  (x &= ~(1 <<y ))      

 
#define  ComMode    0x52  
#define  RCosc      0x30  
#define  LCD_on     0x06 
#define  LCD_off    0x04 
#define  Sys_en     0x02 
#define  CTRl_cmd   0x80
#define  Data_cmd   0xa0 

bool SetCS( bool state,int CS);
void SendByte_1621(unsigned char sdata,unsigned char cnt);
bool SendCmd_1621(unsigned char command, int CS);
bool Write_1621(unsigned char addr,unsigned char sdata,int CS);
void Init_1621(void);
struct CSList _getEnabledCS(void);

struct CSList {
  bool pickCS0;
  bool pickCS1;
  bool pickCS2;
  bool pickCS3;
  bool pickCS4;
  bool pickCS5;
  bool pickCS6;
  bool pickCS7;
  bool pickCS8;
  bool pickCS9;
};

#endif
