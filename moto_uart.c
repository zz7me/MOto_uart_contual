/*
  * @brief ���ڿ����Ŵ�ͷ��������ջ�������ָ��
   
  * @write by zz7me
*/

#include "moto_uart.h"

//ת��10���Ƶ�16λ
//4λת��
void ConvertTo4Hex(unsigned int decimalNumber,unsigned char *OByte,unsigned char *SByte,unsigned char *TByte,unsigned char *FByte)
{
  *FByte=(decimalNumber>>24)&0xFF;
	*TByte=(decimalNumber>>16)&0xFF;
	*SByte=(decimalNumber>>8)&0xFF;
  *OByte=decimalNumber&0xFF;
}
//2λת��
void ConvertTo2Hex(unsigned short decimalNumber,unsigned char *highByte,unsigned char *lowByte)
{
  *highByte=(decimalNumber>>8)&0xFF;
  *lowByte=decimalNumber&0xFF;
}
//1λת��
void ConvertToHex(int decimal,unsigned char *hexstr)
{
  *hexstr=decimal&0xFF;
}

//�ٶ�ģʽ����                    id            //�ٶ�       ���ٶ�       ���ͬ��
void speed_moto_contual(uint8_t ID_ADD,uint16_t speed,uint8_t acc,uint8_t multi)
{
  uint8_t date[8];
	
	unsigned char highByte;
	unsigned char lowByte;
	
	date[0]=ID_ADD;                   //  ����id      ---------
  date[1]=Speed_mode;               //  ģʽ   
	
	if(speed>0)date[2]=CW;    	//  ��ת����      -------- 
	else date[2]=CCW;
	
	//date[2]=dir;                
	
 ConvertTo2Hex(speed,&highByte,&lowByte);
	date[3]=highByte;
	date[4]=lowByte;
	
	
	ConvertToHex(acc,&lowByte);
	date[5]=lowByte;                      //  ���ٶ�        --------   
	date[6]=multi;                        //  ���ͬ����־λ  --------- 
	date[7]=CheckSum;                     //  ���λ
	
	HAL_UART_Transmit(&huart2,date,8,10);  //����
	HAL_UART_Transmit(&huart1,date,8,10);  //����
}



//λ��ģʽ����                  id              �ٶ�       ���ٶ�      ����           ��/����ģʽ     ���ͬ��
void Seat_moto_contual(uint8_t ID_ADD,uint16_t speed,uint8_t acc,uint32_t step,uint8_t OandA,uint8_t multi)
{
  uint8_t date[13];

	unsigned char OByte;
	unsigned char SByte;
	unsigned char TByte;
	unsigned char FByte;
	
	date[0]=ID_ADD;             //ID
	date[1]=Seat_mode;          //λ��ģʽ
	if(speed>0)date[2]=CW;    	//  ��ת�����ж�     -------- 
	else date[2]=CCW;
	ConvertTo2Hex(speed,&TByte,&FByte);
	date[3]=TByte;              //�ߵͰ�λ�ٶ�
	date[4]=FByte;
	ConvertToHex(acc,&FByte);
	date[5]=FByte;               //���ٶ�
	ConvertTo4Hex(step,&OByte,&SByte,&TByte,&FByte);
	date[6]=FByte;               //�ĸ�16λ���ݣ�������
	date[7]=TByte;
	date[8]=SByte;
	date[9]=OByte;
	
	date[10]=OandA;                        // OPPOSITE 0x00//���    ABSOLUTE 0x01    //����
	date[11]=multi;                        //  ���ͬ����־λ  --------- 
	date[12]=CheckSum;                     //  ���λ
	
	
	HAL_UART_Transmit(&huart2,date,13,10);  //����
	HAL_UART_Transmit(&huart1,date,13,10);  //����
	
}

//��ɲ
void Moto_Now_Stop(uint8_t ID_ADD,uint8_t multi)
{
  uint8_t date[5];
	
  date[0]=ID_ADD;     //id
  date[1]=STOP;       //����
	date[2]=0x98;       //����
	date[3]=multi;      //�༶ͬ��
	date[4]=CheckSum;   //У��λ
	HAL_UART_Transmit(&huart2,date,5,10);  //����
	HAL_UART_Transmit(&huart1,date,5,10);  //����
}

//���ʹ/ʧ��

void Moto_enable(uint8_t ID_ADD,uint8_t MY_Eable,uint8_t multi)
{
 uint8_t date[6];
	
	date[0]=ID_ADD;     //id
  date[1]=MOTO_Enable;   //����
	date[2]=0xAB;       //����
	date[3]=MY_Eable;   //ʹ��  M_Enable 0x01  M_Disable 0x00
	date[4]=multi;      //�༶ͬ��
	date[5]=CheckSum;   //У��λ
	
	HAL_UART_Transmit(&huart2,date,6,10);  //����
	HAL_UART_Transmit(&huart1,date,6,10);  //����
}

//���ͬ��
void Moto_synchronous(uint8_t ID_ADD)
{
 uint8_t date[4];
  date[0]=ID_ADD;
  date[1]=Multi_BEGIN;
  date[2]=0x66;
  date[3]=CheckSum;

	HAL_UART_Transmit(&huart2,date,4,10);  //����
	HAL_UART_Transmit(&huart1,date,4,10);  //����
	
}


