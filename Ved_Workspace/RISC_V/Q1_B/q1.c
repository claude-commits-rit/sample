#include <stdio.h>
#include <vega/hal.h>
#include <vega/aries.h>

void UART_Transmit_User(char buff[], uint8_t counter){

    int n = snprintf(buff, 15,"counter : %d\r\n", counter);

    if (n > 0){
        UART_Transmit(&huart0, buff, 15);
        delayms(50);
    }

}

int main(){

    UART_Init(&huart0);

    uint8_t counter = 0;

    char rx_byte;

    char buff[15];

    while(1){

        UART_Receive(&huart0, &rx_byte, 1);

        if(rx_byte == '+' && counter < 20){
            counter++;
            UART_Transmit_User(buff, counter);
        } else if(rx_byte == '-' && counter > 0){
            counter--;
            UART_Transmit_User(buff, counter);
        } else if(rx_byte == 'r'){
            counter = 0;
            UART_Transmit_User(buff, counter);
        } else {
            UART_Transmit(&huart0, "Limit Reached!\r\n", 15);
            delayms(50);
        }
    }
}