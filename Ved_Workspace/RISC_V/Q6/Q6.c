#include <vega/hal.h>
#include <vega/aries.h>
#include <stdio.h>

int main(void)
{
    char rx_byte;
    int count = 0;

    char buffer[19];

    GPIO_Init(GPIOB,BTN0,GPIO_IN);
    GPIO_Init(GPIOB,RGB_GREEN,GPIO_OUT);

    UART_Init(&huart0);

    GPIO_SetPin(GPIOB,RGB_GREEN);

    while(1)
    {
        if(GPIO_ReadPin(GPIOB,BTN0) == 0){

            delayms(50);
            while(GPIO_ReadPin(GPIOB, BTN0) == 0);
            delayms(50);

            count++;

            sprintf(buffer,"Button Count : %d\r\n",count);
            UART_Transmit(&huart0,buffer,26);

            if(count % 5 == 0){
                GPIO_ResetPin(GPIOB,RGB_GREEN);
                delayms(50);
                GPIO_SetPin(GPIOB,RGB_GREEN);

                delayms(100);
                
                GPIO_ResetPin(GPIOB,RGB_GREEN);
                delayms(50);
                GPIO_SetPin(GPIOB,RGB_GREEN);
            }

            if(count >= 20){
                count = 0;
            }

        }
        

    }
}