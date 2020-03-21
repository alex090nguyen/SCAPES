/**
 * File Name: PrintStmt.cpp
 * Class Name: PrintStmt
 * Purpose: Class to hand print statement
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
#include <QMessageBox>
#include <QIcon>
#include <QString>
#include <QSpacerItem>
#include <QGridLayout>
using namespace std;

#include "PrintStmt.h"

/**
 * Purpose: Constructor
 * */
PrintStmt::PrintStmt(){}


/**
 * Purpose: Destructor
 * */
PrintStmt::~PrintStmt(){}


/**
 * Purpose: Compile implementation
 *
 * @param instr string&
 * @return void
 * */
void PrintStmt::compile(string& instr)
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
 * @param stat vector<Statement*>&
 * @return int
 * */
int PrintStmt::run(vector<Statement*>& stat)
{
        cout << "Attempting to run() print." << endl;
    string stringToPrint = "";
    size_t pos;
    string target;
    bool isArray = false;
    int index;

    pos = operand_one->name.find("\"");
    if (pos != string::npos){ // if the operand is a string literal
        stringToPrint = operand_one->name.substr(1, operand_one->name.size() - 2); //removes leading and trailing quotes
        // print the string here (stubbed)
        // for testing purposes, just use cout
        cout << "Printing:" << endl;
        cout << stringToPrint << endl;
        showValue(stringToPrint);
        return 0;
    } 

    // if the operand is an int literal
    try {
        stringToPrint = stoi(operand_one->name);
        cout << "Printing:" << endl;
        cout << stringToPrint << endl;
        showValue(stringToPrint);
        return 0;
    } catch (...) {}

    // last case is if its variable or array
    pos = operand_one->name.find("+");
    target = operand_one->name;
    if (pos != string::npos) { // is an array
        isArray = true;
        target = operand_one->name.substr(0,pos); // pulls the variable name out from before the "+"
        target = target.substr(1,target.length()); // remove leading "$"
        //set index here
        try { // try int literal then try variable
            index = stoi(operand_one->name.substr(pos+1, operand_one->name.length()));
        } catch(...) {
            for (size_t i = 0; i < stat.size() ; ++i) {
                // if stat[i].islive //this will identify it as variable
                if (stat[i]->live and (stat[i]->operand_one->name.compare(operand_one->name.substr(pos+1, operand_one->name.length())) == 0)) {
                    cout << "attempting to read int value to set target index in PrintStmt" << endl;
                    index = stat[i]->operand_one->getRealValue(); //ints are stored in the operand class.
                    break;
                }
            }

        }
    }  
    for (size_t i = 0; i < stat.size() ; ++i) {
        // if stat[i].live //this will identify it as variabl
        cout << "Searching for:" << endl;
        cout << "live: " << stat[i]->live << endl;
        cout << "target: " << target << endl;
        cout << "name: " << stat[i]->operand_one->name << endl;
        if (stat[i]->live and (stat[i]->operand_one->name.compare(target) == 0)) {
            if (isArray) {
                //cout << "setting size of declArr through array variable. debug log." << endl;
                stringToPrint = to_string(stat[i]->getArray(index));
                break;
            } else {
                //cout << "setting size of declArr through int variable. debug log." << endl;
                stringToPrint = to_string(stat[i]->operand_one->getRealValue());
                break;
            }
        }
    }
    cout << "Printing:" << endl;
    cout << stringToPrint << endl;
    showValue(stringToPrint);

    return 0;

}


/**
 * Purpose: Run method inherited from parent class
 *
 * @return void
 * */
void PrintStmt::run()
{
  cout << "Ran PrintStmt" << endl;
}


/**
 * Purpose: Displays the string from the Prt SCAPL instruction to the user.
 *
 * @param userinput string&
 * @return void
 * */
void PrintStmt::showValue(const string& userinput)
{
    QMessageBox printbox;
    printbox.setText(QString::fromStdString(userinput));
    printbox.setWindowTitle("Scapes: Execute Output");
    QPixmap pixmap = QPixmap(":/Icons/Scapes.png");
    printbox.setWindowIcon(QIcon(pixmap));
    printbox.setIcon(QMessageBox::Information);
    printbox.exec();
}


/**
 * Purpose: Serialize implementation
 *
 * @return string
 * */
string PrintStmt::serialize()
{
    if (hasLabel){
        return("<prt>\n\t"
            + operand_one->serialize()
            + "\t" + label->serialize()
            + "</prt>\n");
    } else {
        return("<prt>\n\t"
            + operand_one->serialize()
            + "</prt>\n");
    }
}
