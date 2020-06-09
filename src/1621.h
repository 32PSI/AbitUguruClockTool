#ifndef HEADER_FILE
#define HEADER_FILE
#define CS0   2  //Pin 2 as chip selection output
#define CS1  5  //Pin 5 second chip CS pin
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

bool SetCS(int CS, bool state);
void SendBit_1621(unsigned char sdata,unsigned char cnt);
bool SendCmd_1621(unsigned char command, int CS);
void Write_1621(unsigned char addr,unsigned char sdata,int CS);
void Init_1621(void);

#endif
