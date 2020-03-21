 /**
 * File Name: Operand.h
 * Class Name: Operand
 * Purpose: Header file for Operand class
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

#ifndef OPERAND_H
#define OPERAND_H
using namespace std;
#include <string>

class Operand
{
  public:
    Operand();
    Operand(string newName);
    string name;
    string serialize();
    int getRealValue();
    void setRealValue(int);
    string getName();

  private:
    int realValue;

};

#endif
