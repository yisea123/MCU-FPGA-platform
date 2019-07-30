/*C**************************************************************************
* NAME:  comm_task.c
*----------------------------------------------------------------------------
* Copyright (c) 2017.
*----------------------------------------------------------------------------
* RELEASE:      2017.04.03
* REVISION:     1.0     
*----------------------------------------------------------------------------
* PURPOSE:          
*   This file contains the communication task and attached routines
*****************************************************************************/

/*_____ I N C L U D E S ____________________________________________________*/
#include <string.h>
#include <stdlib.h>
#include "board.h"
#include "usart.h"
#include "led.h"
#include "fsmc.h"
#include "fpga_flag.h"
#include "comm_task.h"            /* comm task definition */


/*_____ D E F I N I T I O N ________________________________________________*/


/*_____ D E C L A R A T I O N ______________________________________________*/      
/* ϵͳ��ʱ */
extern   uint32_t  gl_sys_tick;	  /* ϵͳ��ʱ,�� tick */                    
extern   uint32_t  gl_dly_tick;	  /* Ӧ����ʱ��ʱ,�� tick */ 

/* LED */
extern  uint32_t  led_flash_tick;      //all leds ��˸��ʱtick  
extern  uint32_t  led_flash_pn;        //��˸LED������ʱ��α�־: 0 - ��; 1 - ��
extern  uint32_t  led_light_mode[3];   //ÿ��led������ʽ:  0 - ��; 1 - ����; 2 - ��˸

/* USART */			
extern  char      msg_buf[MAX_RecvFrame];     // received message, used for proceding
extern  uint32_t  msg_buf_valid;	            // received valid flag
extern  char      recv_buf[MAX_RecvFrame];    // receiving buffer               
extern  uint32_t  recv_state;                 // receive state
extern  uint32_t  recv_timer;                 // receive time-out, �����ֽڼ䳬ʱ�ж�
//extern  uint8_t   recv_chksum;                // computed checksum
extern  uint32_t  recv_ctr;                   // reveiving pointer 

/*
extern  uint8_t   trans_buf[MAX_TransFrame];  // uart transfer buffer������ǰ��Ҫ��������ֽڣ���У���ֽ��⣩
extern  uint32_t  trans_ctr;                  // transfering pointer
extern  uint32_t  trans_size;                 // transfered bytes number���������ֽڣ�����֡ͷ��У�飩
extern  uint8_t   trans_chksum;               // check-sum ���߷��ͱ߼��㣩
extern  uint32_t  trans_occupy;               // ��������ռ�ñ�־��1-��ռ��, 0-����                      

extern  uint8_t  uart_q_index;                // ���ڷ���ĳ���������ţ���Ϊ0xFF, ��ʾû���κ����ڷ���
extern  sUART_Q  uart_q[UART_QUEUE_NUM];	    // ���ڶ���
*/		

extern  uint16_t  gVoltage_Ampl;   //�������
extern  uint16_t  gPulse_width;    //������
extern  uint16_t  gPulse_period;   //��������
extern  uint32_t  gSamples_K;      //��������(��KΪ��λ, 1K=1024��)
extern  uint32_t  gExec_flag;      //ִ�б�־: 
                                   //    0 - ���ȴ���������,�����ѯFPGA�����Ͳ�������, 
															     //        ���Ѿ����һ�ν��յ�����������Ͳ������ݹ���
															     //    1 - ���յ���������,���ʹﵽFPGA,����ѯFPGA�Ƿ���׼������������
															     //    2 - FPGA��׼��������,ARM����FPGA����������

/* UART */ 
void uart_init(void);
//void uart_start_trans(void);    



/*F**************************************************************************
* NAME: uart_init
*----------------------------------------------------------------------------
* PARAMS:
* return:
*----------------------------------------------------------------------------
* PURPOSE: uart device initialization
*----------------------------------------------------------------------------
* REQUIREMENTS:
*****************************************************************************/
void uart_init(void)
{	
  //��λ����	
	recv_state = FSA_INIT;
	recv_timer = 0;
	recv_ctr = 0;
	//trans_ctr = 0;
	//trans_size = 0;	
	//trans_occupy = 0;   //����
  
  //��ʼ��USARTӲ��
  //����main()�� usart4.initialize(UART_BAUD_RATE) ��ִ��
}


