/**
 * File Name: JumpStmt.cpp
 * Class Name: JumpStmt
 * Purpose: Class to handle jmp statement
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

#include "JumpStmt.h"

/**
 * Purpose: Constructor
 * */
JumpStmt::JumpStmt(){}


/**
 * Purpose: Destructor
 * */
JumpStmt::~JumpStmt(){}


/**
 * Purpose: Compile implementation
 *
 * @param instr string&
 * @return void
 * */
void JumpStmt::compile(string& instr)
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
int JumpStmt::run(vector<Statement*>&)
{
    return 2;
}


/**
 * Purpose: Run method inherited from parent class
 *
 * @return void
 * */
void JumpStmt::run()
{
  cout << "Ran JumpStmt" << endl;
}


/**
 * Purpose: Serialized implementation
 *
 * @return string
 * */
string JumpStmt::serialize()
{
    if (hasLabel){
        return("<jmp>\n\t"
            + operand_one->serialize()
            + "\t" + label->serialize()
            + "</jmp>\n");
    } else {
        return("<jmp>\n\t"
            + operand_one->serialize()
            + "</jmp>\n");
    }
}
