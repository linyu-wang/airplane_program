#ifndef __DISTANCE_CONTROL_H
#define __DISTANCE_CONTROL_H

#include "sys.h"

//定义上升沿跳变
#define   FLAG_0      0
//定义下降沿跳变  
#define	  FLAG_1      1

typedef struct
{
  int8_t    TIM5_flag;   
	uint32_t  distance_counter_rx; 
	fp32      distance_rx;      
	
}distance_control_t;


extern void  distance_control_init(void);  //距离检测初始化
extern const distance_control_t *get_distance_control_point(void); //获取距离控制数据包指针

#endif
