/*
 * Project Name					: iCore3
 * Description					: iCore3_fsmc
 * Tool Versions				: uVision V5.17.0.0
 * Target Device				: STM32F407IGT6
 * Revision							: 1.0
 * Created Date					: 2017.04.03
 */
 
//-----------------------include--------------------------//
#include "..\include\board.h"
#include "..\include\led.h"
#include "..\include\fsmc.h"
#include "..\include\fpga_flag.h"
#include "..\include\iwdg.h"
#include "..\include\usart.h"
#include "..\include\systick.h"
#include "misc.h"
#include "scheduler.h"


//------------------------define--------------------------//

//-----------------------variable-------------------------//

//------------------Function Prototype--------------------//

//-----------------------Function-------------------------//

int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f40_41xxx.s) before to branch to application main.
  */     

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  	
	/*��ʼ��*/
	led.initialize();                      //3��LED����
	usart4.initialize(UART_BAUD_RATE);     
	fsmc.initialize();	
	fpga_flag.initialize();
	
  //��ģ�������ʼ��  
  sch_scheduler_init();	
	
  //Setup SysTick Timer for SCHEDULER_TICK interrupts
  systick.initialize();
  
  //����WDT
  iwdg.initialize(); 

  //Main loop
  sch_scheduler();   		
}
