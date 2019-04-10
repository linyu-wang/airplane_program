#ifndef __DISTANCE_CONTROL_H
#define __DISTANCE_CONTROL_H

#include "sys.h"

//��������������
#define   FLAG_0      0
//�����½�������  
#define	  FLAG_1      1

typedef struct
{
  int8_t    TIM5_flag;   
	uint32_t  distance_counter_rx; 
	fp32      distance_rx;      
	
}distance_control_t;


extern void  distance_control_init(void);  //�������ʼ��
extern const distance_control_t *get_distance_control_point(void); //��ȡ����������ݰ�ָ��

#endif
