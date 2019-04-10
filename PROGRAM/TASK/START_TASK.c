#include "START_TASK.h"

#include "FreeRTOS.h"
#include "task.h"

#include "USER_TASK.h"
#include "PPM_TASK.h"
#include "ACTION_TASK.h"


//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128
//任务句柄
TaskHandle_t StartTask_Handler;

//任务优先级
#define PPM_TASK_PRIO		   2
//任务堆栈大小	
#define PPM_STK_SIZE 		  256  
//任务句柄
TaskHandle_t PPMTask_Handler;


//任务优先级
#define USER_TASK_PRIO		 3
//任务堆栈大小	
#define USER_STK_SIZE 		 256 
//任务句柄
TaskHandle_t USERTask_Handler;


//任务优先级
#define ACTION_TASK_PRIO	  4
//任务堆栈大小	
#define ACTION_STK_SIZE 	 256 
//任务句柄
TaskHandle_t ACTIONTask_Handler;




//开始任务函数
void start_task(void *pvParameters)
{
   taskENTER_CRITICAL();           //进入临界区
	
   //创建USER任务
    xTaskCreate((TaskFunction_t )user_task,     	
                (const char*    )"user_task",   	
                (uint16_t       )USER_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )USER_TASK_PRIO,	
                (TaskHandle_t*  )&USERTask_Handler);  

   //创建PPM任务
    xTaskCreate((TaskFunction_t )ppm_task,     	
                (const char*    )"ppm_task",   	
                (uint16_t       )PPM_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )PPM_TASK_PRIO,	
                (TaskHandle_t*  )&PPMTask_Handler); 

   //创建ACTION任务
    xTaskCreate((TaskFunction_t )action_task,     	
                (const char*    )"action_task",   	
                (uint16_t       )ACTION_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )ACTION_TASK_PRIO,	
                (TaskHandle_t*  )&ACTIONTask_Handler); 
								
								
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}



void startTask(void)
{
    xTaskCreate((TaskFunction_t)start_task,          //任务函数
                (const char *)"start_task",          //任务名称
                (uint16_t)START_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)START_TASK_PRIO,        //任务优先级
                (TaskHandle_t *)&StartTask_Handler); //任务句柄
}
