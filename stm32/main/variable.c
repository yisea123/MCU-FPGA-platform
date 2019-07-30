/*C**************************************************************************
* NAME:   variable.c
*----------------------------------------------------------------------------
* Copyright (c) 2017.
*----------------------------------------------------------------------------
* RELEASE:      2017.04.03
* REVISION:     1.0 
*----------------------------------------------------------------------------
* PURPOSE:
*   This file contains the definition of the global variables.
*****************************************************************************/

/*_____ I N C L U D E S ____________________________________________________*/
#include "board.h"           /* system config definition */


/*_____ D E F I N I T I O N ________________________________________________*/
/* ϵͳ��ʱ */
uint32_t  gl_sys_tick = 0;	 /* ϵͳ��ʱ,�� tick */                    
uint32_t  gl_dly_tick;	     /* Ӧ����ʱ��ʱ,�� tick */  

/* USART */
char      msg_buf[MAX_RecvFrame];     // received message, used for proceding
uint32_t  msg_buf_valid;	            // received valid flag
char      recv_buf[MAX_RecvFrame];    // receiving buffer               
uint32_t  recv_state;                 // receive state
uint32_t  recv_timer;                 // receive time-out, �����ֽڼ䳬ʱ�ж�
//uint8_t   recv_chksum;              // computed checksum
uint32_t  recv_ctr;                   // reveiving pointer 

/*
uint8_t   trans_buf[MAX_TransFrame];  // uart transfer buffer������ǰ��Ҫ��������ֽڣ���У���ֽ��⣩
uint32_t  trans_ctr;                  // transfering pointer
uint32_t  trans_size;                 // transfered bytes number���������ֽڣ�����֡ͷ��У�飩
uint8_t   trans_chksum;               // check-sum ���߷��ͱ߼��㣩
uint32_t  trans_occupy;               // ��������ռ�ñ�־��1-��ռ��, 0-����                      

uint8_t   uart_q_index;               // ���ڷ���ĳ���������ţ���Ϊ0xFF, ��ʾû���κ����ڷ���
sUART_Q   uart_q[UART_QUEUE_NUM];	    // ���ڶ��� 					
*/

/* LED */
uint32_t  led_flash_tick;      //all leds ��˸��ʱtick  
uint32_t  led_flash_pn;        //��˸LED������ʱ��α�־: 0 - ��; 1 - ��
uint32_t  led_light_mode[3];   //ÿ��led������ʽ:  0 - ��; 1 - ����; 2 - ��˸

/*  */
uint16_t  gVoltage_Ampl;       //�������
uint16_t  gPulse_width;        //������
uint16_t  gPulse_period;       //��������
uint32_t  gSamples_K;          //��������(��KΪ��λ, 1K=1024��)
uint32_t  gExec_flag;          //ִ�б�־: 
                               //    0 - ���ȴ���������,�����ѯFPGA�����Ͳ�������, 
															 //        ���Ѿ����һ�ν��յ�����������Ͳ������ݹ���
															 //    1 - ���յ���������,���ʹﵽFPGA,����ѯFPGA�Ƿ���׼������������
															 //    2 - FPGA��׼��������,ARM����FPGA����������


/*_____ D E C L A R A T I O N ______________________________________________*/
