 /**
 * File Name: JumpStmt.h
 * Class Name: JumpStmt
 * Purpose: Header file for JumpStmt class
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

#ifndef JUMPSTMT_H
#define JUMPSTMT_H
using namespace std;
#include <string>
#include "Statement.h"

class JumpStmt : public Statement
{
  public:
    JumpStmt();
    ~JumpStmt();
    void compile(string&);
    void run();
    int run(vector<Statement*>&);
    string serialize();

  private:

};

#endif
