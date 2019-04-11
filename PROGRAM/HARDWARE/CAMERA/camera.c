#include "camera.h" 

void camera_Init( uint8_t *camera_RX_buf1 , uint8_t *camera_RX_buf2 , uint16_t camera_buf_num)
{    	 
  /* -------------- Enable Module Clock Source ----------------------------*/
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_DMA1, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

        RCC_APB2PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB1Periph_USART2, DISABLE);

        GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);                                                    
        {
                GPIO_InitTypeDef     GPIO_InitStructure;
                USART_InitTypeDef    USART_InitStructure;
					
                GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
                GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
                GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
                GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
                GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
                GPIO_Init(GPIOD, &GPIO_InitStructure);

                USART_DeInit(USART2);

                USART_InitStructure.USART_BaudRate = 115200;
                USART_InitStructure.USART_WordLength = USART_WordLength_8b;
                USART_InitStructure.USART_StopBits = USART_StopBits_1;
                USART_InitStructure.USART_Parity = USART_Parity_No;
                USART_InitStructure.USART_Mode = USART_Mode_Rx;
                USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
                USART_Init(USART2, &USART_InitStructure);

                USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);

                USART_ClearFlag(USART2, USART_FLAG_IDLE);
								
                USART_ITConfig(USART2, USART_IT_IDLE , ENABLE);

                USART_Cmd(USART2, ENABLE);
        }

        /* -------------- Configure NVIC ---------------------------------------*/
        {
                NVIC_InitTypeDef     NVIC_InitStructure;
					
                NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
                NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
                NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
                NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
                NVIC_Init(&NVIC_InitStructure);
        }

        /* -------------- Configure DMA -----------------------------------------*/
        {
                DMA_InitTypeDef     DMA_InitStructure;
					
                DMA_DeInit(DMA1_Stream5);

                DMA_InitStructure.DMA_Channel = DMA_Channel_4;
                DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (USART2->DR);
                DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)camera_RX_buf1;
                DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
                DMA_InitStructure.DMA_BufferSize = camera_buf_num;
                DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
                DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
                DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
                DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
                DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
                DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
                DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
                DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
                DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
                DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
                DMA_Init(DMA1_Stream5, &DMA_InitStructure);
					
                DMA_DoubleBufferModeConfig(DMA1_Stream5, (uint32_t)camera_RX_buf2, DMA_Memory_0);
                DMA_DoubleBufferModeCmd(DMA1_Stream5, ENABLE);
								
                DMA_Cmd(DMA1_Stream5, DISABLE); //Add a disable
                DMA_Cmd(DMA1_Stream5, ENABLE);
        }
}





