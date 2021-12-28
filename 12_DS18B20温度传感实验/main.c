#include "reg51.h"
#include "intrins.h"
#include "temp.h"

sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;

u8 code smgduan[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f};
char num = 0;
u8 DisplayData[8];

//when i=1, delay 10us
void delay(u16 i){
    while(i--){
    }
}

void datapros(int temp){
    float tp;
    if(temp < 0){
        DisplayData[0] = 0x40;
        temp = temp - 1;
        temp = ~temp;
        tp = temp;
        temp = tp*0.0625+0.5;
    }
    else{
        DisplayData[0]=0x00;
        tp = temp;
        temp = tp * 0.0625 * 100 + 0.5;    
    }
    DisplayData[1] = smgduan[temp % 10000 / 1000];
    DisplayData[2] = smgduan[temp % 1000 / 100];
    DisplayData[3] = smgduan[temp % 100 / 10];
    DisplayData[4] = smgduan[temp % 10 / 1];
}

void DigDisplay(void){
    u8 i;
    for(i = 0;i < 6;i++){
        switch(i){
            case 0:
                LSA = 1;
                LSB = 1;
                LSC = 1;
                break;
            case 1:
                LSA = 0;
                LSB = 1;
                LSC = 1;
                break;
            case 2:
                LSA = 1;
                LSB = 0;
                LSC = 1;
                break;
            case 3:
                LSA = 0;
                LSB = 0;
                LSC = 1;
                break;
             case 4:
                LSA = 1;
                LSB = 1;
                LSC = 0;
                break;
             case 5:
                LSA = 0;
                LSB = 1;
                LSC = 0;
                break;
        }
        P0 = DisplayData[i];
        delay(50);
        P0 = 0x00;
    }
}

void main(void){
	while(1){
        datapros(Ds18b20ReadTemp());
        DigDisplay();	
	}
}