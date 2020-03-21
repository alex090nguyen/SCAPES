/**
 * File Name: DeclArrStmt.cpp
 * Class Name: DeclArrStmt
 * Purpose: Class to handle DeclArr statement
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

#include "DeclArrStmt.h"

/**
 * Purpose: Constructor
 * */
DeclArrStmt::DeclArrStmt(){}


/**
 * Purpose: Destructor
 * */
DeclArrStmt::~DeclArrStmt(){}


/**
 * Purpose: Compile implementation
 *
 * @param instr string&
 * @return void
 * */
void DeclArrStmt::compile(string& instr)
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

    // operand_one
    pos = s.find(" ");
    Operand* newOperandOne = new Operand(s.substr(0, pos));
    operand_one = newOperandOne;
    hasOpOne = true;
    s.erase(0, pos + 1); //":".length());

    // operand_two
    Operand* newOperandTwo = new Operand(s);
    operand_two = newOperandTwo;
    hasOpTwo = true;

    return;
}


/**
 * Purpose: Run method inherited from parent class
 *
 * @param stat vector<Statement*>&
 * @return int
 * */
int DeclArrStmt::run(vector<Statement*>& stat)
{
    cout << "Ran DeclArrStmt" << endl;
    size_t pos;
    string target;
    bool isArray = false;
    int index;
    int size;


    // if the operand is already a literal then take it. else perform the variable lookup
    try{
        cout << "Attempting to assign operand_two (as literal form) to size" <<endl;
        size = stoi(operand_two->name);
    } catch (...) {
        cout << "Attempting to assign operand_two (as variable form) to size" <<endl;
        target = operand_two->name;
    
        pos = operand_one->name.find("+");
        if (pos != string::npos) { // is an array
            isArray = true;
            target = operand_two->name.substr(0,pos); // pulls the variable name out from before the "+"
            target = target.substr(1,target.length()); // remove leading "$"
            //set index here
            index = stoi(operand_two->name.substr(pos+1, operand_two->name.length()));
            cout << "Read operand_two " << operand_two << " as " << index << endl;
        }  
        //perform the lookup for operand_two->name
        for (size_t i = 0; i < stat.size() ; ++i) {
            // if stat[i].live //this will identify it as variabl
            cout << "Searching for:" << endl;
            cout << "live: " << stat[i]->live << endl;
            cout << "target: " << target << endl;
            cout << "name: " << stat[i]->operand_one->name << endl;
            if (stat[i]->live and (stat[i]->operand_one->name.compare(target) == 0)) {
                if (isArray) {
                    cout << "setting size of declArr through array variable. debug log." << endl;
                    size = stat[i]->getArray(index);
                    break;
                } else {
                    cout << "setting size of declArr through int variable. debug log." << endl;
                    size = stat[i]->operand_one->getRealValue();
                    break;
                }
            }
        }
    }
    // create the dynamic array in here
    array = new int[size];
    setLive(1);
    cout << "returning from declArray statement" << endl;
    return 0;
}


/**
 * Purpose: Set array
 *
 * @param index int
 * @param value int
 * @return void
 * */
void DeclArrStmt::setArray(int index, int value)
{
    cout << "Inside DeclArrStmt::setArray" << endl;
    cout << "Setting index: " << index << endl;
    cout << "Setting value: " << value <<  endl;
    
    array[index] = value;
}


/**
 * Purpose: Get array
 *
 * @param index int
 * @return int
 * */
int DeclArrStmt::getArray(int index)
{
    return array[index];
}


/**
 * Purpose: Run method inherited from parent class
 *
 * @return void
 * */
void DeclArrStmt::run()
{
  cout << "Ran DeclArrStmt" << endl;
}


/**
 * Purpose: Serialize implementation
 *
 * @return string
 * */
string DeclArrStmt::serialize()
{
    if (hasLabel){
        return("<dca>\n\t"
            + operand_one->serialize()
            + "\t" + operand_two->serialize()
            + "\t" + label->serialize()
            + "</dca>\n");
    } else {
        return("<dca>\n\t"
            + operand_one->serialize()
            + "\t" + operand_two->serialize()
            + "</dca>\n");
    }
}
