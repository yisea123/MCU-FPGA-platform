 /*
 * FILE               : iwdg.c
 * DESCRIPTION        : This file is iwdg driver.
 * Author             : 
 * Rev                : 0.00
 * Date               : 11/21/2015
 */
 
//----------------------include----------------------------//
#include "board.h"
#include "..\include\iwdg.h"
#include "..\fwlib\inc\stm32f4xx_iwdg.h"


//------------------ Function Prototype ------------------//
static int  initialize(void);
static void feed_dog(void);


//----------------------variable--------------------------//
IWDG_T iwdg = {
	.initialize = initialize,
	.feed_dog = feed_dog
};


//-----------------Function-----------------------------//
/*
 * Name               : initialize
 * Description        : 
 * Author             : 
 * Rev                : 0.00
 * Date               : 11/21/2015
 */
static int initialize(void)
{  
#ifdef Enable_WDT		
	//����WDT
	//1sι��
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);         //ȡ���Ĵ�����д����
	IWDG_SetPrescaler(4);                                 //���ö������Ź���Ԥ��Ƶϵ��
	IWDG_SetReload(625);                                  //���ö������Ź�����װ��ֵ
	IWDG_ReloadCounter();                                 //��װ�ؼ�����	
	IWDG_Enable();                                        //ʹ�ܶ������Ź�
#endif  	
	
	return 0;
}


/*
 * Name               : feed_dog
 * Description        : 
 * Author             : 
 * Rev                : 0.00
 * Date               : 11/21/2015
 */
static void feed_dog(void)
{
	IWDG_ReloadCounter();
}
