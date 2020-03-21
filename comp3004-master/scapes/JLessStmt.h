 /**
 * File Name: JLessStmt.h
 * Class Name: JLessStmt
 * Purpose: Header file for JLessStmt class
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

#ifndef JLESSSTMT_H
#define JLESSSTMT_H
using namespace std;
#include <string>
#include "Statement.h"

class JLessStmt : public Statement
{
  public:
    JLessStmt();
    ~JLessStmt();
    void compile(string&);
    void run();
    int run(vector<Statement*>&);
    string serialize();

  private:

};

#endif
