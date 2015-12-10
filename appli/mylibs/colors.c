/**
 * \file colors.c
 * \brief Contient le code source des couleurs utilisées pour dessiner à l'écran, et quelques fonctions utiles
 * \author François Leparoux
 * \version 1.8
 */

#include "stm32f4xx_hal.h"
#include "colors.h"
#include "macro_types.h"

/**
 * \brief Permet de convertir une couleur encodée en RBG565 en RGB888 BMP
 * \param rawBuff la couleur en RGB565 à convertir
 * \param bmpBuff le tableau à remplir : 0 -> bleu, 1-> vert, 2->rouge (cf spécifications BMP)
 */
void Color565ToBMP (uint16_t rawBuff, uint8_t *bmpBuff) {

	bmpBuff[2] = (rawBuff >> 8) & 0xF8; // RED
	bmpBuff[1] = (rawBuff >> 3) & 0xFC; // GREEN
	bmpBuff[0] = rawBuff << 3; 		 	// BLUE
}
