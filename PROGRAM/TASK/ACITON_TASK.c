#include "ACTION_TASK.h"

#include "FreeRTOS.h"
#include "task.h"

#include "PPM_TASK.h"
#include "RC_Control.h"


//�˶����ݰ�����
static  Air_move_t   Air_move;

static void Air_init( Air_move_t *Air_move_init);                          //�����˶���ʼ��
static void Air_set_mode(Air_move_t *Air_move_mode);                       //����ģʽ�趨
static void Air_feedback_update(Air_move_t *Air_move_update);              //�������ݸ���
static void Air_mode_change_control_transit(Air_move_t *Air_move_transit); //����ģʽ�л����ݱ���
static void Air_set_contorl(Air_move_t  *Air_move_control_set);            //���п������趨


//�û������� 
void action_task(void *pvParameters)
{
	  //����һ��ʱ��
    vTaskDelay( ACTION_TASK_INIT_TIME );
	
	  //�˶���ʼ��
	  Air_init(&Air_move);
	
    while(1)
    {
			 //����ģʽ�趨 
			 Air_set_mode(&Air_move);
			
			 //����ģʽ�л����ݱ���
			 Air_mode_change_control_transit(&Air_move);
			
			 //�������ݸ���
			 Air_feedback_update(&Air_move);
			
			 //���п������趨
			 Air_set_contorl(&Air_move);
			
       vTaskDelay( ACTION_CONTROL_TIME_MS );
    }
}   




//�����˶���ʼ��
static void Air_init(Air_move_t *Air_move_init)
{
    if (Air_move_init == NULL)
    {
        return;
    }

    //λ�û�pidֵ
    const static fp32 X_position_pid[3] = { X_position_KP, X_position_KI, X_position_KD};
    const static fp32 Y_position_pid[3] = { Y_position_KP, Y_position_KI, Y_position_KD};
    const static fp32 Z_position_pid[3] = { Z_position_KP, Z_position_KI, Z_position_KD};
		
		
    //��ʼ״̬Ϊʧ��״̬
    Air_move_init->Air_model = AIR_RC_ALTHOLD;
		
		//��ʼ���Ƹ߶��趨
		Air_move_init->Air_height_set  =  MIN_POSITIN_Z;
		
    //��ȡң����ָ��
    Air_move_init->Air_RC = get_remote_control_point();
		
		//��ȡPPM���ݰ�ָ��
    Air_move_init->Air_PPM = get_PPM_control_point();
		
		//��ȡ���봫����ָ��
		Air_move_init->Air_distance = get_distance_control_point();
		
		//��ȡλ�ô�����ָ��
		Air_move_init->Air_position = get_position_control_point();		

    //��ʼ��PID �˶�
    PID_Init( &Air_move_init->X_position_PID, PID_POSITION, X_position_pid, X_position_MAX_OUT, X_position_MAX_IOUT);  //λ��ʽ
    PID_Init( &Air_move_init->Y_position_PID, PID_POSITION, Y_position_pid, Y_position_MAX_OUT, Y_position_MAX_IOUT);  //λ��ʽ
    PID_Init( &Air_move_init->Z_position_PID, PID_POSITION, Z_position_pid, Z_position_MAX_OUT, Z_position_MAX_IOUT);  //λ��ʽ	
		
    //����һ������
    Air_feedback_update(Air_move_init);
}




//����ģʽ�趨
static void Air_set_mode(Air_move_t *Air_move_mode)
{
   if (Air_move_mode == NULL)
    {
        return;
    }
		
	 if( switch_is_up(Air_move_mode->Air_RC->rc.s[MODE_CHANNEL]) )
	  {
	     Air_move_mode->Air_model = AIR_FOLLOW;
	  }
   else
	  {
			 if( switch_is_up(Air_move_mode->Air_RC->rc.s[SENSOR_CHANNEL]) )     Air_move_mode->Air_model = AIR_RC_SENSOR_ALTHOLD;  
			 if( switch_is_mid(Air_move_mode->Air_RC->rc.s[SENSOR_CHANNEL]) )    Air_move_mode->Air_model = AIR_RC_ALTHOLD;
			 if( switch_is_down(Air_move_mode->Air_RC->rc.s[SENSOR_CHANNEL]) )   Air_move_mode->Air_model = AIR_STOP;
	  }	
}




