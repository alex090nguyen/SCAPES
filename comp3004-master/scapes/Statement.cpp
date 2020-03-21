/**
 * File Name: Statement.cpp
 * Class Name: Statement
 * Purpose: Class to handle statement
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

#include "Statement.h"

/**
 * Purpose: Constructor
 * */
Statement::Statement(){live = 69;}


/**
 * Purpose: Destructor
 * */
Statement::~Statement(){}


/**
 * Purpose: * QT won't allow compilation with destructor defined (not sure why) so clean() is called instead
 * 
 * @return void
 * */
void Statement::clean()
{
    if (hasLabel){
        delete label;
    }
    if (hasOpOne) {
        delete operand_one;
    }
    if (hasOpTwo){
        delete operand_two;
    }
}


/**
 * Purpose: Get label
 * 
 * @return string
 * */
string Statement::getLabel()
{
    if(hasLabel){
        return label->name;
    } else {
        return "";
    }
}


/**
 * Purpose: Compile implementation
 *
 * @param instr string&
 * @return void
 * */
void Statement::compile(string& instr)
{
    (void)instr;
}


/**
 * Purpose: Run method inherited from parent class
 * @return void
 * */
void Statement::run(){}


/**
 * Purpose: run
 * 
 * @param vector<Statement*>&
 * @return int
 * */
int Statement::run(vector<Statement*>&) 
{
    cout << "Statement::run -> this should not be seen" <<endl;
    return 0;
}
 

/**
 * Purpose: Set label
 *
 * @param newLabel Label*
 * @return void
 * */
void Statement::setLabel(Label* newLabel)
{
    this->label = newLabel;
}


/**
 * Purpose: Get label
 *
 * @return Label*
 * */
/*Label* Statement::getLabel()
{
    return this->label;
}*/


/**
 * Purpose: Test statement creation
 *
 * @return void
 * */
void Statement::teststmtcreation()
{

    cout << label->name << endl;
    cout << operand_one->name << endl;

}


/**
 * Purpose: Trim whitespace
 *
 * @param s string&
 * @return void
 * */
void Statement::trim(string& s)
{
   size_t p = s.find_first_not_of(" \t");
   s.erase(0, p);
}
