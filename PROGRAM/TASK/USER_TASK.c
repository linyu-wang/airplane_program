#include "USER_TASK.h"

#include "FreeRTOS.h"
#include "task.h"

#include "led.h"


//�û������� 
void user_task(void *pvParameters)
{
    while(1)
    {
        LED0=~LED0;
        LED1=~LED1;		
        vTaskDelay(1000);
    }
}   



