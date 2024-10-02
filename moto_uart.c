/*
  * @brief 串口控制张大头步进电机闭环控制器指令
   
  * @write by zz7me
*/

#include "moto_uart.h"

//转换10进制到16位
//4位转换
void ConvertTo4Hex(unsigned int decimalNumber,unsigned char *OByte,unsigned char *SByte,unsigned char *TByte,unsigned char *FByte)
{
  *FByte=(decimalNumber>>24)&0xFF;
	*TByte=(decimalNumber>>16)&0xFF;
	*SByte=(decimalNumber>>8)&0xFF;
  *OByte=decimalNumber&0xFF;
}
//2位转换
void ConvertTo2Hex(unsigned short decimalNumber,unsigned char *highByte,unsigned char *lowByte)
{
  *highByte=(decimalNumber>>8)&0xFF;
  *lowByte=decimalNumber&0xFF;
}
//1位转换
void ConvertToHex(int decimal,unsigned char *hexstr)
{
  *hexstr=decimal&0xFF;
}

//速度模式控制                    id            //速度       加速度       多机同步
void speed_moto_contual(uint8_t ID_ADD,uint16_t speed,uint8_t acc,uint8_t multi)
{
  uint8_t date[8];
	
	unsigned char highByte;
	unsigned char lowByte;
	
	date[0]=ID_ADD;                   //  器件id      ---------
  date[1]=Speed_mode;               //  模式   
	
	if(speed>0)date[2]=CW;    	//  旋转方向      -------- 
	else date[2]=CCW;
	
	//date[2]=dir;                
	
 ConvertTo2Hex(speed,&highByte,&lowByte);
	date[3]=highByte;
	date[4]=lowByte;
	
	
	ConvertToHex(acc,&lowByte);
	date[5]=lowByte;                      //  加速度        --------   
	date[6]=multi;                        //  多机同步标志位  --------- 
	date[7]=CheckSum;                     //  检查位
	
	HAL_UART_Transmit(&huart2,date,8,10);  //发送
	HAL_UART_Transmit(&huart1,date,8,10);  //发送
}



//位置模式控制                  id              速度       加速度      步数           相/绝对模式     多机同步
void Seat_moto_contual(uint8_t ID_ADD,uint16_t speed,uint8_t acc,uint32_t step,uint8_t OandA,uint8_t multi)
{
  uint8_t date[13];

	unsigned char OByte;
	unsigned char SByte;
	unsigned char TByte;
	unsigned char FByte;
	
	date[0]=ID_ADD;             //ID
	date[1]=Seat_mode;          //位置模式
	if(speed>0)date[2]=CW;    	//  旋转方向判断     -------- 
	else date[2]=CCW;
	ConvertTo2Hex(speed,&TByte,&FByte);
	date[3]=TByte;              //高低八位速度
	date[4]=FByte;
	ConvertToHex(acc,&FByte);
	date[5]=FByte;               //加速度
	ConvertTo4Hex(step,&OByte,&SByte,&TByte,&FByte);
	date[6]=FByte;               //四个16位数据，代表步数
	date[7]=TByte;
	date[8]=SByte;
	date[9]=OByte;
	
	date[10]=OandA;                        // OPPOSITE 0x00//相对    ABSOLUTE 0x01    //绝对
	date[11]=multi;                        //  多机同步标志位  --------- 
	date[12]=CheckSum;                     //  检查位
	
	
	HAL_UART_Transmit(&huart2,date,13,10);  //发送
	HAL_UART_Transmit(&huart1,date,13,10);  //发送
	
}

//急刹
void Moto_Now_Stop(uint8_t ID_ADD,uint8_t multi)
{
  uint8_t date[5];
	
  date[0]=ID_ADD;     //id
  date[1]=STOP;       //功能
	date[2]=0x98;       //功能
	date[3]=multi;      //多级同步
	date[4]=CheckSum;   //校验位
	HAL_UART_Transmit(&huart2,date,5,10);  //发送
	HAL_UART_Transmit(&huart1,date,5,10);  //发送
}

//电机使/失能

void Moto_enable(uint8_t ID_ADD,uint8_t MY_Eable,uint8_t multi)
{
 uint8_t date[6];
	
	date[0]=ID_ADD;     //id
  date[1]=MOTO_Enable;   //功能
	date[2]=0xAB;       //功能
	date[3]=MY_Eable;   //使能  M_Enable 0x01  M_Disable 0x00
	date[4]=multi;      //多级同步
	date[5]=CheckSum;   //校验位
	
	HAL_UART_Transmit(&huart2,date,6,10);  //发送
	HAL_UART_Transmit(&huart1,date,6,10);  //发送
}

//多机同步
void Moto_synchronous(uint8_t ID_ADD)
{
 uint8_t date[4];
  date[0]=ID_ADD;
  date[1]=Multi_BEGIN;
  date[2]=0x66;
  date[3]=CheckSum;

	HAL_UART_Transmit(&huart2,date,4,10);  //发送
	HAL_UART_Transmit(&huart1,date,4,10);  //发送
	
}


