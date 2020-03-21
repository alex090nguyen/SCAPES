/**
* File Name: Variable.h
* Class Name: Variable
* Purpose: Header file for Variable class
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

#ifndef VARIABLE_H
#define VARIABLE_H
using namespace std;
#include <string>
#include "Operand.h"


class Variable : public Operand
{
 public:
   Variable(string="");
   virtual string getName() = 0;

 protected:
   string name;
};

#endif
