/**
 * File Name: Label.cpp
 * Class Name: Label
 * Purpose: Class to handle labels
 *
 * Team: DORCS
 * Team Members:
 * 	- Alexander Nguyen (100908039)
 *	- Emmanuel Elite (100878873)
 *	- Kyle Bechtel (100979669)
 *	- Nem Zutkovic (101085982)
 *
 * Date: 12/05/2019
 * */

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "Label.h"

/**
 * Purpose: Constructor
 * */
Label::Label(){}


/**
 * Purpose: Constructor
 *
 * @param newName string&
 * @return void
 * */
Label::Label(string& newName)
{
  name = newName;
}


/**
 * Purpose: Destructor
 * */
//Label::~Label(){}

/**
 * Purpose: Serialize implementation
 *
 * @return string
 * */
string Label::serialize()
{
    return("<label>\n\t\t<name>" + name + "</name>\n\t</label>\n");
}
