/***************************************************************************/
/*                                                                         */
/*  File: main.cpp                                                         */
/*  Autor: bkenwright@xbdev.net                                            */
/*  URL: www.xbdev.net                                                     */
/*                                                                         */
/***************************************************************************/
/*
	Jpeg File Format Explained
*/
/***************************************************************************/

#include <stdio.h>		// sprintf(..), fopen(..)
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>     // So we can use ... (in dprintf)
#include <string.h>		// memset(..)
#include <math.h>		// sqrt(..), cos(..)

#include "loadjpg.h"	// ConvertJpgFile(..)
#include "loadjpg.c"

#include "savejpg.h"
#include "savejpg.c"

extern void dprintf(const char *fmt, ...);


//Saving debug information to a log file
void dprintf(const char *fmt, ...) 
{
	va_list parms;
	char buf[256];

	// Try to print in the allocated space.
	va_start(parms, fmt);
	vsprintf (buf, fmt, parms);
	va_end(parms);

	// Write the information out to a txt file
	FILE *fp = fopen("output.txt", "a+");
	fprintf(fp, "%s", buf);
	fclose(fp);

}// End dprintf(..)

void main()
{

	// Create a jpg from a bmp
	SaveJpgFile("smiley.bmp", "smiley-1.jpg");

	// Create a bmp from a jpg
	ConvertJpgFile("smiley-1.jpg", "smiley-1.bmp");

	// Create a jpg from a bmp
	// SaveJpgFile("cross.bmp", "cross.jpg");
	// Create a bmp from a jpg
    // ConvertJpgFile("cross.jpg", "cross.bmp");

	return 0;
}


