/*******************************************************

FileName: add_theme.h

Description: Holds the declaration of function to 
	     read theme file

Author: Shaina Sabarwal, Inderpreet Singh, Gauravjeet Singh

License GNU GPL V3

***********************************************************/

#ifndef _ADD_THEME
#define _ADD_THEME

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

//! string for storing the contents of loop file
extern string loopTemplate;
//! string for storing the contents of main file
extern string mainTemplate;
//! string for storing the contents of post file
extern string postTemplate;

void handleThemeFile();

#endif
