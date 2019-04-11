#ifndef _ACTION_TASK_H_
#define _ACTION_TASK_H_

#include "sys.h"
#include "RC_Control.h"
#include "PPM_TASK.h"
#include "distance_control.h" 
#include "position_control.h" 

#include "pid.h"

//任务初始化时间
#define  ACTION_TASK_INIT_TIME  300
//任务控制间隔周期
#define  ACTION_CONTROL_TIME_MS  2

//模式开关通道
#define  MODE_CHANNEL    1
//传感器开关通道
#define  SENSOR_CHANNEL  0


//拨杆通道
#define  THROTTLE_CHANNEL   1
#define  YAW_CHANNEL        0
#define  PITCH_CHANNEL      3
#define  ROLL_CHANNEL       2

//遥控器通道转换为PPM比例
#define  CHANNEL_to_PPM_SEN  0.0378f  

//遥控器通道转换为高度增量比例
#define  THROTTLE_to_HEIGHT_ADD_SEN  0.000060606f


//期待标准位置 （非常重要）
#define   MIN_POSITIN_Z        0.0f     //最低距离信息
#define   STAND_POSITIN_Z     60.0f     //标准距离信息
#define   MAX_POSITIN_Z      100.0f     //最高距离信息

#define   STAND_POSITIN_Y    120.0f     //标准像素点信息
#define   STAND_POSITIN_X    160.0f     //标准像素点信息


//X轴位置PID参数（飞机左右 向右为正）
#define  X_position_KP           0.1f
#define  X_position_KI           0.0f
#define  X_position_KD        2000.0f
#define  X_position_MAX_IOUT     0.0f
#define  X_position_MAX_OUT      5.0f

//Y轴位置PID参数（飞机前后 向前为正）
#define  Y_position_KP           0.1f
#define  Y_position_KI           0.0f
#define  Y_position_KD        2000.0f
#define  Y_position_MAX_IOUT     0.0f
#define  Y_position_MAX_OUT      5.0f

//Z轴位置KP参数（飞机上下 向上为正）
#define  Z_position_KP           0.3f   
#define  Z_position_KI           0.0f
#define  Z_position_KD        4000.0f
#define  Z_position_MAX_IOUT     0.0f
#define  Z_position_MAX_OUT     10.0f



//飞行模式枚举·
typedef enum
{
    AIR_RC_ALTHOLD,
    AIR_RC_SENSOR_ALTHOLD,
    AIR_FOLLOW,
	  AIR_STOP,
	
} Air_mode_e;



//飞行器数据控制包
typedef struct
{
	Air_mode_e         Air_model;           //当前飞行模式
	Air_mode_e         Last_Air_model;      //上次飞行模式
	
  const RC_ctrl_t           *Air_RC;           //遥控器RC数据包
	PPM_control_t             *Air_PPM;          //遥控器PPM数据包
	const distance_control_t  *Air_distance;     //距离传感器数据包
	const position_control_t  *Air_position;     //位置传感器数据包
	
	
  fp32               Air_Z_rx;   //飞行器Z轴位置反馈
  fp32               Air_Y_rx;   //飞行器Y轴位置反馈
  fp32               Air_X_rx;   //飞行器X轴位置反馈
	
	fp32             Air_height_set;     //飞行器高度设定
	
	fp32              Air_throttle_set;  //飞行器油门参数设定  （变量范围 25.0f ~ 75.0f）
	fp32              Air_yaw_set;       //飞行器偏航参数设定 
  fp32              Air_pitch_set;     //飞行器俯仰参数设定
  fp32              Air_roll_set;      //飞行器翻滚参数设定
	fp32              Air_model_set;     //飞行器模式参数设定
	
	
	PidTypeDef       X_position_PID;    //X轴PID控制包
	PidTypeDef       Y_position_PID;    //Y轴PID控制包
  PidTypeDef       Z_position_PID;    //Z轴PID控制包
	
}Air_move_t;


extern void action_task(void *pvParameters);

#endif

