 /**
 * File Name: DeclIntStmt.h
 * Class Name: DeclIntStmt
 * Purpose: Header file for DeclIntStmt class
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

#ifndef DECLINTSTMT_H
#define DECLINTSTMT_H
using namespace std;
#include <string>
#include <vector>
#include "Statement.h"
#include "Operand.h"
#include "Label.h"
#include "Variable.h"
#include "IntVariable.h"
#include "ArrayVariable.h"

class DeclIntStmt : public Statement
{
  public:
    DeclIntStmt();
    DeclIntStmt(int sourceLine);
    ~DeclIntStmt();
    void compile(string&);
    void run();
    int run(vector<Statement*>&);
    string serialize();
    int live; // used for knowing if a variable can be referenced
    int value; // used for runtime

  private:
    int line;
    int lineNumber;
};

#endif
