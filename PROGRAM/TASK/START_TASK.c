#include "START_TASK.h"

#include "FreeRTOS.h"
#include "task.h"

#include "USER_TASK.h"
#include "PPM_TASK.h"
#include "ACTION_TASK.h"


//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128
//������
TaskHandle_t StartTask_Handler;

//�������ȼ�
#define PPM_TASK_PRIO		   2
//�����ջ��С	
#define PPM_STK_SIZE 		  256  
//������
TaskHandle_t PPMTask_Handler;


//�������ȼ�
#define USER_TASK_PRIO		 3
//�����ջ��С	
#define USER_STK_SIZE 		 256 
//������
TaskHandle_t USERTask_Handler;


//�������ȼ�
#define ACTION_TASK_PRIO	  4
//�����ջ��С	
#define ACTION_STK_SIZE 	 256 
//������
TaskHandle_t ACTIONTask_Handler;




//��ʼ������
void start_task(void *pvParameters)
{
   taskENTER_CRITICAL();           //�����ٽ���
	
   //����USER����
    xTaskCreate((TaskFunction_t )user_task,     	
                (const char*    )"user_task",   	
                (uint16_t       )USER_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )USER_TASK_PRIO,	
                (TaskHandle_t*  )&USERTask_Handler);  

   //����PPM����
    xTaskCreate((TaskFunction_t )ppm_task,     	
                (const char*    )"ppm_task",   	
                (uint16_t       )PPM_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )PPM_TASK_PRIO,	
                (TaskHandle_t*  )&PPMTask_Handler); 

   //����ACTION����
    xTaskCreate((TaskFunction_t )action_task,     	
                (const char*    )"action_task",   	
                (uint16_t       )ACTION_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )ACTION_TASK_PRIO,	
                (TaskHandle_t*  )&ACTIONTask_Handler); 
								
								
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}



void startTask(void)
{
    xTaskCreate((TaskFunction_t)start_task,          //������
                (const char *)"start_task",          //��������
                (uint16_t)START_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)START_TASK_PRIO,        //�������ȼ�
                (TaskHandle_t *)&StartTask_Handler); //������
}
