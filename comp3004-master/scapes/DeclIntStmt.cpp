/**
 * File Name: DeclIntStmt.cpp
 * Class Name: DeclIntStmt
 * Purpose: Class to handle Declare Int statement
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

#include "DeclIntStmt.h"
#include "Program.h"

/**
 * Purpose: Construtor
 * */
DeclIntStmt::DeclIntStmt(){}


/**
 * Purpose: Constructor
 *
 * @param sourceLine int
 * */
DeclIntStmt::DeclIntStmt(int sourceLine)
{
    line = sourceLine;
}


/**
 * Purpose: Destructor
 * */
DeclIntStmt::~DeclIntStmt(){}


/**
 * Purpose: Compile implementation
 *
 * @param instr string&
 * @return void
 * */
void DeclIntStmt::compile(string& instr)
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
    pos = s.find(" ");
    s.erase(0, pos + 1); //":".length());

    // operand
    Operand* newOperand = new Operand(s);
    operand_one = newOperand;
    hasOpOne = true;

    return;
}


/**
 * Purpose: Run method inherited from parent class
 *
 * @return void
 * */
void DeclIntStmt::run()
{
    live = true;
    cout << "Ran DeclIntStmt" << endl;
}


/**
 * Purpose: Run method inherited from parent class
 *
 * @param stat vector<Statement*>&
 * @return int
 * */
int DeclIntStmt::run(vector<Statement*>& stat)
{
    // have to give it ability to take variable paremter
    setLive(1);
    cout << "Ran DeclIntStmt" << endl;
    return 0;
}


/*
 * Purpose: serialize implementation
 *
 * @return string
 * */
string DeclIntStmt::serialize()
{
    if (hasLabel){
        return("<dci>\n\t"
            + operand_one->serialize()
            + "\t" + label->serialize()
            + "</dci>\n");
    } else {
        return("<dci>\n\t"
            + operand_one->serialize()
            + "</dci>\n");
    }
}
