/**
* File Name: IntVariable.h
* Class Name: IntVariable
* Purpose: Header file for IntVariable class
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

#ifndef INTVARIABLE_H
#define INTVARIABLE_H
using namespace std;
#include <string>
#include <Variable.h>


class IntVariable : public Variable
{
 public:
   IntVariable(string="");
   string getName();
   void setValue(int);
   int getValue();

 private:
   int value;
};

#endif
