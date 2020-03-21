/**
 * File Name: JEqStmt.cpp
 * Class Name: JEqStmt
 * Purpose: Class to handle jeq statement
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

#include "JEqStmt.h"

/**
 * Purpose: Constructor
 * */
JEqStmt::JEqStmt(){}


/**
 * Purpose: Destructor
 * */
JEqStmt::~JEqStmt(){}


/**
 * Purpose: Compile implementation
 *
 * @param instr string&
 * @return void
 * */
void JEqStmt::compile(string& instr)
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
 * Purpose: run
 *
 * @param vector<Statement*>&
 * @return int
 * */
int JEqStmt::run(vector<Statement*>&) {
    cout << "Ran JEqStmt" << endl;
    return 3;
}


/**
 * Purpose: Run method inherited from parent class
 *
 * @return void
 * */
void JEqStmt::run()
{
  cout << "Ran JEqStmt" << endl;
}


/**
 * Purpose: serialize implementation
 *
 * @return string
 * */
string JEqStmt::serialize(){
    if (hasLabel){
        return("<jeq>\n\t"
            + operand_one->serialize()
            + "\t" + label->serialize()
            + "</jeq>\n");
    } else {
        return("<jeq>\n\t"
            + operand_one->serialize()
            + "</jeq>\n");
    }
}
