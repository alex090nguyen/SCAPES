 /**
 * File Name: EndStmt.h
 * Class Name: EndStmt
 * Purpose: Header file for EndStmt class
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

#ifndef ENDSTMT_H
#define ENDSTMT_H
using namespace std;
#include <string>
#include "Statement.h"

class EndStmt : public Statement
{
  public:
    EndStmt();
    ~EndStmt();
    void compile(string&);
    void run();
    int run(vector<Statement*>&);
    string serialize();

  private:

};

#endif
