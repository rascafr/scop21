/**
 * \file dmaadc.c
 * \brief Contient le code source qui permet l'initialisation et la gestion des périphériques ADC et DMA
 * \author Timé Kadel
 * \version 2.5
 */

#include "main.h"
#include "timer.h"
#include "dmaadc.h"
#include "stm32f4xx_hal.h"
#include "stm32f4_gpio.h"
#include "stm32f4_uart.h"
#include "stm32f4_timer.h"
#include "stm32f4_sys.h"
#include "macro_types.h"

volatile uint32_t ADC_Buff_channel1[BUFFER_SIZE*2];
volatile uint32_t ADC_Buff_channel2[BUFFER_SIZE*2];

// Handler local
volatile ADC_HandleTypeDef g_AdcHandle, g_AdcHandle2;
volatile DMA_HandleTypeDef g_DmaHandle, g_DmaHandle2;


/**
 * \brief Initialise les périphériques ADC et DMA pour qu'ils fonctionnent ensemblent
 */
void DmaAdcInit (void) {

	// Initialisation Timer
	TIMER3_init_for_1ms();

	// Initialisation ADC
	ConfigureADC();

	// Initialisation DMA
	ConfigureDMA();

}

/**
 * \brief Lance les périphériques
 */
void DmaAdcStart (void) {

	// Lancement Timer3
	TIMER3_run();

	// DMA & ADC
	HAL_ADC_Start_DMA(&g_AdcHandle, ADC_Buff_channel1, BUFFER_SIZE*2);
	HAL_ADC_Start_DMA(&g_AdcHandle2, ADC_Buff_channel2, BUFFER_SIZE*2);
}

/**
 * \brief Coupe l'acquisition
 */
void DmaAdcStop (void) {

	// DMA & ADC
	//HAL_ADC_Stop_DMA(&g_AdcHandle);
}

/**
 * \brief Configure le périphérique ADC
 */
void ConfigureADC (void) {
	GPIO_InitTypeDef gpioInit, gpioInit2;

	__GPIOC_CLK_ENABLE();
	__ADC1_CLK_ENABLE();
	__ADC2_CLK_ENABLE();

	// CH1
	gpioInit.Pin = GPIO_PIN_1;
	gpioInit.Mode = GPIO_MODE_ANALOG;
	gpioInit.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &gpioInit);

	// CH2
	gpioInit2.Pin = GPIO_PIN_0;
	gpioInit2.Mode = GPIO_MODE_ANALOG;
	gpioInit2.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &gpioInit2);

	HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(ADC_IRQn);

	ADC_ChannelConfTypeDef adcChannel, adcChannel2;

	// CH1
	g_AdcHandle.Instance = ADC1;
	g_AdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
	g_AdcHandle.Init.Resolution = ADC_RESOLUTION_8B;
	g_AdcHandle.Init.ScanConvMode = DISABLE;
	g_AdcHandle.Init.ContinuousConvMode = ENABLE;
	g_AdcHandle.Init.DiscontinuousConvMode = DISABLE;
	g_AdcHandle.Init.NbrOfDiscConversion = 0;
	g_AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	g_AdcHandle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_CC1;
	g_AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	g_AdcHandle.Init.NbrOfConversion = 1;
	g_AdcHandle.Init.DMAContinuousRequests = ENABLE;
	g_AdcHandle.Init.EOCSelection = EOC_SINGLE_CONV;

	// CH2
	g_AdcHandle2.Instance = ADC2;
	g_AdcHandle2.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
	g_AdcHandle2.Init.Resolution = ADC_RESOLUTION_8B;
	g_AdcHandle2.Init.ScanConvMode = DISABLE;
	g_AdcHandle2.Init.ContinuousConvMode = ENABLE;
	g_AdcHandle2.Init.DiscontinuousConvMode = DISABLE;
	g_AdcHandle2.Init.NbrOfDiscConversion = 0;
	g_AdcHandle2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	g_AdcHandle2.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_CC1;
	g_AdcHandle2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	g_AdcHandle2.Init.NbrOfConversion = 1;
	g_AdcHandle2.Init.DMAContinuousRequests = ENABLE;
	g_AdcHandle2.Init.EOCSelection = EOC_SINGLE_CONV;

	// Init
	HAL_ADC_Init(&g_AdcHandle);
	HAL_ADC_Init(&g_AdcHandle2);

	// Channel 1
	adcChannel.Channel = ADC_CHANNEL_11;
	adcChannel.Rank = 1;
	adcChannel.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	adcChannel.Offset = 0;

	// Channel 2
	adcChannel2.Channel = ADC_CHANNEL_10;
	adcChannel2.Rank = 1;
	adcChannel2.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	adcChannel2.Offset = 0;

	// Crash test
	if (HAL_ADC_ConfigChannel(&g_AdcHandle, &adcChannel) != HAL_OK || HAL_ADC_ConfigChannel(&g_AdcHandle2, &adcChannel2) != HAL_OK) {
		asm("bkpt 255");
	}
}



