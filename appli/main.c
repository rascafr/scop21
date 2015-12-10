 /**
  * \file main.c
  * \brief Contient le code source de la tâche de fond (main)
  */

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "macro_types.h"
#include "main.h"
#include "config.h"
#include "lcd_display_form_and_text.h"
#include <string.h>
#include "stm32f4_gpio.h"
#include "stm32f4_lcd.h"
#include "demo_touchscreen.h"
#include "stdlib.h"

// Librairies custom
#include "mylibs/viewcontroller.h"
#include "mylibs/sdcard.h"
#include "mylibs/scope.h"
#include "mylibs/bmpfile.h"
#include "mylibs/dmaadc.h"
#include "mylibs/colors.h"

// Instructions de capture d'écran
char text[50];

// Flags utilisés pour la copie des données buffer depuis les interruptions DMA
char toggle = 0;
char enable_copy = 0;
char enable_copy2 = 0;
unsigned char counter = 0;

// Les tableaux d'affiche des mesure et des copies des signaux
volatile int8_t data_scope[BUFFER_SIZE] = {0};
int8_t data_scope_mem[BUFFER_SIZE] = {0};
volatile int8_t data_scope2[BUFFER_SIZE] = {0};
int8_t data_scope_mem2[BUFFER_SIZE] = {0};
int8_t data_scope_math[BUFFER_SIZE] = {0};

// Curseurs
int16_t cursorA, cursorB;
char textCursorA[8], textCursorB[8], textMaths[8];

// Flag de copie des channel du scope
char copyChannel1 = 0;
char copyChannel2 = 0;
char copyChannelMath = 0;

// Flag de sauvegarde de la capture d'écran
char sdCardFlag = 0;

/**
  * \brief  Programme principal : initialisations et tâche de fond
  * \func   int main(void)
  * \param  None
  * \retval None
  */
int main(void) {

	// Système
	HAL_Init();
	SYS_init();			//initialisation du systeme (horloge...)

	// Carte SD
	GPIO_Configure();	//Configuration des broches d'entree-sortie.
	TIMER2_run_1ms();	//Lancement du timer 2 a une periode d'1ms.

	// Ecran LCD et entrée tactile
	STM32f4_Discovery_LCD_Init();		//on initialise l'ecran LCD
	ScreenInitGraphics();
	TS_Init();

	// Périphériques DMA et ADC
	DmaAdcInit();
	DmaAdcStart();

	// Initialisation curseurs
	cursorA = 136-50; // Moitié haut
	cursorB = 136+50; // Moitié basse
	strcpy(textCursorA, "---");
	strcpy(textCursorB, "---");

	// Variables qui contiendront la lecture de l'écran tactile
	uint16_t touchX, touchY;
	bool_e changed = 1, buttonVal;

	// Variables utilisées pour l'initialisation des données, la boucle d'affichage des boutons, etc
	// TODO leur trouver un nom plus explicite ...
	int i, j;

	// Init data de l'oscillo à afficher (deux constantes) pour montrer que le système est allumé
	for (i=0;i<100;i++) {
		data_scope[i] = -10;
		data_scope2[i] = 10;
	}

	// Instruction de capture d'écran par défaut
	strcpy(text, "Press BMP button ...");

	// Boucle infinie de la tâche de fond
	while (1) {

		// Get touch screen value
		buttonVal = TS_Get_Touch(&touchX, &touchY);

		// Get change Event
		if (changed != buttonVal || toggle) {
			changed = buttonVal;
			toggle = 0;

			// Menu bar's buttons
			for (j=0;j<5;j++) {
				if(virtual3DButton(STR_BUTTONS_VALUES[j], 60*j+5, 5, COLORS_BUTTONS_VALUES[j], buttonVal, touchX, touchY)) {

					switch (j) {

					// Start
					case 0:
						enable_copy = !enable_copy;
						enable_copy2 = !enable_copy2;
						break;

					// Channel 1 memory copy
					// 0 : no display, 1 : copy data, 2 : display
					case 1:
						copyChannel1 = copyChannel1 == 0 ? 1 : 0;
						break;

					// Channel 2 memory copy
					// 0 : no display, 1 : copy data, 2 : display
					case 2:
						copyChannel2 = copyChannel2 == 0 ? 1 : 0;
						break;

					// Math channel memory copy
					// 0 : no display, 1 : copy data, 2 : display
					case 3:
						copyChannelMath = (copyChannelMath + 1) % 3;

						// On relance l'acquisition des signaux + calcul de la courbe
						switch (copyChannelMath) {

						case 0:
							strcpy(textMaths, " EMPTY ");
							break;
						case 1:
							strcpy(textMaths, "CH1-CH2");
							copyChannel1 = 1;
							copyChannel2 = 1;
							break;
						case 2:
							strcpy(textMaths, "CH1+CH2");
							copyChannel1 = 1;
							copyChannel2 = 1;
							break;
						}

						break;

					// BMP save as
					case 4:
						sdCardFlag = 1;
						break;
					}
				}
			}

			// Test SD card
			if (sdCardFlag) {

				// Réinit
				sdCardFlag = 0;

				// Start SD Card Interface
				status = INIT;
			}

			// Move cursors
			if (touchY > 36 && touchY < 236) {

				// Should we move cursor A or cursor B ?
				if (abs(cursorA - touchY) < abs(cursorB - touchY)) {
					cursorA = touchY;

					// Calc the new value for cursor A
					sprintf(textCursorA, "%.2fV", pixelToVolt(cursorA));

				} else {
					cursorB = touchY;

					// Calc the new value for cursor B
					sprintf(textCursorB, "%.2fV", pixelToVolt(cursorB));
				}
			}

			// Copy Channel 1 in memory (if asked)
			if (copyChannel1 == 1) {
				copyChannel1 = 2; // Enable copy display
				for (i=0;i<100;i++) {
					data_scope_mem[i] = data_scope[i];
				}
			}

			// Copy Channel 2 in memory (if asked)
			if (copyChannel2 == 1) {
				copyChannel2 = 2; // Enable copy display
				for (i=0;i<100;i++) {
					data_scope_mem2[i] = data_scope2[i];
				}
			}

			// Copy Channel Maths in memory (if asked)
			if (copyChannelMath != 0) {
				for (i=0;i<100;i++) {
					data_scope_math[i] = copyChannelMath == 1 ? data_scope[i] - data_scope2[i] : data_scope[i] + data_scope2[i];

					// Limites
					if (data_scope_math[i] > 98) data_scope_math[i] = 98;
					else if (data_scope_math[i] < -98) data_scope_math[i] = -98;
				}
			}

			// Draw scope data
			ScreenUpdate (  data_scope, copyChannel1, data_scope_mem, data_scope2, copyChannel2, data_scope_mem2, copyChannelMath, data_scope_math, textMaths,
							cursorA, textCursorA, cursorB, textCursorB);

			// Reprise de la capture ADC des deux voies (CH1 et CH2)
			DmaAdcStart();
		}

		// Mise à jour de la machine à états de la carte SD
		SDCardMachine();

		// Draw some text
		LCD_DisplayStringLine(220,10,(uint8_t *)text,GREY_80,GREY_30,LCD_NO_DISPLAY_ON_UART);
	}
}


