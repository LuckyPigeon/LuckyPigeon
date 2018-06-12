//============================================================================
// Name        : jpeg.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

//#include <windows.h>

#include <stdio.h>		// sprintf(..), fopen(..)
#include <stdarg.h>     // So we can use ... (in dprintf)


#include "loadjpg.h"	// ConvertJpgFile(..)

#include "savejpg.h"    // SaveJpgFile(..)

/***************************************************************************/
/*                                                                         */
/* FeedBack Data                                                           */
/*                                                                         */
/***************************************************************************/

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



/***************************************************************************/
/*                                                                         */
/* Entry Point                                                             */
/*                                                                         */
/***************************************************************************/

int main(void){
  // Create a jpg from a bmp
  SaveJpgFile("smiley.bmp", "ex.jpg");

  // Create a bmp from a jpg
  ConvertJpgFile("ex.jpg", "out.bmp");



  return 0;
}

/*int __stdcall WinMain (HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
{

	// Create a jpg from a bmp
	//SaveJpgFile("smiley.bmp", "ex.jpg");

	// Create a bmp from a jpg
	ConvertJpgFile("smiley.jpg", "smiley.bmp");


	//ConvertJpgFile("cross.jpg", "cross.bmp");

	return 0;
}// End WinMain(..)*/



