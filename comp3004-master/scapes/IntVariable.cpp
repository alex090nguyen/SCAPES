/**
 * File Name: IntVariable.cpp
 * Class Name: IntVariable
 * Purpose: This class handles integer variables.
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

#include "IntVariable.h"

/**
 * Purpose: IntVariable class constructor. Initializes attributes.
 * 
 * @param n string
 * */
IntVariable::IntVariable(string n)
{
  name = n;
}


/**
 * Purpose: Get the name of this variable. Should also be the name of the object on which this is called.
 *
 * @return string
 * */
string IntVariable::getName()
{
  return name;
}


/**
 * Purpose: Set the value of this variable.
 *
 * @param i int
 * @return void
 * */
void IntVariable::setValue(int i)
{
  value = i;
}


/**
 * Purpose: Get the value of this variable.
 *
 * @return int
 * */
int IntVariable::getValue()
{
  return value;
}
