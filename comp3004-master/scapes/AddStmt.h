 /**
 * File Name: AddStmt.h
 * Class Name: AddStmt
 * Purpose: Header file for AddStmt class
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

#ifndef ADDSTMT_H
#define ADDSTMT_H
using namespace std;
#include <string>
#include <vector>
#include "Statement.h"

class AddStmt : public Statement
{
  public:
    AddStmt();
    ~AddStmt();
    void compile(string&);
    void run();
    int run(vector<Statement*>&);
    string serialize();

  private:

};

#endif
