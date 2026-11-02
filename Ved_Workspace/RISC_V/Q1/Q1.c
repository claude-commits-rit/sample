#include <vega/hal.h>
#include <vega/aries.h>
#include <stdio.h>
#include <string.h>

#define NUM_DUTY_CYCLES   11

extern PWM_Handle_t hpwm1;



int main(void)
{
    GPIO_Init(GPIOB,RGB_RED,GPIO_OUT);

    RGB_RED_RST;

    int duty_cycles[] = {0,10,20,30,40,50,60,70,80,90,100};
    char tx_buffer[30];

    PWM_Init(&hpwm1);
    UART_Init(&huart0);

    PWM_Start(&hpwm1);

    int count = 0;
    


    while (1) {
        hpwm1.Channel->DUTY = duty_cycles[count];
        

        int n = snprintf(tx_buffer, sizeof(tx_buffer), "PWM Duty : %d\r\n", duty_cycles[count]);
        if(n > 0)
        {
            UART_Transmit(&huart0, tx_buffer, strlen(tx_buffer));
            delayms(100);
        }

        count = (count + 1) % NUM_DUTY_CYCLES;
        delayms(100);   
    }   
}