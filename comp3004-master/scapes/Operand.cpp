/**
 * File Name: Operand.cpp
 * Class Name: Operand
 * Purpose: Class to handle Operand
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

#include "Operand.h"

/**
 * Purpose: Constructor
 * */
Operand::Operand(){}


/**
 * Purpose: Constructor
 *
 * @param newName string
 * */
Operand::Operand(string newName)
{
  name = newName;
}


/**
 * Purpose: Serialize implementation
 *
 * @return string
 * */
string Operand::serialize()
{
    return("<operand>\n\t\t<name>" + name + "</name>\n\t</operand>\n");
}


/**
 * Purpose: get name
 *
 * @return string
 * */
int Operand::getRealValue()
{
    return realValue; 
}


/**
 * Purpose: Set real value
 *
 * @param in int
 * @return void
 * */
void Operand::setRealValue(int in)
{
    realValue = in;
}


/**
 * Purpose: get name
 *
 * @return string
 * */
string Operand::getName()
{
    return name;
}
