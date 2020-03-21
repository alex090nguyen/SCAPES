/**
 * File Name: JLessStmt.cpp
 * Class Name: JLessStmt
 * Purpose: Class to handle JLess statement
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

#include "JLessStmt.h"


/**
 * Purpose: Constructor
 * */
JLessStmt::JLessStmt(){}


/**
 * Purpose: Destructor
 * */
JLessStmt::~JLessStmt(){}


/**
 * Purpose: Compile implementation
 *
 * @param instr string&
 * @return void
 * */
void JLessStmt::compile(string& instr)
{
    size_t pos;
    string s = instr;

    // parse statement into
    // label
    pos = s.find(":");
    if (pos != string::npos) {
        string stringLabel = instr.substr(0, pos);
        Label* newLabel = new Label(stringLabel);
        label = newLabel;
        s.erase(0, pos + 1); //":".length());
        trim(s);
        hasLabel = true;
    }

    // statement
    pos = s.find (" ");
    s.erase(0, pos + 1); //":".length());

    // operand
    Operand* newOperand = new Operand(s);
    operand_one = newOperand;
    hasOpOne = true;

    return;
}


/**
 * Purpose: Run
 *
 * @param vector<Statement*>&
 * @return int
 * */
int JLessStmt::run(vector<Statement*>&)
{
    cout << "Ran JLessStmt" << endl;
    return 5;
}


/**
 * Purpose: Run method inherited from parent class
 *
 * @return void
 * */
void JLessStmt::run()
{
  cout << "Ran JLessStmt" << endl;
}


/**
 * Purpose: serialize implementation
 *
 * @return string
 * */
string JLessStmt::serialize()
{
    if (hasLabel){
        return("<jls>\n\t"
            + operand_one->serialize()
            + "\t" + label->serialize()
            + "</jls>\n");
    } else {
        return("<jls>\n\t"
            + operand_one->serialize()
            + "</jls>\n");
    }
}
