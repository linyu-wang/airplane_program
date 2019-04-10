#include "distance_control.h" 

#include "sonic.h" 

//���������ݰ�
static  distance_control_t   distance_control;


//��������ָ��
const distance_control_t *get_distance_control_point(void)
{
    return &distance_control;
}


//����ʼ��
void  distance_control_init(void)
{
  sonic_Init();
	distance_control.TIM5_flag  = FLAG_0 ;
  TIM_Cmd(TIM2, ENABLE);  
}



void TIM5_IRQHandler(void)
{
   if( TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET )  //���������¼�
		{	
        if(distance_control.TIM5_flag == FLAG_0)
				{
				  TIM5->CNT =0;
					
					TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);
					
					distance_control.TIM5_flag = FLAG_1;
					
				}
				else if(distance_control.TIM5_flag == FLAG_1)
				{
					distance_control.distance_counter_rx =  TIM5->CNT ;
					
					distance_control.distance_rx = (fp32)((distance_control.distance_counter_rx) * 0.017f);
					
					TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);
					
					distance_control.TIM5_flag = FLAG_0;
				}	
	  }
	 TIM_ClearITPendingBit(TIM5, TIM_IT_CC1); //����жϱ�־λ
}


