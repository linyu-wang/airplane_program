#ifndef _PPM_TASK_H_
#define _PPM_TASK_H_

#include "sys.h"

#define  CHANNEL_HIGH   75.0f    //���ͨ��ֵ
#define  CHANNEL_LOW    25.0f    //���ͨ��ֵ
#define  CHANNEL_HALF   50.0f    //�м�ͨ��ֵ

#define   ALTHOLD_DATA      75.0f   //���߿����ź�  
#define   STABILIZE_DATA    25.0f   //���ȿ����ź�


//ͨ�����ݱ仯��Χ 25~75 ,�м�ֵΪ50
typedef struct
{
	int8_t   Channel_1_roll;     // ������      roll
	int8_t   Channel_2_pitch;    // ������     pitch
	int8_t   Channel_3_throttle; // ����       throttle
  int8_t   Channel_4_yaw;      // ƫ����      YAW 
  int8_t   Channel_5_model;    // ģʽͨ��   model
	int8_t   Channel_6;          // δ��        NULL 
  int8_t   Channel_7;          // δ��        NULL
	int8_t   Channel_8;          // δ��        NULL
	int16_t  PPM_conder;         //PPM��������20us����һ��

} PPM_control_t;



extern PPM_control_t *get_PPM_control_point(void);  //��ȡPPM���Ʊ���ָ��
extern void ppm_task(void *pvParameters);           //PPM������������

#endif

