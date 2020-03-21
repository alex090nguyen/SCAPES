/**
 * File Name: ReadStmt.cpp
 * Class Name: ReadStmt
 * Purpose: Class to handle Read statement
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
#include <QString>
#include <QInputDialog>
using namespace std;

#include "ReadStmt.h"

/**
 * Purpose: Constructor
 * */
ReadStmt::ReadStmt(){}


/**
 * Purpose: Destructor
 * */
ReadStmt::~ReadStmt(){}


/**
 * Purpose: Compile implementation
 *
 * @param instr string&
 * @return void
 * */
void ReadStmt::compile(string& instr)
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
 * Purpose: Run method inherited from parent class
 *
 * @param stat vector<Statement*>&
 * @return int (to represent state)
 * */
int ReadStmt::run(vector<Statement*>& stat)
{
    size_t pos;
    string target = operand_one->name;
    bool isArray = false;
    int index;
    int userinput = readValue(target);

    cout << "Ran ReadStmt" << endl;

    // first check if operand is an array
    pos = operand_one->name.find("+");
    if (pos != string::npos) { // is an array
        cout << "Found array element" << endl;
        isArray = true;
        target = operand_one->name.substr(0,pos); // pulls the variable name out from before the "+"
        cout << "made it here 1" << endl;
        target = target.substr(1,target.length()); // remove leading "$"
        cout << "made it here 2" << endl;
        //set index here
        cout << operand_one->name.substr(pos+1, operand_one->name.length()) << endl;
        try { // if its an int literal this should be fine to access
            index = stoi(operand_one->name.substr(pos+1, operand_one->name.length()));
        } catch(...) { //otherwise perform variable lookup
            for (size_t i = 0; i < stat.size() ; ++i) {
                // if stat[i].islive //this will identify it as variable
                if (stat[i]->live and (stat[i]->operand_one->name.compare(operand_one->name.substr(pos+1, operand_one->name.length())) == 0)) {
                    cout << "attempting to read int value to set target index in ReadStmt" << endl;
                    index = stat[i]->operand_one->getRealValue(); //ints are stored in the operand class.
                    break;
                }
            }
        }
    }

        cout << "made it here 4" << endl;
    //perform a lookup to match operand label to destination label
    for (size_t i = 0; i < stat.size() ; ++i) {
        // if stat[i].islive //this will identify it as variable
        if (stat[i]->live and (stat[i]->operand_one->name.compare(target) == 0)) {
            if (isArray) {
                cout << "attempting to set array value. debug log." << endl;
                stat[i]->setArray(index, userinput); //arrays are stored in the statement class
                break;
            } else {
                cout << "attempting to set int value. debug log." << endl;
                stat[i]->operand_one->setRealValue(userinput); //ints are stored in the operand class.
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
void ReadStmt::run()
{
    cout << "Ran ReadStmt" << endl;
    readValue("testswag");
}


/**
 * Purpose: Read value
 *
 * @param name string&
 * @return int
 * */
int ReadStmt::readValue(const string& operand)
{
    string basetext = "Input For: " + operand;
    bool ok;
    int integer = QInputDialog::getInt(NULL, QObject::tr(basetext.c_str()), QObject::tr("Integer:"), 0, 0, 2147483647, 1, &ok);
    if(!ok){
        readValue(operand);
    }
    return integer;
}


/**
 * Purpose: serialize implementation
 *
 * @return string
 * */
string ReadStmt::serialize()
{
    if (hasLabel){
        return("<rdi>\n\t"
            + operand_one->serialize()
            + "\t" + label->serialize()
            + "</rdi>\n");
    } else {
        return("<rdi>\n\t"
            + operand_one->serialize()
            + "</rdi>\n");
    }
}
