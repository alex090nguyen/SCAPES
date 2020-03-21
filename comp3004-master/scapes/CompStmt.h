 /**
 * File Name: CompStmt.h
 * Class Name: CompStmt
 * Purpose: Header file for CompStmt class
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

#ifndef COMPSTMT_H
#define COMPSTMT_H
using namespace std;
#include <string>
#include "Statement.h"

class CompStmt : public Statement
{
  public:
    CompStmt();
    ~CompStmt();
    void compile(string&);
    void run();
    int run(vector<Statement*>&);
    string serialize();

  private:

};

#endif
