#include <vega/hal.h>
#include <vega/aries.h>


int main(void)
{
    GPIO_Init(GPIOB,RGB_RED,GPIO_OUT);
    GPIO_Init(GPIOB,RGB_BLUE,GPIO_OUT);
    GPIO_Init(GPIOB,RGB_GREEN,GPIO_OUT);
    GPIO_Init(GPIOB,BTN0,GPIO_IN);
    GPIO_Init(GPIOB,BTN1,GPIO_IN);
    
    RGB_RED_RST;
    RGB_BLUE_RST;
    RGB_GREEN_RST;

    while(1)
    {
        if(GPIO_ReadPin(GPIOB,BTN0) == 0)
        {
            delayms(50);
            RGB_RED_SET;
            delayms(500);
            RGB_RED_RST;
            delayms(500);

            RGB_GREEN_SET;
            delayms(500);
            RGB_GREEN_RST;
            delayms(500);

            RGB_BLUE_SET;
            delayms(500);
            RGB_BLUE_RST;
            delayms(500); 
            
        }

        else if(GPIO_ReadPin(GPIOB,BTN1) == 0)
        {
            delayms(50);
            GPIO_SetPin(GPIOB,RGB_RED);
            delayms(200);
            GPIO_ResetPin(GPIOB,RGB_RED);
            
        }
    }
}