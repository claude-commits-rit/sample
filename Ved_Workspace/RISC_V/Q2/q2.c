#include <stdio.h>
#include <vega/hal.h>
#include <vega/aries.h>

int main(){

    GPIO_Init(GPIOB, RGB_RED, GPIO_OUT);
    GPIO_Init(GPIOB, BTN0, GPIO_IN);

    GPIO_ResetPin(GPIOB, RGB_RED);

    while(1){

        if(GPIO_ReadPin(GPIOB, BTN0) == 0){
            GPIO_TogglePin(GPIOB, RGB_RED);
            delayms(250);
        } else {
            GPIO_TogglePin(GPIOB, RGB_RED);
            delayms(1000);
        }
    }

}