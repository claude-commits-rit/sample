#include <vega/hal.h>
#include <vega/aries.h>
#include <stdio.h>
#include <vega/uart.h>

int main(void)
{
    char rx_byte;
    int count = 0;

    char buffer[19];

    UART_Init(&huart0);

    while(1)
    {
        UART_Receive(&huart0,&rx_byte,1);

        if(rx_byte == 'a' || rx_byte == 'e' || rx_byte == 'i' || rx_byte == 'o' || rx_byte == 'u' ||
           rx_byte == 'A' || rx_byte == 'E' || rx_byte == 'I' || rx_byte == 'O' || rx_byte == 'U')
        {
           count++;
        }

        UART_Transmit(&huart0,&rx_byte,1);

        int n = snprintf(buffer,19,"Vowel Count : %d\r\n",count);

        if(n > 0)
        {
            UART_Transmit(&huart0, "\r\n", 3);
            UART_Transmit(&huart0,buffer,19);
        }

    }
}