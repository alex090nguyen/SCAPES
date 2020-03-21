/**
* File Name: ArrayVariable.h
* Class Name: ArrayVariable
* Purpose: Header file for ArrayVariable class
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

#ifndef ARRAYVARIABLE_H
#define ARRAYVARIABLE_H
using namespace std;
#include <string>
#include <vector>
#include <Variable.h>


class ArrayVariable : public Variable
{
 public:
   ArrayVariable(string="", int=0);
   string getName();
   void setElementValue(size_t&, int&);
   int getElementValue(size_t&);
   int getSize();

 private:
   vector<int> array;
   int maxSize;
};

#endif
