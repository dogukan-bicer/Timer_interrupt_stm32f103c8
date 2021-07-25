#include "stm32f10x.h"
 
int main(void)
{
	RCC->APB2ENR |= (1<<2); /// port a aktif
	GPIOA->CRL &= 0xFFFF0FFF; /// pin 3 ü resetle
	GPIOA->CRL |= 0x00003000; /// pin 3 ü çikis olarak ayarla
 
	
	__disable_irq();
	RCC->APB1ENR|=(1<<0);// timer2 aktif
	TIM2->ARR = 0xffff;  // maksimum arr degeri (AUTO RELOAD)
	TIM2->PSC = 54;  // 10hz frekans 54
	TIM2->DIER = 0x1;//güncelleme sirasinda kesintileri etkinlestir (OVERFLOW) 
	TIM2->CR1 = 0x1; // enable timer by setting TIMx_CR1.CEN
	NVIC_EnableIRQ(TIM2_IRQn); //TIMx_CR1.CEN'i ayarlayarak zamanlayiciyi etkinlestirin 
	__enable_irq();
	
	while(1)
	{
		
	}
	
}
 
void TIM2_IRQHandler()
{
	TIM2->SR =~0x01;//interrupt bayragi aktif
	GPIOA->ODR ^=0x0008;//toggle pa3
}
