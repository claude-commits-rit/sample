#include <stdio.h>
#include <vega/hal.h>
#include <vega/aries.h>
#include <vega/uart.h>

int main(){

    UART_Init(&huart0);

    char rx_buf[3];

    char rx_byte;
    
    uint8_t i = 0;

    char msg[] = "Enter Expression in the form Op1 Op2 Operand\n";

    UART_Transmit(&huart0, msg, sizeof(msg) - 1);

    while(1){        

        UART_Receive(&huart0, &rx_byte, 1);

        if(rx_byte == '\r' || rx_byte == '\n'){

            UART_Transmit(&huart0, "\r\n", 2);

            if((i == 3 && (rx_buf[0] <= '9' && rx_buf[0] >= '0')) 
               && (rx_buf[1] <= '9' && rx_buf[1] >= '0') 
               && (rx_buf[2] == '+' || rx_buf[2] == '-')){

                int op1 = rx_buf[0] - '0';
                int op2 = rx_buf[1] - '0';
                int calc_result = 0;
                char out_buf[16];
                int len = 0;

                if (rx_buf[2] == '+') {
                    calc_result = op1 + op2;
                } else {
                    calc_result = op1 - op2;
                }

                len = snprintf(out_buf, sizeof(out_buf), "Result: %d\r\n", calc_result);
                UART_Transmit(&huart0, out_buf, len);

            } else {
                UART_Transmit(&huart0, "Invalid Expression\r\n", 20);
            } 

            i = 0;

        } else {

            UART_Transmit(&huart0, &rx_byte, 1);    
            if (i < 3){
                rx_buf[i] = rx_byte;
                i++;
            }
        }
    
    }
}