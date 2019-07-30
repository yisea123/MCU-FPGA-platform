/*
 * FILE               : systick.c
 * DESCRIPTION        : This file is systick driver.
 * Author             : 
 * Rev                : 0.00
 * Date               : 11/21/2015
 */
 
//--------------------------- Include ---------------------------//
#include "board.h"
#include "..\include\systick.h"
#include "..\fwlib\inc\stm32f4xx_syscfg.h"


/* ϵͳ��ʱ */
extern  uint32_t  gl_sys_tick;	 /* ϵͳ��ʱ,�� tick */                    
extern  uint32_t  gl_dly_tick;	 /* Ӧ����ʱ��ʱ,�� tick */  

/* LED */
extern  uint32_t  led_flash_tick;    //all leds ��˸��ʱtick  

/* USART */			              
extern  uint32_t  recv_state;        //receive state
extern  uint32_t  recv_timer;        //receive time-out, �����ֽڼ䳬ʱ�ж�


//--------------------- Function Prototype ----------------------//
static int initialize(void);

//--------------------------- Variable --------------------------//
SYSTICK_T systick = {
	.initialize = initialize
};

//--------------------------- Function --------------------------//
/*
 * Name               : initialize
 * Description        : 
 * Author             : 
 * Rev                : 0.00
 * Date               : 11/21/2015
 */
static int initialize(void)
{
	//�� SCHEDULER_TICK ��ʱ, SCHEDULER_TICK�ĵ�λ����Ϊ ms	
	if (SysTick_Config((SystemCoreClock / 1000) * SCHEDULER_TICK))
	{ //δ���óɹ�
		while(1);
	}
	return 0;
}


/*
 * Name               : SysTick_Handler
 * Description        : 
 * Author             : 
 * Rev                : 1.00
 * Date               : 2017-04-04
 */
void SysTick_Handler(void)
{
  /* ϵͳ��ʱ */
  gl_sys_tick++;         /* ϵͳ��ʱ,�� tick */  
  if (gl_dly_tick > 0)   /* Ӧ����ʱ��ʱ,�� tick */  
	  gl_dly_tick--;

	/* ��ʱ�������� */
	led_flash_tick++;      //LED��˸��ʱ
	
  /* USART�ֽ�֮����ճ�ʱ */  
	if (recv_state != FSA_INIT) 
	{ //�ǳ�ʼ״̬����Ҫ����Ƿ�ʱ
		if (recv_timer > 0)
			recv_timer--;
		if (recv_timer == 0)  
			recv_state = FSA_INIT;   //�ֽ�֮����ճ�ʱ����λ����ʼ״̬
	}
}
