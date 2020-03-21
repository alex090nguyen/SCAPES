/**
 * File Name: ArrayVariable.cpp
 * Class Name: ArrayVariable
 * Purpose: This class handles array variables.
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

#include "ArrayVariable.h"

/**
 * Purpose: ArrayVariable class constructor. Initializes attributes.
 * */
ArrayVariable::ArrayVariable(string n, int s)
{
  name = n;
  maxSize = s;
}


/**
 * Purpose: Get the name of this variable. Should also be the name of the object on which this is called.
 *
 * @return string
 * */
string ArrayVariable::getName()
{
  return name;
}


/**
 * Purpose: Set the value of this variable.
 *
 * @param index size_t&
 * @param value int&
 * @return void
 * */
void ArrayVariable::setElementValue(size_t& index, int& value)
{
  array[index] = value;
}


/**
 * Purpose: Get the value of this variable.
 *
 * @param i size_t&
 * @return int
 * */
int ArrayVariable::getElementValue(size_t& i)
{
  return array[i];
}


/**
 * Purpose: Get the size of the array.
 *
 * @return int
 * */
int ArrayVariable::getSize()
{
  return maxSize;
}
