/**
  ******************************************************************************
  * @file    board.h
  * @author  
  * @version V1.0.0
  * @date    2017-04-03
  * @brief   Header file for MOS-Tester
  ******************************************************************************  
  */ 
  
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
 extern "C" {
#endif 

	 
/* Includes ------------------------------------------------------------------*/	 
#include <stdint.h>
	 
	 
/* Scheduler Tick */
#define SCHEDULER_TICK       10    //��λ: ms	(������ms,�����SysTick_Config())

/* UART */
#define	FRAME_STX          0x02	   // Frame header = \STX
#define FRAME_ETX          0x03    // Frame end 	 = \ETX
//#define UART_BAUD_RATE   115200    // UART baud rate
//#define UART_BAUD_RATE 460800    // UART baud rate	 
#define UART_BAUD_RATE 921600    // UART baud rate	 
#define	MAX_RecvFrame        30    // ���ջ�������С
#define	MAX_TransFrame       30    // ���ͻ�������С
#define RECV_TIMEOUT          5    // ����ʱ������ֽڼ����ʱ����, ��λ: tick                                

/* Uart Queue */
typedef struct strUART_Q
{
  uint32_t  flag;                   //״̬��0 - ����; 1 - �ȴ�����; 2 - ���ڷ���; 3 - �ѷ���,�ȴ�Ӧ��
  uint8_t   tdata[MAX_TransFrame];  //���ݰ�
  uint32_t  len;					          //���ݰ���Ч����(��Ч���ֽ�)
  uint32_t  need_wait_ack;          //�Ƿ���Ҫ�ȴ�Ŀ�Ļ�Ӧ�� 0 - �� 1 - ��
  uint32_t  wait_ack_time;		      //���ͺ�ȴ�Ŀ�Ļ�Ӧ����ʣ���ʱ�䣬��λ��tick 
                                    //  ��flag=3,��ʣ��ʱ���Ϊ0ʱ���ط�                                    
}sUART_Q;

#define UART_WAIT_ACK   (300/SCHEDULER_TICK)   //���ͺ�ȴ�Ŀ�Ļ�Ӧ������������ʱ��, ��λ��tick
#define UART_QUEUE_NUM   5                     //���Ͷ�����

/* uart state constant(�����ڽ���) */
#define FSA_INIT      0      //�ȴ�֡ͷ \STX
#define FSA_DATA      1      //�ȴ����
#define FSA_END       2      //�ȴ�֡β \ETX 

/* WDT */		 
//#define Enable_WDT

#ifdef __cplusplus
}
#endif

#endif /* _BOARD_H_ */  


/******************* (C) COPYRIGHT 2017 *****END OF FILE****/
