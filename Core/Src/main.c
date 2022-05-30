#include <stm32f4xx.h>

void USART_init(void){
	RCC->AHB1ENR |= 0X1; // enable clock access to port A
	RCC->APB1ENR |= 0x20000; // enable clock access to USART pin (17)

	GPIOA->AFR[0] |= 0x7000;// enable alternate function for USART2 (PA3)
	USART->BRR = 0x8B; ;// set baudrate =115200 @16Mhz // 16/(8*2*115200)= 8.6805 10^-6 // 8=Mantissa (0x8) // DivFraction=0.6805*16=10.888~=11 (0xB) // TotalBRR=0x8B
	USART->CR1 = 0x4 ; // USART Reception enable (RX)
	USART->CR1 |= 0x2000;  //USART2 module enable
}
