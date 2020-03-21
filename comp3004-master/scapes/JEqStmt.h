 /**
 * File Name: JEqStmt.h
 * Class Name: JEqStmt
 * Purpose: Header file for JEqStmt class
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

#ifndef JEQSTMT_H
#define JEQSTMT_H
using namespace std;
#include <string>
#include "Statement.h"

class JEqStmt : public Statement
{
  public:
    JEqStmt();
    ~JEqStmt();
    void compile(string&);
    void run();
    int run(vector<Statement*>&);
    string serialize();

  private:

};

#endif
