 /**
 * File Name: PrintStmt.h
 * Class Name: PrintStmt
 * Purpose: Header file for PrintStmt class
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

#ifndef PRINTSTMT_H
#define PRINTSTMT_H
using namespace std;
#include <string>
#include "Statement.h"

class PrintStmt : public Statement
{
  public:
    PrintStmt();
    ~PrintStmt();
    void compile(string&);
    void run();
    int run(vector<Statement*>&);
    string serialize();
    void showValue(const string&);

  private:
    int value;

};

#endif
