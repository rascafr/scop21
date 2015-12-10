/**
 * \file sdcard.c
 * \brief Contient le code source la machine à état de gestion de la carte SD
 * \author François Leparoux
 * \version 1.4
 */

#include "sdcard.h"
#include "diskio.h"
#include "sd_diskio.h"
#include "stm32f4_sd.h"
#include "colors.h"
#include "bmpfile.h"
#include "macro_types.h"
#include "string.h"
#include "main.h"

//Definition de deux lecteurs physiques pour FATFS
PARTITION VolToPart[2] = {(PARTITION){0, 0}, (PARTITION){1, 1}};

char SDPath[4]; /* SD card logical drive path */
FATFS SDFatFs;

state_e status = IDLE;

/**
 * \brief Machine à état permettant la capture d'écran puis l'enregistrement sur carte SD
 */
void SDCardMachine (void) {

	FRESULT res = FR_OK;
	static FIL file;
	running_e ret;

	// Machine
	switch (status) {

	case IDLE: // Idle, no action, wait for BMP button press
		// Do nothing
		break;

	case INIT: // Init the SD Card Soft & Hard Interface

		if(BSP_SD_Init() == MSD_OK) {
			strcpy(text, "SD Card : module initialized");
			status = MOUNT;
		} else {
			strcpy(text, "SD Card : FAIL initialized");
			status = END_WITH_ERROR;
		}

		break;

	case MOUNT:{ // Mount the SD card
		FATFS * fs;
		Uint32 p2;
		status = END_WITH_ERROR;	//On fait la supposition que ça ne va pas marcher.... si tout se passe bien, on ira faire la suite.
		if (FATFS_LinkDriver(&SD_Driver, SDPath) != 0) {
			strcpy(text, "SD Card : NOT mounted");
		} else {
			res = f_mount(&SDFatFs, (TCHAR const*)SDPath, 0);
			if(res == FR_OK) {
				res = f_getfree("", (DWORD*)&p2, &fs);
				if (res == FR_OK) {
					sprintf(text, "SD Card : mounted (%s)", (fs->fs_type==FS_FAT16) ? "FAT16" : "FAT32");
					status = PREPARE_WRITE;
				}
			}
		}
		break;}

	case PREPARE_WRITE: // Wait message
		strcpy(text, "Please wait ...");
		status = WRITE_TEST_FILE;
		break;

	case WRITE_TEST_FILE:{ // Write a BMP
				UINT nb_to_write;
				UINT nb_written;

				// On enregistre les captures dans scope_screen.bmp
				res = f_open(&file, "scope_screen.bmp", FA_WRITE | FA_CREATE_ALWAYS | FA_OPEN_ALWAYS);
				if(res == FR_OK) {
					strcpy(text, "File ok");

					// Init LCD to (0,0)
					LCD_SetCursor(0,0);

					// Write Header
					f_write(&file,BMP_HEADER,BMP_HEADER_SIZE,&nb_written);

					// Read value for each pixel
					uint8_t buff[3]; // R,G,B channel (for each pixel)
					uint16_t rawBuff;
					int16_t rx, ry;

					// Compteur d'écriture des octets
					unsigned long total = nb_written;
					for (ry=239;ry>=0;ry--) {
						for (rx=0;rx<320;rx++) {

							LCD_SetCursor(rx, ry);

							// ATTENTION ! Pour être compatible avec la libraire stm32f4_lcd, modifier la fonction LCD_ReadRAM() !
							// Décommenter : LCD_CMD = SSD2119_RAM_DATA_REG;
							rawBuff = LCD_ReadRAM(); // Lecture d'un pixel

							Color565ToBMP(rawBuff, buff); // RBG565 (Pixel écran) -> RBG888 (BMP)

							f_write(&file,buff,3,&nb_written); // Ecriture du pixel dans la carte SD

							total+=nb_written;
						}
					}

					sprintf(text, "Data wrote : %lu bytes", total);
					f_close(&file);
				} else {
					strcpy(text, "FAIL to open Testfile");
				}

				status = IDLE;
				break;}
	}
}
