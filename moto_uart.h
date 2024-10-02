#ifndef __MOTO_UART_H
#define __MOTO_UART_H



#include "usart.h"
#include "uart.h"
#include "stdio.h"

//У���ֽ�CheckSum
#define CheckSum 0x6B



//������ַIDAddr

#define IDAddr1 0x01
#define IDAddr2 0x02
#define IDAddr3 0x03
#define IDAddr4 0x04
#define IDAddr5 0x05

//������Func_Code
#define Speed_mode 0xF6   //�ٶ�ģʽ���ƹ�����
#define Seat_mode 0xFD    //λ��ģʽ
#define STOP 0xFE         //ֹͣ
#define MOTO_Enable 0xF3   //ʹ�ܹ�����

//���ͬ��
#define Multi_BEGIN  0xFF 



#define Multi_OFF    0x00
#define Multi_ON     0x01

#define CW 0x01
#define CCW 0x00
//λ��ģʽ�����ģʽ����ģʽ
#define OPPOSITE 0x00    //���
#define ABSOLUTE 0x01    //����

//ʹ��
#define M_Enable 0x01
#define M_Disable 0x00

void speed_moto_contual(uint8_t ID_ADD,uint16_t speed,uint8_t acc,uint8_t multi);
void Seat_moto_contual(uint8_t ID_ADD,uint16_t speed,uint8_t acc,uint32_t step,uint8_t OandA,uint8_t multi);
void Moto_Now_Stop(uint8_t ID_ADD,uint8_t multi);
void ConvertToHex(int decimal,unsigned char *hexstr);



#endif