/**
 * \brief Configure le périphérique DMA
 */
void ConfigureDMA (void) {
    __DMA2_CLK_ENABLE();

	// Stream 4 : Channel 0 -> CH1
	g_DmaHandle.Instance = DMA2_Stream4;
	g_DmaHandle.Init.Channel  = DMA_CHANNEL_0;
	g_DmaHandle.Init.Direction = DMA_PERIPH_TO_MEMORY;
	g_DmaHandle.Init.PeriphInc = DMA_PINC_DISABLE;
	g_DmaHandle.Init.MemInc = DMA_MINC_ENABLE;
	g_DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	g_DmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
	g_DmaHandle.Init.Mode = DMA_CIRCULAR;
	g_DmaHandle.Init.Priority = DMA_PRIORITY_HIGH;
	g_DmaHandle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	g_DmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	g_DmaHandle.Init.MemBurst = DMA_MBURST_SINGLE;
	g_DmaHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;

	// Stream 2 : Channel 1 -> CH2
	g_DmaHandle2.Instance = DMA2_Stream2;
	g_DmaHandle2.Init.Channel  = DMA_CHANNEL_1;
	g_DmaHandle2.Init.Direction = DMA_PERIPH_TO_MEMORY;
	g_DmaHandle2.Init.PeriphInc = DMA_PINC_DISABLE;
	g_DmaHandle2.Init.MemInc = DMA_MINC_ENABLE;
	g_DmaHandle2.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	g_DmaHandle2.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
	g_DmaHandle2.Init.Mode = DMA_CIRCULAR;
	g_DmaHandle2.Init.Priority = DMA_PRIORITY_HIGH;
	g_DmaHandle2.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	g_DmaHandle2.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	g_DmaHandle2.Init.MemBurst = DMA_MBURST_SINGLE;
	g_DmaHandle2.Init.PeriphBurst = DMA_PBURST_SINGLE;

	// Init
	HAL_DMA_Init(&g_DmaHandle);
	HAL_DMA_Init(&g_DmaHandle2);

	// Link ADC's and DMA's
	__HAL_LINKDMA(&g_AdcHandle, DMA_Handle, g_DmaHandle);
	__HAL_LINKDMA(&g_AdcHandle2, DMA_Handle, g_DmaHandle2);

	HAL_NVIC_SetPriority(DMA2_Stream4_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream4_IRQn);
	HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 1, 1);
	HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
}

/**
 * \brief Interruption qui se déclenche lorsque l'acquisition ADC est terminée
 */
void ADC_IRQHandler() {
	HAL_ADC_IRQHandler(&g_AdcHandle);
	HAL_ADC_IRQHandler(&g_AdcHandle2);
}

// Not used
/*
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{
	//g_ADCValue = HAL_ADC_GetValue(AdcHandle);
	//g_MeasurementNumber += ADC_BUFFER_LENGTH;
	HAL_ADC_IRQHandler(&g_AdcHandle);
	HAL_GPIO_WritePin(GREEN_LED, toggle);
	toggle = ~toggle;
}
*/

