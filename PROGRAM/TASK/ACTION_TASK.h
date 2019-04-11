#ifndef _ACTION_TASK_H_
#define _ACTION_TASK_H_

#include "sys.h"
#include "RC_Control.h"
#include "PPM_TASK.h"
#include "distance_control.h" 
#include "position_control.h" 

#include "pid.h"

//�����ʼ��ʱ��
#define  ACTION_TASK_INIT_TIME  300
//������Ƽ������
#define  ACTION_CONTROL_TIME_MS  2

//ģʽ����ͨ��
#define  MODE_CHANNEL    1
//����������ͨ��
#define  SENSOR_CHANNEL  0


//����ͨ��
#define  THROTTLE_CHANNEL   1
#define  YAW_CHANNEL        0
#define  PITCH_CHANNEL      3
#define  ROLL_CHANNEL       2

//ң����ͨ��ת��ΪPPM����
#define  CHANNEL_to_PPM_SEN  0.0378f  

//ң����ͨ��ת��Ϊ�߶���������
#define  THROTTLE_to_HEIGHT_ADD_SEN  0.000060606f


//�ڴ���׼λ�� ���ǳ���Ҫ��
#define   MIN_POSITIN_Z        0.0f     //��;�����Ϣ
#define   STAND_POSITIN_Z     60.0f     //��׼������Ϣ
#define   MAX_POSITIN_Z      100.0f     //��߾�����Ϣ

#define   STAND_POSITIN_Y    120.0f     //��׼���ص���Ϣ
#define   STAND_POSITIN_X    160.0f     //��׼���ص���Ϣ


//X��λ��PID�������ɻ����� ����Ϊ����
#define  X_position_KP           0.1f
#define  X_position_KI           0.0f
#define  X_position_KD        2000.0f
#define  X_position_MAX_IOUT     0.0f
#define  X_position_MAX_OUT      5.0f

//Y��λ��PID�������ɻ�ǰ�� ��ǰΪ����
#define  Y_position_KP           0.1f
#define  Y_position_KI           0.0f
#define  Y_position_KD        2000.0f
#define  Y_position_MAX_IOUT     0.0f
#define  Y_position_MAX_OUT      5.0f

//Z��λ��KP�������ɻ����� ����Ϊ����
#define  Z_position_KP           0.3f   
#define  Z_position_KI           0.0f
#define  Z_position_KD        4000.0f
#define  Z_position_MAX_IOUT     0.0f
#define  Z_position_MAX_OUT     10.0f



//����ģʽö�١�
typedef enum
{
    AIR_RC_ALTHOLD,
    AIR_RC_SENSOR_ALTHOLD,
    AIR_FOLLOW,
	  AIR_STOP,
	
} Air_mode_e;



//���������ݿ��ư�
typedef struct
{
	Air_mode_e         Air_model;           //��ǰ����ģʽ
	Air_mode_e         Last_Air_model;      //�ϴη���ģʽ
	
  const RC_ctrl_t           *Air_RC;           //ң����RC���ݰ�
	PPM_control_t             *Air_PPM;          //ң����PPM���ݰ�
	const distance_control_t  *Air_distance;     //���봫�������ݰ�
	const position_control_t  *Air_position;     //λ�ô��������ݰ�
	
	
  fp32               Air_Z_rx;   //������Z��λ�÷���
  fp32               Air_Y_rx;   //������Y��λ�÷���
  fp32               Air_X_rx;   //������X��λ�÷���
	
	fp32             Air_height_set;     //�������߶��趨
	
	fp32              Air_throttle_set;  //���������Ų����趨  ��������Χ 25.0f ~ 75.0f��
	fp32              Air_yaw_set;       //������ƫ�������趨 
  fp32              Air_pitch_set;     //���������������趨
  fp32              Air_roll_set;      //���������������趨
	fp32              Air_model_set;     //������ģʽ�����趨
	
	
	PidTypeDef       X_position_PID;    //X��PID���ư�
	PidTypeDef       Y_position_PID;    //Y��PID���ư�
  PidTypeDef       Z_position_PID;    //Z��PID���ư�
	
}Air_move_t;


extern void action_task(void *pvParameters);

#endif

