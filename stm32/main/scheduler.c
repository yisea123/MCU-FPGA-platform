/*C**************************************************************************
* NAME:  scheduler.c
*----------------------------------------------------------------------------
* Copyright (c) 2017.04.03
*----------------------------------------------------------------------------           
* REVISION: 1.0     
*----------------------------------------------------------------------------
* PURPOSE:	This file contains the scheduler routines
* NOTES:
*****************************************************************************/

/*_____ I N C L U D E S ____________________________________________________*/
#include "board.h"
#include "iwdg.h"
#include "scheduler.h"         /* scheduler definition */


/*_____ D E F I N I T I O N ________________________________________________*/

			  
/*_____ D E C L A R A T I O N ______________________________________________*/



/*F**************************************************************************
* NAME:     sch_scheduler_init
*----------------------------------------------------------------------------
* PARAMS:
* return:
*----------------------------------------------------------------------------
* PURPOSE: Scheduler initialization
*----------------------------------------------------------------------------
* NOTE:	Task_x_init() and Task_x_fct() are defined in scheduler.h
*****************************************************************************/
void sch_scheduler_init(void)
{ 
  Task_1_init();   
  Task_2_init();     
  Task_3_init(); 
  Task_4_init();  
  Task_5_init();  
  Task_6_init(); 
  Task_7_init();  
  Task_8_init();  
  Task_9_init(); 
  Task_10_init(); 
}


/*F**************************************************************************
* NAME:     sch_scheduler
*----------------------------------------------------------------------------
* PARAMS:
* return:
*----------------------------------------------------------------------------
* PURPOSE: Task execution scheduler 
*----------------------------------------------------------------------------
* REQUIREMENTS:
*****************************************************************************/
void sch_scheduler(void)
{
  while (1)
  {
    Task_1_fct();
    Task_2_fct();
    Task_3_fct();            
    Task_4_fct(); 
    Task_5_fct();    
    Task_6_fct(); 
    Task_7_fct();         
    Task_8_fct();          
    Task_9_fct();          
    Task_10_fct();         	  
		
	  #ifdef  Enable_WDT           
		  iwdg.feed_dog();
    #endif     
  }
}
