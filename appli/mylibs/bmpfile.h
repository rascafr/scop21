/**
 * \file bmpfile.h
 * \brief Contient la définition du header Bitmap utilisé pour que l'image soit reconnue sous Windows / Unix
 * \author François Leparoux
 * \version 1.2
 */

#ifndef APPLI_MYLIBS_BMPFILE_H_
#define APPLI_MYLIBS_BMPFILE_H_

// BMP File Header
#define BMP_HEADER_SIZE 54

extern const unsigned char BMP_HEADER[BMP_HEADER_SIZE];

#endif /* APPLI_MYLIBS_BMPFILE_H_ */
