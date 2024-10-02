#ifndef __MOTO_UART_H
#define __MOTO_UART_H



#include "usart.h"
#include "uart.h"
#include "stdio.h"

//校验字节CheckSum
#define CheckSum 0x6B



//器件地址IDAddr

#define IDAddr1 0x01
#define IDAddr2 0x02
#define IDAddr3 0x03
#define IDAddr4 0x04
#define IDAddr5 0x05

//功能码Func_Code
#define Speed_mode 0xF6   //速度模式控制功能码
#define Seat_mode 0xFD    //位置模式
#define STOP 0xFE         //停止
#define MOTO_Enable 0xF3   //使能功能码

//多机同步
#define Multi_BEGIN  0xFF 



#define Multi_OFF    0x00
#define Multi_ON     0x01

#define CW 0x01
#define CCW 0x00
//位置模式的相对模式决定模式
#define OPPOSITE 0x00    //相对
#define ABSOLUTE 0x01    //绝对

//使能
#define M_Enable 0x01
#define M_Disable 0x00

void speed_moto_contual(uint8_t ID_ADD,uint16_t speed,uint8_t acc,uint8_t multi);
void Seat_moto_contual(uint8_t ID_ADD,uint16_t speed,uint8_t acc,uint32_t step,uint8_t OandA,uint8_t multi);
void Moto_Now_Stop(uint8_t ID_ADD,uint8_t multi);
void ConvertToHex(int decimal,unsigned char *hexstr);



#endif


