#include "sys.h"

#include "FreeRTOS.h"
#include "task.h"

#include "delay.h"
#include "led.h"
#include "ppm.h"

#include "RC_Control.h"
#include "distance_control.h" 
#include "position_control.h" 

#include "START_TASK.h"

void BSP_init(void);


int main(void)
{
	BSP_init();              //�豸��ʼ��
	startTask();             //������ʼ����
  vTaskStartScheduler();   //�����������
}
 

void BSP_init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	
	delay_init(168);		      //��ʼ����ʱ����
	LED_Init();		            //��ʼ��LED�˿�
	ppm_Init();               //��ʼ��PPM������
	remote_control_init();    //��ʼ��ң����
  distance_control_init();  //��ʼ���߶Ȳ���
	position_control_init();  //��ʼ��λ�ò���
}




