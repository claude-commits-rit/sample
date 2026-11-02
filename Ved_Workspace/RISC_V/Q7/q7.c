#include <stdio.h>
#include <vega/hal.h>
#include <vega/aries.h>
#include <vega/timer.h>

#define MILLIS(time)        (time * 100000)   

volatile uint8_t counter = 0, flag = 0;
uint8_t len = 0;
char out_buf[14];

int main(){

    htimer0.LoadCount = MILLIS(1000);

    char rx_data;

    char rx_buffer[26];

    GPIO_Init(GPIOB,RGB_BLUE,GPIO_OUT);
    TIMER_Init(&htimer0);
    TIMER_Start_IT(&htimer0);
    UART_Init(&huart0);

    GPIO_SetPin(GPIOB,RGB_BLUE);

    while(1)
    {
        if (UART_Receive(&huart0,&rx_data,1) == OK){

            if(rx_data == 'o')
            {   
                GPIO_ResetPin(GPIOB,RGB_BLUE);
                flag = 1;
                counter = 0;
                
                sprintf(rx_buffer,"Counter : %d\r\n",counter);
                UART_Transmit(&huart0,rx_buffer,26);

                rx_data = 'o';

            }
            if(rx_data == 's')
            {
                if(flag == 1 && counter < 5)
                {
                    sprintf(rx_buffer,"LED ON | Counter : %d\r\n",counter);
                }
                else if(flag == 0)
                {
                    sprintf(rx_buffer,"LED OFF | Counter : %d\r\n",counter);
                }
                UART_Transmit(&huart0,rx_buffer,26);

            }
        }        

        sprintf(rx_buffer,"Counter : %d\r\n",counter);
        UART_Transmit(&huart0,rx_buffer,26);
    }
}

void TIMER_ElapsedCallback(TIMER_Handle_t *htimer)
{
    if(flag == 1)
    {
        counter++;

        if(counter >= 5){
            flag = 0;
            counter = 0;
            GPIO_SetPin(GPIOB,RGB_BLUE);
        }
        
    }

}