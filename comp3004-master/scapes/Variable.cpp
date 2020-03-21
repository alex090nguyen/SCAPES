/**
 * File Name: Variable.cpp
 * Class Name: Variable
 * Purpose: This class handles variables.
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
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

#include "Variable.h"

/**
 * Purpose: Variable class constructor. Initializes attributes.
 * 
 * @param n string
 * */
Variable::Variable(string n)
{
  name = n;
}


/**
 * Purpose: Get the name of this variable. Should also be the name of the object on which this is called.
 *
 * @return string
 * */
string Variable::getName()
{
  return name;
}
