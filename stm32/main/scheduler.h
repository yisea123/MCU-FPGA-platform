/*H**************************************************************************
* NAME:  scheduler.h         
*----------------------------------------------------------------------------
* Copyright (c) 2017.04.03
* REVISION:     1.0    
*----------------------------------------------------------------------------
* PURPOSE:
*   This file contains the scheduler definition and the task function to be
*   executed by the scheduler
* NOTE:
*   SCHEDULER_TICK is defined in board.h
*****************************************************************************/

#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_


/*_____ I N C L U D E S ____________________________________________________*/
#include "..\tasks\comm_task.h"       //���������
#include "..\tasks\timing_task.h"     //timing������
#include "..\tasks\alarm_task.h"      //alarm������


/*_____ D E F I N I T I O N ________________________________________________*/

/*----- Task Definitions -----*/
#define Task_1_init()     comm_task_init()      //����������ʼ��
#define Task_2_init()     timing_task_init()    //timing�������ʼ��
#define Task_3_init()     alarm_task_init()     //alarm�������ʼ��
#define Task_4_init()     
#define Task_5_init()     
#define Task_6_init()	   
#define Task_7_init()     
#define Task_8_init()
#define Task_9_init()
#define Task_10_init()


#define Task_1_fct()      comm_task()           //���������
#define Task_2_fct()	    timing_task()         //timing������
#define Task_3_fct()      alarm_task()          //alarm������
#define Task_4_fct()      
#define Task_5_fct()           	
#define Task_6_fct() 	         
#define Task_7_fct()      
#define Task_8_fct()     
#define Task_9_fct()
#define Task_10_fct()


/*_____ D E C L A R A T I O N ______________________________________________*/
void sch_scheduler_init(void);
void sch_scheduler(void);


#endif /* _SCHEDULER_H_ */
