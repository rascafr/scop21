/**
 * \file sdcard.h
 * \brief Contient le prototype de la machine à état de gestion de la carte SD
 * \author François Leparoux
 * \version 1.4
 */

#ifndef APPLI_MYLIBS_SDCARD_H_
#define APPLI_MYLIBS_SDCARD_H_


/**
 * \union state_e
 * \brief Enumération des états possibles de la machine à états
 */
typedef enum {
	INIT = 0,
	MOUNT,
	PREPARE_WRITE,
	WRITE_TEST_FILE,
	READ_TEST_FILE,
	DELETE_TEST_FILE,
	END_WITH_ERROR,
	IDLE
} state_e;

/**
 * \brief Le statut courant de la machine à états de la carte SD
 */
extern state_e status;

/**
 * \brief Machine à état permettant la capture d'écran puis l'enregistrement sur carte SD
 */
void SDCardMachine (void);

#endif /* APPLI_MYLIBS_SDCARD_H_ */
