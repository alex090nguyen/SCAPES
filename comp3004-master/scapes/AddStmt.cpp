/**
 * File Name: AddStmt.cpp
 * Class Name: AddStmt
 * Purpose: Class to handle AddStmt statement
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

#include "AddStmt.h"
#include "Statement.h"

//rdireads an integer value from the user and stores it in a variable or array elementvariable or array element where the value will be storednot used

/**
 * Purpose: Constructor
 * */
AddStmt::AddStmt(){}


/**
 * Purpose: Destructor
 * */
AddStmt::~AddStmt(){}


/**
 * Purpose: Compile implementation
 *
 * @param instr string&
 * @return void
 * */
void AddStmt::compile(string& instr)
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

    // operand_one
    pos = s.find(" ");
    Operand* newOperand = new Operand(s.substr(0, pos));
    operand_one = newOperand;
    hasOpOne = true;
    s.erase(0, pos + 1); //":".length());

    // operand_two
    Operand* newOperandTwo = new Operand(s);
    operand_two = newOperandTwo;
    hasOpTwo = true;

    return;
}


/**
 * Purpose: run
 *
 * @param stat vector<Statement*>&
 * @return int
 * */
int AddStmt::run(vector<Statement*>& stat)
{
    // move takes a source and goes to the destination
    cout << "Ran AddStmt" << endl;
    size_t pos;
    string target;
    bool isArray = false;
    int index;
    int sourceValue;


    // source accepts every type of value
    // assign sourceValue here
    // if the operand is already a literal then take it. else perform the variable lookup
    try{
        cout << "Attempting to assign operand_one (as literal form) to sourceValue" <<endl;
        sourceValue = stoi(operand_one->name);

    } catch (...) {
        cout << "Attempting to assign operand_one (as variable form) to sourceValue inside AddStmt" <<endl;
        target = operand_one->name;
        cout << "target: " << target << endl;
    
        pos = operand_one->name.find("+");
        if (pos != string::npos) { // is an array
            isArray = true;
            target = operand_one->name.substr(0,pos); // pulls the variable name out from before the "+"
            target = target.substr(1,target.length()); // remove leading "$"
            //set index here
            index = stoi(operand_one->name.substr(pos+1, operand_one->name.length()));
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
                    sourceValue = stat[i]->getArray(index);
                    break;
                } else {
                    sourceValue = stat[i]->operand_one->getRealValue();
                    break;
                }
            }
        }
    }
    isArray = false; //reset this flag for next lookup

    // destination is variable or array element
    target = operand_two->name;

    pos = operand_two->name.find("+");
    if (pos != string::npos) { // is an array
        isArray = true;
        target = operand_two->name.substr(0,pos); // pulls the variable name out from before the "+"
        target = target.substr(1,target.length()); // remove leading "$"
        //set index here
        index = stoi(operand_two->name.substr(pos+1, operand_two->name.length()));
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
                stat[i]->setArray(index, sourceValue + stat[i]->getArray(index));
                break;
            } else {
                stat[i]->operand_one->setRealValue(sourceValue + stat[i]->operand_one->getRealValue());
                break;
            }
        }
    }
    return 0;
}


/**
 * Purpose: Run method inherited from parent class
 *
 * @return void
 * */
void AddStmt::run()
{
  cout << "Ran AddStmt" << endl;
}


/**
 * Purpose: serialize implementation
 *
 * @return string
 * */
string AddStmt::serialize()
{
    if (hasLabel){
        return("<add>\n\t"
            + operand_one->serialize()
            + "\t" + operand_two->serialize()
            + "\t" + label->serialize()
            + "</add>\n");
    } else {
        return("<add>\n\t"
            + operand_one->serialize()
            + "\t" + operand_two->serialize()
            + "</add>\n");
    }
}
