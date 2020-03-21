 /**
 * File Name: Statement.h
 * Class Name: Statement
 * Purpose: Header file for Statement class
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

#ifndef STATEMENT_H
#define STATEMENT_H
using namespace std;
#include <string>
#include <vector>
#include "Operand.h"
#include "Label.h"

class Statement
{
  public:
    Statement();
    virtual ~Statement();
    void clean();
    virtual void compile(string&) = 0;
    virtual string serialize() = 0;
    virtual void run();
    virtual int run(vector<Statement*>&);
    string getLabel();
    void setLabel(Label*);
    void teststmtcreation();
    void trim(string& s); //removes leading whitespaces from string
    Operand* operand_one;
    Operand* operand_two;
    //these attributes had to be moved here in order for the statemtn vector to work in the run method
    int live; // used for knowing if a variable can be referenced
    void setLive(int in) {live = in;}
    virtual void setArray(int, int) {}
    virtual int getArray(int) {}


  protected:
    Label* label;
    //Operand* op[];
    bool hasLabel = false;
    bool hasOpOne = false;
    bool hasOpTwo = false;
};

#endif
