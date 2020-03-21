/**
 * File Name: MovStmt.cpp
 * Class Name: MovStmt
 * Purpose: Class to handle Mov statement
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

#include "MovStmt.h"

/**
 * Purpose: Constructor
 * */
MovStmt::MovStmt(){}


/**
 * Purpose: Destructor
 * */
MovStmt::~MovStmt(){}


/**
 * Purpose: Compile implementation
 *
 * @param instr string&
 * @return void
 * */
void MovStmt::compile(string& instr)
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

    cout << "CHECK HERE" << endl;
    cout <<operand_one->name << endl;
    
    return;
}


/**
 * Purpose: Run
 *
 * @param stat vector<Statement*>&
 * @return int
 * */
int MovStmt::run(vector<Statement*>& stat){
    // move takes a source and goes to the destination
    cout << "Ran MovStmt" << endl << flush;
    //cout << "Operand_one: " << operand_one->name << endl;
    size_t pos;
    string target;
    string temporary;
    bool isArray = false;
    int index;
    int sourceValue;


    // source accepts every type of value
    // assign sourceValue here
    // if the operand is already a literal then take it. else perform the variable lookup
    try{
        cout << "Attempting to assign operand_one (as literal form) to sourceValue" <<endl;
        sourceValue = stoi(operand_one->name);
        cout << "just performed the stoi" << endl;
    } catch (...) {
        cout << "Attempting to assign operand_one (as variable form) to sourceValue" <<endl;
        target = operand_one->name;
    
        pos = operand_one->name.find("+");
        if (pos != string::npos) { // is an array
            cout << "identified operand_one as array identifier" <<endl;
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

    // destination is variable or array element\
    cout << "Attempting to assign operand_one (as variable form) to sourceValue" <<endl;
    target = operand_two->name;

    cout << "made it down here" << endl;
    pos = operand_two->name.find("+");
    cout << "made it down here 2" << endl;
    cout << "operand_two: " << operand_two->name << endl;
    if (pos != string::npos) { // is an array
        cout << "made it down here 3" << endl;
        isArray = true;
        target = operand_two->name.substr(0,pos); // pulls the variable name out from before the "+"
        cout << "made it down here 5" << endl;
        target = target.substr(1,target.length()); // remove leading "$"
        cout << "made it down here 6" << endl;
        //set index here
        
        cout << (operand_two->name.substr(pos+1, operand_two->name.length())) << endl;
        try { // attempt to get it as a literal
            index = stoi(operand_two->name.substr(pos+1, operand_two->name.length()));
        } catch(...) { // otherwise variable lookup
            //target = operand_two->name.substr(pos+1, operand_two->name.length()); //modify target to look for variable (temporary)
            temporary = operand_two->name.substr(pos+1, operand_two->name.length()); //modify target to look for variable (temporary)
            for (size_t i = 0; i < stat.size() ; ++i) {
                if (stat[i]->live and (stat[i]->operand_one->name.compare(temporary) == 0)) {
                    index = stat[i]->operand_one->getRealValue();
                    break;
                }
            }

        }
        cout << "made it down here 7" << endl;
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
                cout << " Setting MOV array: " << endl;
                cout << "index : " << index << endl;
                cout << "sourceValue: " << sourceValue << endl;
                stat[i]->setArray(index, sourceValue);
                break;
            } else {
                stat[i]->operand_one->setRealValue(sourceValue);
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
void MovStmt::run(){}


/**
 * Purpose: serialize implementation
 *
 * @return string
 * */
string MovStmt::serialize()
{
    if (hasLabel){
        return("<mov>\n\t"
            + operand_one->serialize()
            + "\t" + operand_two->serialize()
            + "\t" + label->serialize()
            + "</mov>\n");
    } else {
        return("<mov>\n\t"
            + operand_one->serialize()
            + "\t" + operand_two->serialize()
            + "</mov>\n");
    }
}
