#ifndef _PPM_TASK_H_
#define _PPM_TASK_H_

#include "sys.h"

#define  CHANNEL_HIGH   75.0f    //最高通道值
#define  CHANNEL_LOW    25.0f    //最低通道值
#define  CHANNEL_HALF   50.0f    //中间通道值

#define   ALTHOLD_DATA      75.0f   //定高控制信号  
#define   STABILIZE_DATA    25.0f   //自稳控制信号


//通道数据变化范围 25~75 ,中间值为50
typedef struct
{
	int8_t   Channel_1_roll;     // 翻滚角      roll
	int8_t   Channel_2_pitch;    // 俯仰角     pitch
	int8_t   Channel_3_throttle; // 油门       throttle
  int8_t   Channel_4_yaw;      // 偏航角      YAW 
  int8_t   Channel_5_model;    // 模式通道   model
	int8_t   Channel_6;          // 未用        NULL 
  int8_t   Channel_7;          // 未用        NULL
	int8_t   Channel_8;          // 未用        NULL
	int16_t  PPM_conder;         //PPM计数器，20us计数一次

} PPM_control_t;



extern PPM_control_t *get_PPM_control_point(void);  //获取PPM控制变量指针
extern void ppm_task(void *pvParameters);           //PPM产生函数任务

#endif

