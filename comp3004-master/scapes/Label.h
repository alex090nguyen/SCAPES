 /**
 * File Name: Label.h
 * Class Name: Label
 * Purpose: Header file for Label class
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

#ifndef LABEL_H
#define LABEL_H
using namespace std;
#include <string>
#include "Operand.h"

class Label : public Operand
{
  public:
    Label();
    Label(string&);
    string serialize();
    string name;

  private:
    //string name;

};

#endif
