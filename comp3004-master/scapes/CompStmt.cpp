/**
 * File Name: CompStmt.cpp
 * Class Name: CompStmt
 * Purpose: Class to handle Compare statement
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

#include "CompStmt.h"

/**
 * Purpose: Constructor
 * */
CompStmt::CompStmt(){}


/**
 * Purpose: Destructor
 * */
CompStmt::~CompStmt(){}


/**
 * Purpose: Compile implementation
 *
 * @param instr string&
 * @return void
 * */
void CompStmt::compile(string& instr)
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
 * Purpose: run
 *
 * @param stat vector<Statement*>&
 * @return int
 * */
int CompStmt::run(vector<Statement*>& stat)
{
    // move takes a source and goes to the destination
    cout << "Ran CompStmt" << endl;
    size_t pos;
    string target;
    bool isArray = false;
    int index;
    // two values to compare
    int sourceValue_one;
    int sourceValue_two;


    // source accepts every type of value
    // assign sourceValue here
    // if the operand is already a literal then take it. else perform the variable lookup
    try{
        cout << "Attempting to assign operand_one (as literal form) to sourceValue_one" <<endl;
        sourceValue_one = stoi(operand_one->name);
    } catch (...) {
        cout << "Attempting to assign operand_one (as variable form) to sourceValue_one" <<endl;
        target = operand_one->name;
    
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
                    sourceValue_one = stat[i]->getArray(index);
                    break;
                } else {
                    sourceValue_one = stat[i]->operand_one->getRealValue();
                    break;
                }
            }
        }
    }


    isArray = false; //reset this flag for next lookup

    // destination is variable or array element\
    cout << "Attempting to assign operand_one (as variable form) to sourceValue" <<endl;
    try{
        cout << "Attempting to assign operand_one (as literal form) to sourceValue_two" <<endl;
        sourceValue_two = stoi(operand_two->name);
    } catch (...) {
        cout << "Attempting to assign operand_one (as variable form) to sourceValue_two" <<endl;
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
                cout << "attempting access " << endl;
                if (isArray) {
                    //stat[i]->setArray(index, sourceValue + stat[i]->getArray(index));
                    cout << "attempting array access " << endl;
                    sourceValue_two = stat[i]->getArray(index);
                    break;
                } else {
                    sourceValue_two = stat[i]->operand_one->getRealValue();
                    //stat[i]->operand_one->setRealValue(sourceValue + stat[i]->operand_one->getRealValue());
                    break;
                }
            }
        }
    }

    cout << "COMPARE STATEMENT FINAL EVAL" << endl;
    cout << "sourceValue_one: " << sourceValue_one << endl;
    cout << "sourceValue_two: " << sourceValue_two << endl;
    if (sourceValue_one == sourceValue_two){ return 11;}
    if (sourceValue_one > sourceValue_two){ return 12;}
    if (sourceValue_one < sourceValue_two){ return 13;}
}


/**
 * Purpose: Inherited from run method from parent
 *
 * @return void
 * */
void CompStmt::run()
{
  cout << "Ran CompStmt" << endl;
}


/**
 * Purpose: Serialize implementation
 *
 * @return string
 * */
string CompStmt::serialize(){
    if (hasLabel){
        return("<cmp>\n\t"
            + operand_one->serialize()
            + "\t" + operand_two->serialize()
            + "\t" + label->serialize()
            + "</cmp>\n");
    } else {
        return("<cmp>\n\t"
            + operand_one->serialize()
            + "\t" + operand_two->serialize()
            + "</cmp>\n");
    }
}
