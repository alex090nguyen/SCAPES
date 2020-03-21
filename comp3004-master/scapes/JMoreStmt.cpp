/**
 * File Name: JMoreStmt.cpp
 * Class Name: JMoreStmt
 * Purpose: Class to handle jmr statement
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
#include <vector>
using namespace std;

#include "JMoreStmt.h"

/**
 * Purpose: Constructor
 * */
JMoreStmt::JMoreStmt(){}


/**
 * Purpose: Destructor
 * */
JMoreStmt::~JMoreStmt(){}


/**
 * Purpose: Compile implementation
 *
 * @param instr string&
 * @return void
 * */
void JMoreStmt::compile(string& instr)
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
int JMoreStmt::run(vector<Statement*>&)
{
    cout << "Ran JMoreStmt" << endl;
    return 4;
}


/**
 * Purpose: Run method inherited from parent class
 *
 * @return void
 * */
void JMoreStmt::run()
{
  cout << "Ran JMoreStmt" << endl;
}


/**
 * Purpose: Serialize implementation
 *
 * @return string
 * */
string JMoreStmt::serialize()
{
    if (hasLabel){
        return("<jmr>\n\t"
            + operand_one->serialize()
            + "\t" + label->serialize()
            + "</jmr>\n");
    } else {
        return("<jmr>\n\t"
            + operand_one->serialize()
            + "</jmr>\n");
    }
}