//ģʽ�л����ݸ���
static void Air_mode_change_control_transit(Air_move_t *Air_move_transit)
{
    if (Air_move_transit == NULL)
    {
        return;
    }

    if (Air_move_transit->Last_Air_model == Air_move_transit->Air_model)
    {
        return;
    }

		//���PID��������
    PID_clear(&Air_move_transit->X_position_PID);
    PID_clear(&Air_move_transit->Y_position_PID);		
    PID_clear(&Air_move_transit->Z_position_PID);	
		
		//���������߶�Ϊ��ǰ�߶�
		Air_move_transit->Air_height_set  = Air_move_transit->Air_Z_rx ;
		
		Air_move_transit->Last_Air_model = Air_move_transit->Air_model;
}





//�������ݸ���
static void Air_feedback_update(Air_move_t *Air_move_update)
{
    if (Air_move_update == NULL)
    {
        return;
    }

   Air_move_update->Air_Z_rx = Air_move_update->Air_distance->distance_rx;
		
   Air_move_update->Air_X_rx = Air_move_update->Air_position->position_x;
	 Air_move_update->Air_Y_rx = Air_move_update->Air_position->position_y;
}




//���п������趨
static void Air_set_contorl(Air_move_t  *Air_move_control_set)
{
	
    if( Air_move_control_set == NULL )
    {
        return;
    }

	 //	ֹͣģʽ��
	  if( Air_move_control_set->Air_model == AIR_STOP )
		{
		   Air_move_control_set->Air_throttle_set = CHANNEL_LOW;
		   Air_move_control_set->Air_yaw_set      = CHANNEL_LOW;
		   Air_move_control_set->Air_pitch_set    = CHANNEL_HIGH;
		   Air_move_control_set->Air_roll_set     = CHANNEL_HIGH;	
			
		   Air_move_control_set->Air_model_set    = STABILIZE_DATA;  //����ģʽ
		}
		
	
		
   //ң��������ģʽ��
	  if( Air_move_control_set->Air_model == AIR_RC_ALTHOLD )
		{ 
			 Air_move_control_set->Air_throttle_set = ( Air_move_control_set->Air_RC->rc.ch[THROTTLE_CHANNEL] +660.0f )* CHANNEL_to_PPM_SEN + 25.2f;
			 Air_move_control_set->Air_yaw_set = ( Air_move_control_set->Air_RC->rc.ch[YAW_CHANNEL] + 660.0f ) * CHANNEL_to_PPM_SEN + 25.2f;
			 Air_move_control_set->Air_pitch_set = ( - Air_move_control_set->Air_RC->rc.ch[PITCH_CHANNEL] + 660.0f ) * CHANNEL_to_PPM_SEN + 25.2f;    
			 Air_move_control_set->Air_roll_set = ( Air_move_control_set->Air_RC->rc.ch[ROLL_CHANNEL] + 660.0f ) * CHANNEL_to_PPM_SEN + 25.2f;
			
		   Air_move_control_set->Air_model_set    = ALTHOLD_DATA;		  //����ģʽ	
		}
		
		
		
	 //ң��������������ģʽ��
	  if( Air_move_control_set->Air_model == AIR_RC_SENSOR_ALTHOLD )
		{

			//ң���������������и߶�
			Air_move_control_set->Air_height_set +=  Air_move_control_set->Air_RC->rc.ch[THROTTLE_CHANNEL] * THROTTLE_to_HEIGHT_ADD_SEN;   
		
			//�����߶��޷�
			Air_move_control_set->Air_height_set  =  Air_move_control_set->Air_height_set > MAX_POSITIN_Z ? MAX_POSITIN_Z : Air_move_control_set->Air_height_set;
			Air_move_control_set->Air_height_set  =  Air_move_control_set->Air_height_set < MIN_POSITIN_Z ? MIN_POSITIN_Z : Air_move_control_set->Air_height_set;
		
			//���ſ��Ƹ߶�����	
			Air_move_control_set->Air_throttle_set = PID_Calc( &Air_move_control_set->Z_position_PID , Air_move_control_set->Air_Z_rx , Air_move_control_set->Air_height_set) +  50.0f ;
	
			//YAW��pitch��roll ���ſ��ƣ�pitch���ģ�
			Air_move_control_set->Air_yaw_set = ( Air_move_control_set->Air_RC->rc.ch[YAW_CHANNEL] + 660.0f ) * CHANNEL_to_PPM_SEN + 25.2f;
			Air_move_control_set->Air_pitch_set = ( - Air_move_control_set->Air_RC->rc.ch[PITCH_CHANNEL] + 660.0f ) * CHANNEL_to_PPM_SEN + 25.2f;  
			Air_move_control_set->Air_roll_set = ( Air_move_control_set->Air_RC->rc.ch[ROLL_CHANNEL] + 660.0f ) * CHANNEL_to_PPM_SEN + 25.2f;	
		
			Air_move_control_set->Air_model_set    = ALTHOLD_DATA;		  //����ģʽ	  	
		}
		
		
		
	  //�������ģʽ��
	  if( Air_move_control_set->Air_model == AIR_FOLLOW )
		{
			
			//��׼�߶�λ������
			Air_move_control_set->Air_throttle_set = PID_Calc( &Air_move_control_set->Z_position_PID , Air_move_control_set->Air_Z_rx , STAND_POSITIN_Z ) +  50.0f ;
			
			//YAW�᷽�򲻱�
			 Air_move_control_set->Air_yaw_set = CHANNEL_HALF;
			
			//pitch ��roll��PID���ſ��ƣ�pitch���ģ�
			if( (Air_move_control_set->Air_position->last_position_x != Air_move_control_set->Air_position->position_x)  || 
				  (Air_move_control_set->Air_position->last_position_y != Air_move_control_set->Air_position->position_y)    )
			{
		    Air_move_control_set->Air_roll_set     =    PID_Calc( &Air_move_control_set->X_position_PID , Air_move_control_set->Air_X_rx , STAND_POSITIN_X ) +  50.0f ;
		    Air_move_control_set->Air_pitch_set    =  - PID_Calc( &Air_move_control_set->Y_position_PID , Air_move_control_set->Air_Y_rx , STAND_POSITIN_Y ) +  50.0f ;
			}
			else
			{
				PID_clear(&Air_move_control_set->X_position_PID);
        PID_clear(&Air_move_control_set->Y_position_PID);
				
			  Air_move_control_set->Air_roll_set = ( Air_move_control_set->Air_RC->rc.ch[ROLL_CHANNEL] + 660.0f ) * CHANNEL_to_PPM_SEN + 25.2f;	
				Air_move_control_set->Air_pitch_set = ( - Air_move_control_set->Air_RC->rc.ch[PITCH_CHANNEL] + 660.0f ) * CHANNEL_to_PPM_SEN + 25.2f;  
			}
			
			 Air_move_control_set->Air_model_set    = ALTHOLD_DATA;		  //����ģʽ	  
		}
		
		
		//���������޷�
		Air_move_control_set->Air_throttle_set  =  Air_move_control_set->Air_throttle_set > CHANNEL_HIGH ? CHANNEL_HIGH : Air_move_control_set->Air_throttle_set;
		Air_move_control_set->Air_throttle_set  =  Air_move_control_set->Air_throttle_set < CHANNEL_LOW  ? CHANNEL_LOW  : Air_move_control_set->Air_throttle_set;

		Air_move_control_set->Air_yaw_set  =  Air_move_control_set->Air_yaw_set > CHANNEL_HIGH ? CHANNEL_HIGH : Air_move_control_set->Air_yaw_set;
		Air_move_control_set->Air_yaw_set  =  Air_move_control_set->Air_yaw_set < CHANNEL_LOW  ? CHANNEL_LOW  : Air_move_control_set->Air_yaw_set;

		Air_move_control_set->Air_pitch_set  =  Air_move_control_set->Air_pitch_set > CHANNEL_HIGH ? CHANNEL_HIGH : Air_move_control_set->Air_pitch_set;
		Air_move_control_set->Air_pitch_set  =  Air_move_control_set->Air_pitch_set < CHANNEL_LOW  ? CHANNEL_LOW  : Air_move_control_set->Air_pitch_set;

		Air_move_control_set->Air_roll_set  =  Air_move_control_set->Air_roll_set > CHANNEL_HIGH ? CHANNEL_HIGH : Air_move_control_set->Air_roll_set;
		Air_move_control_set->Air_roll_set  =  Air_move_control_set->Air_roll_set < CHANNEL_LOW  ? CHANNEL_LOW  : Air_move_control_set->Air_roll_set;		
		
		
    //���ݴ���
	  Air_move_control_set->Air_PPM->Channel_3_throttle = (int8_t)Air_move_control_set ->Air_throttle_set;
	  Air_move_control_set->Air_PPM->Channel_4_yaw      = (int8_t)Air_move_control_set ->Air_yaw_set;
	  Air_move_control_set->Air_PPM->Channel_2_pitch    = (int8_t)Air_move_control_set ->Air_pitch_set;
	  Air_move_control_set->Air_PPM->Channel_1_roll     = (int8_t)Air_move_control_set ->Air_roll_set;
		Air_move_control_set->Air_PPM->Channel_5_model    = (int8_t)Air_move_control_set ->Air_model_set;
		
}

