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

    TIMER_Init(&htimer0);
    TIMER_Start_IT(&htimer0);
    UART_Init(&huart0);

    while(1){

        if(flag){
            len = snprintf(out_buf, sizeof(out_buf), "Counter: %d\r\n", counter);
            UART_Transmit(&huart0, out_buf, len);

            if(counter == 10){
                counter = 0;
            }

            flag = 0;
        }

    }
}

void TIMER_ElapsedCallback(TIMER_Handle_t *htimer)
{
    counter++;
    flag = 1;

}