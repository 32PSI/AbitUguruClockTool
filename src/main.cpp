#include <Arduino.h>
#include "1621.h"
#include "1621.c"

//defiing chars
/* 
Pins on device:
Pin 1 = cs1
Pin 2 = data
Pin 4 = WR
Pin 5 = cs2
*/
struct mem1620 {
  unsigned int first[16];
  unsigned int second[16];
};
void setup() {
  struct mem1620 mem={0,0};
  mem.first[0]=0b00000000; // 4th digit rpm //ul,mid,dl,VGA,u,ur,dr,d            //    u
  mem.first[1]=0b00000000; // 3rd digit rpm //ul,mid,dl,NB,u,ur,dr,d             //    _  
  mem.first[2]=0b00000000; // 1st digit rpm //u,ur,dr,d,ul,m,dl,CPU            // ul  |_| ur
  mem.first[3]=0b00000000; // 2nd digit rpm //u,ur,dr,d,ul,m,dl,SYS            // dl  |_| dr
  mem.first[4]=0b00000000; // down left clock 1st//ul,mid,dl,AM,RPM,AUX2,AUX1,TIME//      d
  mem.first[5]=0b00000000; //down left clock 2nd//ul,mid,dl,PM,prevU,PrevUR,PrevDR,PrevD
  mem.first[6]=0b00000000; //down left clock 3rd//ul,mid,dl,Clock Dots,prevU,PrevUR,PrevDR,PrevD
  mem.first[7]=0b00000000; //down left clock 4rd//ul,mid,dl,Person Icon,prevU,PrevUR,PrevDR,PrevD
  mem.first[8]=0b00000000; //NC?,Warning,mail,wawes,prevU,PrevUR,PrevDR,PrevD
  mem.first[9]=0b00000000; //down Right temperature first // ul,mid,dl,Room,PCIE,AGP,DDR,VRAM
  mem.first[10]=0b00000000;//down Right temperature second // ul,mid,dl,Temp,,prevU,PrevUR,PrevDR,PrevD
  mem.first[11]=0b00000000;//down Right temperature third // ul,mid,dl,decimalDot,prevU,PrevUR,PrevDR,PrevD
  mem.first[12]=0b00000000;//temp circle,top part of deg,mid of deg,lowerpart of deg,prevU,PrevUR,PrevDR,PrevD
  mem.first[13]=0b00000000; // NC
  mem.first[14]=0b00000000;// NC
  mem.first[15]=0b00000000; // NC

  mem.second[0]=0b11111111; //Clock panel 1st digit//ul,mid,dl,turbo,3,2,1,User
  mem.second[1]=0b11111111; //Clock panel 2nd digit//ul,mid,dl,Normal,prevU,PrevUR,PrevDR,PrevD
  mem.second[2]=0b11111111; //Clock panel 3st digit//ul,mid,dl,Quiet,prevU,PrevUR,PrevDR,PrevD
  mem.second[3]=0b11111111; //Clock panel 4st digit//ul,mid,dl,Default,prevU,PrevUR,PrevDR,PrevD
  mem.second[4]=0b11111111; //uper divider,mhz,half circle ul,VGA,prevU,PrevUR,PrevDR,PrevD
  mem.second[5]=0b11111111; //UR circle divider,divider line right,DR circle divider,divider line bottom,mid logo,AutoDrive,dividing line left,DL divider circle
  mem.second[6]=0b11111111; //UR temp 1st digit //u,ur,dr,d,ul,m,dl,CPU 
  mem.second[7]=0b11111111; //UR temp 2nd digit //u,ur,dr,d,ul,m,dl,SYS 
  mem.second[8]=0b11111111; //UR temp 3rd digit //u,ur,dr,d,ul,m,dl,decimal point 
  mem.second[9]=0b11111111; //C and some warning TR
  mem.second[10]=0b11011111;//fourth digit downtop right
  mem.second[11]=0b11111111;//third digit downtop right
  mem.second[12]=0b11111111;//second digit downtop right
  mem.second[13]=0b11111111;//first digit downtop right
  mem.second[14]=0b00000000; // NC
  mem.second[15]=0b00000000; // NC



  SetCS(0,1); //Sets CS pins high for init
  SetCS(1,1);
  DATAHigh;
  WRHigh;
  delay(50);
  Init_1621();
  HT1621_all_on(16);
  delay(1000);
  HT1621_all_off(16);
  delay(1000);
  int b=0;
  for(int i=0;i<32;i+=2){
      Write_1621(i,mem.first[b],0);
      b++;
  }
  b=0;
  for(int i=0;i<32;i+=2){
      Write_1621(i,mem.second[b],1);
      b++;
  }

  // for(int i=0; i<=30;i+=2) {
  //   Write_1621(i,0xff,0);
  //   delay(180);
  // }
  // for(int i=0; i<=30;i+=2) {
  //   Write_1621(i,0xff,1);
  //   delay(180);
  // }
} 
void loop() {
  // put your main code here, to run repeatedly:
 
}