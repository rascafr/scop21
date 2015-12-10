/**
 * \file timer.c
 * \brief Contient le code source des fonctions de gestion du Timer 3 (cadencement théorique de l'ADC). Non Utilisé.
 * \author Timé Kadel
 * \version 1.1
 */

#include "stm32f4xx_hal.h"
#include "stm32f4_gpio.h"
#include "stm32f4_uart.h"
#include "stm32f4_timer.h"
#include "stm32f4_sys.h"
#include "macro_types.h"
#include "timer.h"
#include "main.h"

static TIM_HandleTypeDef Tim3_Handle;

void TIMER3_init_for_1ms(void){

	// On active l'horloge du TIM3
	__HAL_RCC_TIM3_CLK_ENABLE();

	// On fixe les priorités des interruptions du timer2 PreemptionPriority = 0, SubPriority = 1 et on autorise les interruptions
	HAL_NVIC_SetPriority(TIM3_IRQn , 0, 1);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);

	// Time base configuration
	Tim3_Handle.Instance = TIM3; //On donne le timer 3 en instance à notre gestionnaire (Handle)
	Tim3_Handle.Init.Period = 1000; //period_us - période choisie en us : Min = 1us, Max = 65535 us
	Tim3_Handle.Init.Prescaler = 41; //divise notre clock de timer par 84 (afin d'augmenter la période maximale)
	Tim3_Handle.Init.ClockDivision = 0;
	Tim3_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;

	// On applique les paramètres d'initialisation
	HAL_TIM_Base_Init(&Tim3_Handle);

	// On autorise les interruptions
	HAL_TIM_Base_Start_IT(&Tim3_Handle);

	// On lance le timer3
	__HAL_TIM_ENABLE(&Tim3_Handle);

}

void TIMER3_run(void){
	__HAL_TIM_ENABLE(&Tim3_Handle);
}

void TIMER3_stop(void){
	__HAL_TIM_DISABLE(&Tim3_Handle);
}

void TIM3_IRQHandler(void)
{
	if(__HAL_TIM_GET_IT_SOURCE(&Tim3_Handle, TIM_IT_UPDATE) != RESET) {
		__HAL_TIM_CLEAR_IT(&Tim3_Handle, TIM_IT_UPDATE); //Acquittement TIMER3_user_handler_it_1ms();
		TIMER3_user_handler_it_1ms();
	}
}

void TIMER3_user_handler_it_1ms(void){

	//HAL_GPIO_WritePin(BLUE_LED, toggle);
	//toggle = !toggle;
}
