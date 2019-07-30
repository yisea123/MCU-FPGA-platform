/*C**************************************************************************
* NAME:   alarm_task.c
*----------------------------------------------------------------------------
* Copyright (c) 2017.
*----------------------------------------------------------------------------
* RELEASE:     2017.04.04
* REVISION:    1.0     
*----------------------------------------------------------------------------
* PURPOSE:          
*   This file contains the led display task and attached routines.
*****************************************************************************/


/*_____ I N C L U D E S ____________________________________________________*/
#include "board.h"               /* board configuration */
#include "led.h"
#include "alarm_task.h"          /* alarm task definition */


/*_____ D E F I N I T I O N ________________________________________________*/
/* LED��˸���ڲ��� */
#define  LED_ON_FL    (200/SCHEDULER_TICK)
#define  LED_OFF_FL   (800/SCHEDULER_TICK)


/*_____ D E C L A R A T I O N ______________________________________________*/
/* LED */
extern  uint32_t  led_flash_tick;      //all leds ��˸��ʱtick  
extern  uint32_t  led_flash_pn;        //��˸LED������ʱ��α�־: 0 - ��; 1 - ��
extern  uint32_t  led_light_mode[3];   //ÿ��led������ʽ:  0 - ��; 1 - ����; 2 - ��˸



/*F**************************************************************************
* NAME: alarm_task_init
*----------------------------------------------------------------------------
* PARAMS:
* return:
*----------------------------------------------------------------------------
* PURPOSE: alarm task initialization
*****************************************************************************/
void alarm_task_init(void)
{
  /* for led initialize */  
	led_flash_pn = 0; 
  led_light_mode[0] = 2;  //�����˸
  led_light_mode[1] = 0;  //�̵���
	led_light_mode[2] = 0;  //������					
}


/*F**************************************************************************
* NAME: alarm_task
*----------------------------------------------------------------------------
* PARAMS:
* return:
*----------------------------------------------------------------------------
* PURPOSE: alarm task
*****************************************************************************/
void alarm_task(void)
{ 
  //1. LED           
  if ((led_light_mode[0] == 2) || (led_light_mode[1] == 2) || (led_light_mode[2] == 2))
  { //����Ҫ�������˸LED  
    if (led_flash_pn && (led_flash_tick >= LED_ON_FL))
    { //������ʱ���, �ɷ�תΪ��
      if (led_light_mode[0] == 2)
      { //���Ϊ��˸    
        LED_RED_OFF;      //��      
      }
      if (led_light_mode[1] == 2)
      { //�̵�Ϊ��˸
        LED_GREEN_OFF;     //��             
      }	
      if (led_light_mode[2] == 2)
      { //����Ϊ��˸
        LED_BLUE_OFF;     //��             
      }				
      led_flash_tick = 0;
      led_flash_pn = 0;
    }
    else if (!led_flash_pn && (led_flash_tick >= LED_OFF_FL))
    { //������ʱ���, �ɷ�תΪ��
      if (led_light_mode[0] == 2)
      { //���Ϊ��˸
        LED_RED_ON;       //��
      }
      if (led_light_mode[1] == 2)
      { //�̵�Ϊ��˸
        LED_GREEN_ON;     //��       
      }	
      if (led_light_mode[2] == 2)
      { //����Ϊ��˸
        LED_BLUE_ON;      //��       
      }			
      led_flash_tick = 0;
      led_flash_pn = 1;              
    }        
  }  
}//end FUNC()
