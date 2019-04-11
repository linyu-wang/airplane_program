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
	BSP_init();              //设备初始化
	startTask();             //创建开始任务
  vTaskStartScheduler();   //开启任务调度
}
 

void BSP_init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	
	delay_init(168);		      //初始化延时函数
	LED_Init();		            //初始化LED端口
	ppm_Init();               //初始化PPM发生器
	remote_control_init();    //初始化遥控器
  distance_control_init();  //初始化高度测量
	position_control_init();  //初始化位置测量
}




