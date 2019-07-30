/*
 * FILE                : usart.c
 * DESCRIPTION         : This file is usart driver.
 * Author              : 
 * Rev                 : 1.0
 * Date                : 2017-04-04
 */
//------------------------ Include files ------------------------//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <math.h>
#include <stdarg.h>

#include "..\FWlib\inc\stm32f4xx_rcc.h"
#include "..\FWlib\inc\stm32f4xx_gpio.h"
#include "..\FWlib\inc\stm32f4xx_usart.h"

#include "board.h"
#include "..\include\usart.h"


//--------------------------- Variable --------------------------// 
/* USART */			
extern  char      msg_buf[MAX_RecvFrame];     // received message, used for proceding
extern  uint32_t  msg_buf_valid;	            // received valid flag
extern  char      recv_buf[MAX_RecvFrame];    // receiving buffer               
extern  uint32_t  recv_state;                 // receive state
extern  uint32_t  recv_timer;                 // receive time-out, �����ֽڼ䳬ʱ�ж�
//extern  uint8_t   recv_chksum;              // computed checksum
extern  uint32_t  recv_ctr;                   // reveiving pointer 


static int send_string_to_usart4(char * str);
static int send_byte_to_usart4(char data);
static int initialize_usart4(unsigned long int baudrate);
static int my_printf4(const char * fmt,...);
static int send_buffer4(void * ,int);


UART_T usart4 = {
	//.receive_ok_flag=0,
	//.counter=0,
	.send_byte   = send_byte_to_usart4,
	.send_string = send_string_to_usart4,
	.initialize  = initialize_usart4,
	.printf      = my_printf4,
	.send_buffer = send_buffer4
};


//--------------------------- Function --------------------------//
//USART4 initialize
/*
 * Name               : initialize_usart4
 * Description        : 
 * Author             : 
 * Rev                : 0.00
 * Date               : 11/21/2015
 */
static int initialize_usart4(unsigned long int baudrate)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);             // GPIOʱ��ʹ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                        //PA0Ϊ�����������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                        //PA1Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4);           //PA0���Ÿ���ΪUART4
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4);           //PA1���Ÿ���ΪUART4
	
	USART_DeInit(UART4);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);            //UART4ʱ��ʹ��
	  
	USART_InitStructure.USART_BaudRate = baudrate;                   //������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;      //8������λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;           //1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;             //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  //�շ�ģʽ
	USART_Init(UART4, &USART_InitStructure);                         //��ʼ��UART4
	USART_Cmd(UART4, ENABLE);                                        //ʹ��UART4
	//USART_ITConfig(UART4,USART_IT_PE,ENABLE);             //USART_IT_PE   : if a parity error occur
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);             //USART_IT_RXNE : if receive buffer register is not empty
	
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	return 0;
}

/*
 * Name               : send_buffer4
 * Description        : 
 * Author             : 
 * Rev                : 0.00
 * Date               : 11/21/2015
 */
static int send_buffer4(void * buf,int len)                                  
{
	char *p = (char *)buf;
	
	if (len <= 0)
		return -1;
	
	while(len --){
		send_byte_to_usart4(*p);
		p ++;
	}
	
	return 0;
}

/*
 * Name               : send_byte_to_usart4
 * Description        : 
 * Author             : 
 * Rev                : 0.00
 * Date               : 11/21/2015
 */
static int send_byte_to_usart4(char data)
{
	//while(!(USART_GetFlagStatus(UART4,USART_FLAG_TC) == 1));        //�ȴ������������
	while(!(USART_GetFlagStatus(UART4,USART_FLAG_TXE) == 1));         //ZZX: �ȴ����ͼĴ�����
	USART_SendData(UART4,data);                                       //������д�����ݼĴ�����
	
	return 0;
}

/*
 * Name               : send_string_to_usart4
 * Description        : 
 * Author             : 
 * Rev                : 0.00
 * Date               : 11/21/2015
 */
static int send_string_to_usart4(char * str)
{
	while(*str != '\0'){
		while(!(USART_GetFlagStatus(UART4,USART_FLAG_TC) == 1));
		USART_SendData(UART4,*str++);	
	}
	return 0;
}

/*
 * Name               : printf
 * Description        : 
 * Author             : 
 * Rev                : 0.00
 * Date               : 11/21/2015
 */
static int my_printf4(const char * fmt,...)
{
	__va_list arg_ptr; 
	char buf[UART_BUFFER_SIZE];
  		
	memset(buf,'\0',sizeof(buf));

	va_start(arg_ptr,fmt);
	vsprintf(buf,fmt,arg_ptr);
	va_end(arg_ptr);

	send_string_to_usart4(buf);

	return 0;
}


/*
 * Name               : UART4_IRQHandler
 * Description        : 
 * Author             : 
 * Rev                : 1.0
 * Date               : 2017-04-04
*  Note               : �� startup_stm32f40_41xxx.s ���� 
 */
void UART4_IRQHandler(void)
{	
  char c;	
    
  if (USART_GetFlagStatus(UART4,USART_FLAG_RXNE) != RESET)
  { //�����ж�(���յ�һ���ֽ�)
    c = USART_ReceiveData(UART4);	  //��DR�Զ���RXNE	        
    switch (recv_state)
    {
      case FSA_INIT://�Ƿ�Ϊ֡ͷ
                    if (c == FRAME_STX)
										{ //Ϊ֡ͷ, ��ʼ�µ�һ֡                        
											recv_ctr = 0;				
											recv_timer = RECV_TIMEOUT;						
											recv_state = FSA_DATA; 							
										}
										break;				 																			
										
      case FSA_DATA://��ȡ���
					          recv_buf[recv_ctr] = c;                                      
										if (recv_ctr == 15)             
											recv_state = FSA_END;   //�Ѿ��յ�ָ�����ȵ���������
										else
											recv_ctr++;   //��δ����						 
                    recv_timer = RECV_TIMEOUT;
                    break;

      case FSA_END: //�Ƿ�Ϊ֡β
                    if ((c == FRAME_ETX) && (msg_buf_valid == 0))
                    { //�Ѿ��յ�����һ֡������ǰ�յ�����Ϣ�Ѿ���������
                      memcpy(&msg_buf[0], &recv_buf[0], 16);	 					  						  
                      msg_buf_valid = 1;
                    }										
      default:      //��λ
                    recv_state = FSA_INIT;
                    break;                        	
    }//end switch         	    
  }//end if	
}
