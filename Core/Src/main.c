#include <stm32f4xx.h>

void USART_init(void);
char USART2_read(void);
void LED_play(int val);
void delayMs(int delay);

int main(void){

	RCC->AHB1ENR |= 0x1; // ENABLE Clock access to port A
	GPIOA->MODER |= 0x40000000; // Set pin 15 as OUTPUT
	USART_init();
	char ch;
	while(1){
		ch = USART2_read();
		LED_play(ch);
	}
}

void USART_init(void){
	RCC->AHB1ENR |= 0X1; // enable clock access to port A
	RCC->APB1ENR |= 0x20000; // enable clock access to USART pin (17)

	GPIOA->AFR[0] |= 0x7000;// enable alternate function for USART2 (PA3)
	USART2->BRR = 0x8B; // set baudrate =115200 @16Mhz // 16/(8*2*115200)= 8.6805 10^-6 // 8=Mantissa (0x8) // DivFraction=0.6805*16=10.888~=11 (0xB) // TotalBRR=0x8B
	USART2->CR1 = 0x4 ; // USART Reception enable (RX)
	USART2->CR1 |= 0x2000;  //USART2 module enable
}
 char USART2_read(void){
	 while(!(USART2->SR & 0x20)){  // wait until character arrives
		 return USART2->DR;
	 }
 }

 void LED_play(int val){
	 val %= 16;
	 for(;val>0;val--){
		 GPIOA->BSRR = 0x8000;  // blink LED6
		 delayMs(100);
		 GPIOA->BSRR = 0x80000000; // led turned off
		 delayMs(100);
	 }
	 delayMs(400);

 }
void delayMs(int delay){
	int i;
	for(; delay>0;delay--){
		for(i=0; i<3195; i++);
	}
}
