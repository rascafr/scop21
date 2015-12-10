/**
 * \file viewcontroller.c
 * \brief Contient le code source des fonctions de gestion des boutons tactiles
 * \author François Leparoux
 * \version 1.1
 */

#include "viewcontroller.h"
#include "stm32f4_lcd.h"
#include "lcd_display_form_and_text.h"
#include "stdio.h"
#include <string.h>

/**
 * \brief Dessine un bouton en 3D (style Windows 98)
 * Largeur et hauteur sont calculés automatiquement en fonction de la chaîne de caractères
 *
 * \param text La chaîne de caractères à écrire à l'écran
 * \param x La position horizontale où placer le texte
 * \param y La position verticale où placer le texte
 * \param color La couleur en RGB565 du bouton
 * \param pressed L'état de la dalle tactile (en contact d'un doigt ou non)
 * \param touchX La position X du doigt utilisateur sur la dalle tactile
 * \param touchY La position Y du doigt utilisateur sur la dalle tactile
 *
 * \return 1 si d'après les coordonnées de l'évenement tactile, le bouton a été appuyé, 0 sinon
 */
char virtual3DButton(const char *text, int x, int y, const uint16_t color, int pressed, int touchX, int touchY) {

	// On récupère les données de la police courante
	char fontWidth = LCD_GetFont()->Width;
	char fontHeight = LCD_GetFont()->Height;

	// On calcule la taille du bouton
	char margin = 5; // 5 px de marge
	unsigned char buttonWidth = strlen(text) * fontWidth + margin * 2;
	unsigned char buttonHeight = fontHeight + margin * 2;

	// On calcule la position X et Y du texte du bouton en tenant compte des marges
	unsigned char textX = x + margin;
	unsigned char textY = y + margin;

	// L'évenement tactile est-il dans la zone du bouton ?
	char isTouched = (touchX >= x && touchX <= x+buttonWidth) && (touchY >= y && touchY <= y+buttonHeight) && pressed;

	// On dessine le bouton : les conditions ternaires sur les couleurs permettent de gagner en lisibilité (et de supprimer la redondance du code)
	LCD_DrawLine(x, y, buttonWidth-1, LCD_DIR_HORIZONTAL, isTouched ? LCD_COLOR_BLACK:LCD_COLOR_WHITE);
	LCD_DrawLine(x, y, buttonHeight-1, LCD_DIR_VERTICAL, isTouched ? LCD_COLOR_BLACK:LCD_COLOR_WHITE);
	LCD_DrawFullRect(x+1, y+1, buttonWidth-2, buttonHeight-3, color, color);
	LCD_DrawLine(x+1, isTouched ? y+1 : y+buttonHeight-2, buttonWidth-2, LCD_DIR_HORIZONTAL, 0x8451);
	LCD_DrawLine(isTouched ? x+1 : x+buttonWidth-2, y+1, buttonHeight-2, LCD_DIR_VERTICAL, 0x8451);
	LCD_DrawLine(x, y+buttonHeight-1, buttonWidth, LCD_DIR_HORIZONTAL, isTouched ? LCD_COLOR_WHITE:LCD_COLOR_BLACK);
	LCD_DrawLine(x+buttonWidth-1, y, buttonHeight, LCD_DIR_VERTICAL, isTouched ? LCD_COLOR_WHITE:LCD_COLOR_BLACK);
	LCD_DisplayStringLine(textY,textX,(uint8_t *)text,LCD_COLOR_BLACK,color,LCD_NO_DISPLAY_ON_UART);

	return isTouched;
}
