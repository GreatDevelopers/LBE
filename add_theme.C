/*******************************************************

FileName: add_theme.C

Description: Holds the definition of function to 
             read theme file

Author: Shaina Sabarwal, Inderpreet Singh, Gauravjeet Singh

License GNU GPL V3

***********************************************************/

#include "add_theme.h"

//!definition of handleThemeFile function.
/*!
The function handleThemeFile reads the content of file themes/yanni/loop.lml and put it into a string tempText.
*/
void handleThemeFile() 
{
	ifstream loop("themes/yanni/loop.lml");
	getline(loop, loopTemplate, '\0');

        ifstream main("themes/yanni/main.lml");
        getline(main, mainTemplate, '\0');

        ifstream post("themes/yanni/post.lml");
        getline(post, postTemplate, '\0');
}