/**
 * \brief Inteeruption qui Se déclenche lorsque le buffer du DMA2-stream4 est plein (CH1)
 */
void DMA2_Stream4_IRQHandler()
{
	unsigned char i;

	// On arrête l'acquisition DMA-ADC n°1 avant de traîter les données
	HAL_ADC_Stop_DMA(&g_AdcHandle);

	// Si on a demandé une aquisition
	if (enable_copy) {
		enable_copy = 0; // Clear flag acquisition du channel 1

		// On convertit les données du convertisseur 8 bits en valeurs exploitables : 100...-100
		for (i=0;i<BUFFER_SIZE;i++) {

			// Traitement data CH1
			data_scope[i] = (signed int)((float)(ADC_Buff_channel1[i]/1.28-100));

			// Pour ne pas que le signal dépasse de la zone affichable de l'écran, on met des limites à +98 et -98
			if (data_scope[i] > 98) data_scope[i] = 98;
			else if (data_scope[i] < -98) data_scope[i] = -98;
		}
	}

	// On lève le flag de l'interruption
    HAL_DMA_IRQHandler(&g_DmaHandle);
}

/**
 * \brief Inteeruption qui Se déclenche lorsque le buffer du DMA2-stream2 est plein (CH2)
 */
void DMA2_Stream2_IRQHandler() {

	unsigned char i;

	// On arrête l'acquisition DMA-ADC n°1 avant de traîter les données
	HAL_ADC_Stop_DMA(&g_AdcHandle2);

	// Si on a demandé une aquisition pour le channel 2
	if (enable_copy2) {
		enable_copy2 = 0;

		// On convertit les données du convertisseur 8 bits en valeurs exploitables : 100...-100
		for (i=0;i<BUFFER_SIZE;i++) {

			// Traitement data CH2
			data_scope2[i] = (signed int)((float)(ADC_Buff_channel2[i]/1.28-100));

			// Pour ne pas que le signal dépasse de la zone affichable de l'écran, on met des limites à +98 et -98
			if (data_scope2[i] > 98) data_scope2[i] = 98;
			else if (data_scope2[i] < -98) data_scope2[i] = -98;
		}
	}

	// On lève le flag de l'interruption du DMA2-stream2 (CH2)
	HAL_DMA_IRQHandler(&g_DmaHandle2);
}

/**
 * SD Card interrupt (NVIC) management
 */
void SDIO_IRQHandler(void) {
	BSP_SD_IRQHandler();
}

void DMA2_Stream3_IRQHandler(void) {
	BSP_SD_DMA_Rx_IRQHandler();
}

void DMA2_Stream6_IRQHandler(void) {
	BSP_SD_DMA_Tx_IRQHandler();
}

