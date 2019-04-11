#ifndef __POSITION_CONTROL_H
#define __POSITION_CONTROL_H

#include "sys.h"

//定义接收数据长度(防止传输越界)
#define  CAMERA_RX_BUF_NUM    24u    
#define  CAMERA_FRAME_LENGTH  12u    


typedef struct
{    
	uint8_t   camera_rx_buf[2][CAMERA_RX_BUF_NUM];  //原始数据
	fp32      position_x;    //x轴坐标
	fp32      position_y;    //y轴坐标
	fp32      last_position_x;  //上次x轴坐标
	fp32      last_position_y;  //上次x轴坐标
	
}position_control_t;


extern void  position_control_init(void);  //位置检测初始化
extern const position_control_t *get_position_control_point(void); //获取位置控制数据包指针

#endif