/*F**************************************************************************
* NAME: comm_task_init
*----------------------------------------------------------------------------
* PARAMS:
* return:
*----------------------------------------------------------------------------
* PURPOSE: Communication task initialization
*----------------------------------------------------------------------------
* REQUIREMENTS:
*****************************************************************************/
void comm_task_init(void)
{ 
  //uint8_t i;	

  //1. USART������ʼ��	
	msg_buf_valid = 0;
	
/*	
	uart_q_index  = 0xFF;   //�޶�������뷢������
	for (i=0; i<UART_QUEUE_NUM; i++)
	{
		uart_q[i].flag = 0;                 //������
		//uart_q[i].tdata[0] = FRAME_STX;	  //֡ͷ
		uart_q[i].need_wait_ack = 0;        //����Ӧ�� 
	}/
*/
  
  //2. UARTӲ����ʼ��
  uart_init(); 
	
	//3. ��ӡ��ʾ
	usart4.printf("hello! I am MOS-Tester!\r\n");
	
	//4. ϵͳ״̬
	gExec_flag = 0;    //�ȴ���������
}
					

/*F**************************************************************************
* NAME: comm_task
*----------------------------------------------------------------------------
* PARAMS:
* return:
*----------------------------------------------------------------------------
* PURPOSE: communication task
*----------------------------------------------------------------------------
* REQUIREMENTS:
*****************************************************************************/
void comm_task(void)
{   
	char str_val[5];	
	static uint32_t samples_K_remain;
	uint32_t i, j, k;
	uint16_t fsmc_val;
	uint32_t fsmc_addr_base;   //ÿK���ݵĻ���ַ
		 		
  //1. �Ƿ����½��յ��������?
  if (msg_buf_valid)
  {	//�����������������
    //a. ��ȡ��������
		//�����������
		memcpy(&str_val[0], &msg_buf[0], 4);
		str_val[4] = 0;
		gVoltage_Ampl = atoi(str_val);       
		//����������
		memcpy(&str_val[0], &msg_buf[4], 4);
		//str_val[4] = 0;				
    gPulse_width  = atoi(str_val);
		//������������
		memcpy(&str_val[0], &msg_buf[8], 4);
		//str_val[4] = 0;				
    gPulse_period = atoi(str_val);
    //�����������(KΪ��λ)
		memcpy(&str_val[0], &msg_buf[12], 4);
		//str_val[4] = 0;			
    gSamples_K  = atoi(str_val);    //KΪ��λ,ÿKΪ1024����
    samples_K_remain = gSamples_K;			
		
		//b. �ñ�־
    if (gExec_flag == 2)
		{ //���ڶ��ϴδ���,ֹͣ��, ֹͣ��ɫ����˸ָʾ
      led_light_mode[1] = 0;    //����ɫ��
		  LED_GREEN_OFF;
		}			
		gExec_flag = 1;
		//����ָʾ��(��ɫ�Ƴ���)							
    led_light_mode[0] = 0;    //���ɫ��
		LED_RED_OFF;
		led_light_mode[2] = 1;    //������ɫ��
    LED_BLUE_ON;
		
		//c. ����������д��FPGA
		//�Ȳ�����λ
    fpga_write((uint32_t)0x08, 0x00);   
/*		
		//���Ը�λ��������ȼĴ����Ƿ���ȷ?
		fsmc_val = fpga_read(0x02);		
    usart4.send_byte((fsmc_val >> 8) & 0xFF);	   //���͸��ֽ�		
    usart4.send_byte(fsmc_val & 0xFF);	         //���͵��ֽ�
		//���Ը�λ����������ڼĴ����Ƿ���ȷ?
		fsmc_val = fpga_read(0x04);
    usart4.send_byte((fsmc_val >> 8) & 0xFF);	   //���͸��ֽ�		
    usart4.send_byte(fsmc_val & 0xFF);	         //���͵��ֽ�
*/
    //��ʼд������ֵ
		fpga_write((uint32_t)0x01, gVoltage_Ampl);   //�����ѹ��ֵ	
		fpga_write((uint32_t)0x02, gPulse_width);    //�����ѹ���						
		fpga_write((uint32_t)0x04, gPulse_period);   //�����ѹ����		
		
		//����д���������ȼĴ����Ƿ���ȷ?
		fsmc_val = fpga_read(0x02);		
    usart4.send_byte((fsmc_val >> 8) & 0xFF);	   //���͸��ֽ�		
    usart4.send_byte(fsmc_val & 0xFF);	         //���͵��ֽ�
		//����д�����������ڼĴ����Ƿ���ȷ?
		fsmc_val = fpga_read(0x04);
    usart4.send_byte((fsmc_val >> 8) & 0xFF);	   //���͸��ֽ�		
    usart4.send_byte(fsmc_val & 0xFF);	         //���͵��ֽ�
	
		
		//ZZX: ����SRAM 		
/*		
    //��д��SRAM - ϵ��ֵ
		j = samples_K_remain;
    while (j)		
		{	
			//���㵱ǰ1K�������SRAM����ַ
			fsmc_addr_base = gSamples_K - j;   //K ��ַ
			fsmc_addr_base <<= 10;             //16bit���ʵ�1K����ַ
			//ÿ��д1024����ַ
		  for (i=0; i<1024; i++)
			{ //д SRAM
				k = fsmc_addr_base + i;
				k <<= 1;                   //<<1 ��ʾת��Ϊ���ֵ�ַ	
			  fpga_write_SRAM((uint32_t)k, (uint16_t)i); 							
			}			
			j--;
		}
*/
		
    //d. ��������Ѵ���,��λ��־
    msg_buf_valid = 0;	   
  }
    
  //2. �Ƿ���Ҫ����FPGA
  if (gExec_flag == 1)
  { //���յ���������,���ʹﵽFPGA,����ѯFPGA�Ƿ���׼������������	
	  if (FPGA_FLAG == 0)
		{ //FPGA��׼�����������ݣ�����ȥ��ȡ
      gExec_flag = 2;
			//����ָʾ��
      led_light_mode[2] = 0;    //����ɫ��
		  LED_BLUE_OFF;
		  led_light_mode[1] = 2;    //��˸��ɫ��   
      LED_GREEN_ON;  		
		}					
	}
  else if (gExec_flag == 2)
  { //FPGA��׼��������,ARM����FPGA����������
		//ÿһ����ѭ����1K���㲢����
    if (samples_K_remain == 0)
		{ //��ȫ��������ϻ����跢��
			//�ָ�ָʾ
			gExec_flag = 0;
      led_light_mode[1] = 0;    //����ɫ��
		  LED_GREEN_OFF;
		  led_light_mode[0] = 2;    //��˸��ɫ��  			
		}	
    else
	 	{ //����Ҫ����					
			if (samples_K_remain == gSamples_K)
			{ //��һ�η���, �ȷ���֡ͷ
				usart4.send_byte(0x02);			
			}
			//���㵱ǰ1K�������SRAM����ַ
			fsmc_addr_base = gSamples_K - samples_K_remain;
			fsmc_addr_base <<= 10;       //16bit���ʵ�1K����ַ
			//ÿ�ζ�������1K��������(1024����ַ)
			for (i=0; i<1024; i++)
			{ 
				//��FPGA
				k = fsmc_addr_base + i;
				k <<= 1;                    //<<1 ��ʾת��Ϊ���ֵ�ַ					
				fsmc_val = fpga_read_SRAM(k);						  
        usart4.send_byte((fsmc_val >> 8) & 0xFF);	   //���͸��ֽ�			  
        usart4.send_byte(fsmc_val & 0xFF);					 //���͵��ֽ�
			}			
			//������
			samples_K_remain--;
			if (samples_K_remain == 0)
			{ //��ȫ���������,����֡β
				usart4.send_byte(0x03);	
			}								
		}			
	}		
  
	
  //2. USART ���з���
/*	
  if (uart_q_index == 0xFF)         
  { //USART�޽��뷢�����̵Ķ�����.         
		for (i=0; i<UART_QUEUE_NUM; i++)
		{ 
			if (uart_q[i].flag == 1)
			{ //�еȴ����͵�����Ŵ����
				uart_q[i].flag = 2;
				uart_q_index = i;
				memcpy(&trans_buf[0], &uart_q[i].tdata[0], uart_q[i].len - 1);   
				trans_size = uart_q[i].len; 		  	  		 
				uart_start_trans();
				break;
			}
		}    
  }
*/	
}//end FUNC()


/*F**************************************************************************
* NAME: uart_start_trans
*----------------------------------------------------------------------------
* PARAMS:    
* return:  None
*----------------------------------------------------------------------------
* PURPOSE: ��ʼ���ڷ���
*----------------------------------------------------------------------------
* REQUIREMENTS:	 ʹ��˳������
*                a. while (trans?_occupy), �ȴ�ǰһ��������
*                b. ��trans?_buf[] 
*                c. ��trans?_size
*                d. ���ñ�����
* Note�� ��ʹ��USART���Ͷ��У������з�����comm_task()����
*****************************************************************************/
/*
void uart_start_trans(void)
{   
  trans_occupy = 1;       
  trans_chksum = 0;  
  trans_ctr = 0;   
  //USART_SendData(, trans_buf[0]);           //�Զ����ϴε�TXE/TC 
  //USART_ITConfig(, USART_IT_TC, DISABLE);   //ZZX: need ? 
  //USART_ITConfig(, USART_IT_TXE, ENABLE);   //������TXE�ж�  
}
*/
