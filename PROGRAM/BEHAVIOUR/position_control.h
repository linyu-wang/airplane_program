#ifndef __POSITION_CONTROL_H
#define __POSITION_CONTROL_H

#include "sys.h"

//����������ݳ���(��ֹ����Խ��)
#define  CAMERA_RX_BUF_NUM    24u    
#define  CAMERA_FRAME_LENGTH  12u    


typedef struct
{    
	uint8_t   camera_rx_buf[2][CAMERA_RX_BUF_NUM];  //ԭʼ����
	fp32      position_x;    //x������
	fp32      position_y;    //y������
	fp32      last_position_x;  //�ϴ�x������
	fp32      last_position_y;  //�ϴ�x������
	
}position_control_t;


extern void  position_control_init(void);  //λ�ü���ʼ��
extern const position_control_t *get_position_control_point(void); //��ȡλ�ÿ������ݰ�ָ��

#endif
