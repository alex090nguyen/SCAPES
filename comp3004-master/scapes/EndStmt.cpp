/**
 * File Name: EndStmt.cpp
 * Class Name: EndStmt
 * Purpose: Class to handle End Statement
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

#include "EndStmt.h"

//endindicates the end of the program | not used | not used

/**
 * Purpose: Constructor
 * */
EndStmt::EndStmt(){}


/**
 * Purpose: Destructor
 * */
EndStmt::~EndStmt(){}


/**
 * Purpose: Compile implementation
 *
 * @param instr string&
 * @return void
 * */
void EndStmt::compile(string& instr)
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

    return;
}


/**
 * Purpose: run
 *
 * @param vector<Statement*>&
 * @return int
 * */
int EndStmt::run(vector<Statement*>&)
{
    cout << "Ran EndStmt" << endl;
    return 1;
}


/**
 * Purpose: Run method inherited from parent
 *
 * @return void
 * */
void EndStmt::run(){}


/**
 * Purpose: Serialize implementation
 *
 * @return string
 * */
string EndStmt::serialize()
{
    if (hasLabel) {
        return("<end>\n\t"
            + label->serialize()
            + "</end>\n");
    } else {
        return("<end>\n</end>\n");
    }
}
