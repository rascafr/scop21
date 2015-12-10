/**
 * \file viewcontroller.h
 * \brief Contient la définition des fonctions de gestion des boutons tactiles
 * \author François Leparoux
 * \version 1.1
 */

#ifndef APPLI_MYLIBS_VIEWCONTROLLER_H_
#define APPLI_MYLIBS_VIEWCONTROLLER_H_

#include "macro_types.h"
#include "stdint.h"

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
char virtual3DButton(const char *text, int x, int y, const uint16_t color, int pressed, int touchX, int touchY);


#endif /* APPLI_MYLIBS_VIEWCONTROLLER_H_ */
