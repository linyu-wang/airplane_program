#include "position_control.h" 

#include "camera.h" 


//����λ�ÿ������ݰ�
static  position_control_t   position_control;


static void camera_to_position(volatile const uint8_t *RX_buf , position_control_t *positon_control_loop);


//��������ָ��
const position_control_t *get_position_control_point(void)
{
    return &position_control;
}


//λ�ÿ��Ƴ�ʼ��
void  position_control_init(void)
{
	camera_Init( position_control.camera_rx_buf[0] , position_control.camera_rx_buf[1] , CAMERA_RX_BUF_NUM );
}


//λ�ü�⴮���ж�
void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        USART_ReceiveData(USART2);
    }
    else if (USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
    {
        static uint16_t this_time_rx_len = 0;
        USART_ReceiveData(USART2);

        if(DMA_GetCurrentMemoryTarget(DMA1_Stream5) == 0)
        {
            //��������DMA
            DMA_Cmd(DMA1_Stream5, DISABLE);
            this_time_rx_len = CAMERA_RX_BUF_NUM - DMA_GetCurrDataCounter(DMA1_Stream5);
            DMA_SetCurrDataCounter(DMA1_Stream5, CAMERA_RX_BUF_NUM);
            DMA1_Stream5->CR |= DMA_SxCR_CT;
            //��DMA�жϱ�־
            DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF2 | DMA_FLAG_HTIF2);
            DMA_Cmd(DMA1_Stream5, ENABLE);
            if(this_time_rx_len == CAMERA_FRAME_LENGTH)
            {
               //����ң��������
               camera_to_position( position_control.camera_rx_buf[0], &position_control );
            }
        }
        else
        {
            //��������DMA
            DMA_Cmd(DMA1_Stream5, DISABLE);
            this_time_rx_len = CAMERA_RX_BUF_NUM - DMA_GetCurrDataCounter(DMA1_Stream5);
            DMA_SetCurrDataCounter(DMA1_Stream5, CAMERA_RX_BUF_NUM);
            DMA1_Stream5->CR &= ~(DMA_SxCR_CT);
            //��DMA�жϱ�־
            DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF2 | DMA_FLAG_HTIF2);
            DMA_Cmd(DMA1_Stream5, ENABLE);
            if(this_time_rx_len == CAMERA_FRAME_LENGTH)
            {
                //����ң��������
               camera_to_position( position_control.camera_rx_buf[1], &position_control );
            }

        }
    }
}



//λ�����ݴ���
static void camera_to_position(volatile const uint8_t *RX_buf , position_control_t *positon_control_loop)
{
    if (RX_buf == NULL || positon_control_loop == NULL)
    {
        return;
    }
		
		if( RX_buf[0]  == 0x5B  && RX_buf[4]  == 0x2C && RX_buf[5] == 0x20 && RX_buf[9] == 0x5D && 
			  RX_buf[10] == 0x0D  && RX_buf[11] == 0x0A )
		{
			//�ϴ�xy
			positon_control_loop->last_position_x  = positon_control_loop->position_x; 
			positon_control_loop->last_position_y  = positon_control_loop->position_y; 
			
			//X��
	   	positon_control_loop->position_x =  (fp32)((RX_buf[1]-0x30)*100 + (RX_buf[2]-0x30)*10 + (RX_buf[3]-0x30))  - 100.0f;

			//Y��
	   	positon_control_loop->position_y =  (fp32)((RX_buf[6]-0x30)*100 + (RX_buf[7]-0x30)*10u + (RX_buf[8]-0x30)) - 100.0f;
      positon_control_loop->position_y = 240 - positon_control_loop->position_y;

	  }	
}

