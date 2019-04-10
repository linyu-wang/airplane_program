#include "PPM_TASK.h"

#include "FreeRTOS.h"
#include "task.h"

#include "ppm.h"
#include "delay.h"

//PPM���ƽṹ�嶨��
static   PPM_control_t   air_ppm;


//��ȡ�ṹ��ָ��
PPM_control_t *get_PPM_control_point(void)
{
    return &air_ppm;
}


//PPM���������� 
void ppm_task(void *pvParameters)
{
	PPM_OUT=1;     //������PPM�ź���
	air_ppm.PPM_conder = 0;     //PPM����������
	air_ppm.Channel_3_throttle  = CHANNEL_LOW;	   //���������
	air_ppm.Channel_4_yaw       = CHANNEL_HALF;    //ƫ��������
	air_ppm.Channel_2_pitch     = CHANNEL_HALF;    //����������
	air_ppm.Channel_1_roll      = CHANNEL_HALF;    //����������
	air_ppm.Channel_5_model     = ALTHOLD_DATA;    //����ģʽ
	
	air_ppm.Channel_6 = CHANNEL_HALF;          //��ͨ��
	air_ppm.Channel_7 = CHANNEL_HALF;          //��ͨ��
	air_ppm.Channel_8 = CHANNEL_HALF;          //��ͨ��
	
	while(1)
	{ 
		 //�������ۼ�
		 air_ppm.PPM_conder ++;
		
		
		 if( air_ppm.PPM_conder <= 25 ) 
		 {
				PPM_OUT = 0;
		 }
		 else if( air_ppm.PPM_conder > 25 && air_ppm.PPM_conder <= 25 + air_ppm.Channel_1_roll ) 
		 {  
			  PPM_OUT = 1;
		 }
		 else if( air_ppm.PPM_conder > 25+ air_ppm.Channel_1_roll && air_ppm.PPM_conder <= 50 + air_ppm.Channel_1_roll ) 
		 {			 
			  PPM_OUT = 0;	
		 }
		 else if( air_ppm.PPM_conder > 50+ air_ppm.Channel_1_roll && air_ppm.PPM_conder <= 50 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch ) 
		 {			 
			  PPM_OUT = 1;	
		 }	
		 else if( air_ppm.PPM_conder > 50 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch  && 
			        air_ppm.PPM_conder <= 75 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch  ) 
		 {			 
			  PPM_OUT = 0;	
		 }	
		 else if( air_ppm.PPM_conder > 75 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch  && 
			        air_ppm.PPM_conder <= 75 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle ) 
		 {			 
			  PPM_OUT = 1;	
		 }		 
		 else if( air_ppm.PPM_conder > 75 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle && 
			        air_ppm.PPM_conder <= 100 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle ) 
		 {			 
			  PPM_OUT = 0;	
		 } 
		 else if( air_ppm.PPM_conder > 100 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle && 
			        air_ppm.PPM_conder <= 100 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw ) 
		 {			 
			  PPM_OUT = 1;	
		 } 
		 else if( air_ppm.PPM_conder > 100 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw && 
			        air_ppm.PPM_conder <= 125 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw   ) 
		 {			 
			  PPM_OUT = 0;	
		 }	 
		 else if( air_ppm.PPM_conder > 125 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw && 
			        air_ppm.PPM_conder <= 125 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw + air_ppm.Channel_5_model ) 
		 {			 
			  PPM_OUT = 1;	
		 }	
		 else if( air_ppm.PPM_conder > 125  + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw + air_ppm.Channel_5_model && 
			        air_ppm.PPM_conder <= 150 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw + air_ppm.Channel_5_model   ) 
		 {			 
			  PPM_OUT = 0;	
		 }	
		 else if( air_ppm.PPM_conder > 150  + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw + air_ppm.Channel_5_model && 
			        air_ppm.PPM_conder <= 150 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw + air_ppm.Channel_5_model + air_ppm.Channel_6  ) 
		 {			 
			  PPM_OUT = 1;	
		 }	
		 else if( air_ppm.PPM_conder > 150  + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw + air_ppm.Channel_5_model + air_ppm.Channel_6 && 
			        air_ppm.PPM_conder <= 175 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw + air_ppm.Channel_5_model + air_ppm.Channel_6  ) 
		 {			 
			  PPM_OUT = 0;	
		 }	
		 else if( air_ppm.PPM_conder > 175  + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw + air_ppm.Channel_5_model + air_ppm.Channel_6  && 
			        air_ppm.PPM_conder <= 175 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw + air_ppm.Channel_5_model + air_ppm.Channel_6 + air_ppm.Channel_7 ) 
		 {			 
			  PPM_OUT = 1;	
		 }	
		 else if( air_ppm.PPM_conder > 175  + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw + air_ppm.Channel_5_model + air_ppm.Channel_6 + air_ppm.Channel_7 && 
			        air_ppm.PPM_conder <= 200 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw + air_ppm.Channel_5_model + air_ppm.Channel_6 + air_ppm.Channel_7 ) 
		 {
			  PPM_OUT = 0;	
		 }	 
		 else if( air_ppm.PPM_conder > 200  + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw + air_ppm.Channel_5_model + air_ppm.Channel_6 + air_ppm.Channel_7 && 
			        air_ppm.PPM_conder <= 200 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw + air_ppm.Channel_5_model + air_ppm.Channel_6 + air_ppm.Channel_7 + air_ppm.Channel_8) 
		 {			 
			  PPM_OUT = 1;	
		 }	 
		 else if( air_ppm.PPM_conder > 200  + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw + air_ppm.Channel_5_model + air_ppm.Channel_6 + air_ppm.Channel_7 + air_ppm.Channel_8 && 
			        air_ppm.PPM_conder <= 225 + air_ppm.Channel_1_roll + air_ppm.Channel_2_pitch + air_ppm.Channel_3_throttle + air_ppm.Channel_4_yaw + air_ppm.Channel_5_model + air_ppm.Channel_6 + air_ppm.Channel_7 + air_ppm.Channel_8    ) 
		 {
			  PPM_OUT = 0;	
		 }	 
		 else 
		 {			 
			  PPM_OUT = 1;	
		 }	 
		 
		 
		 //��������������
		 if(air_ppm.PPM_conder >= 1000 ) 
		 {
		 air_ppm.PPM_conder =0;
		 }
		 	 
		delay_us(20);	
	}
}   


