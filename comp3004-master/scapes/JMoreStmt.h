 /**
 * File Name: JMoreStmt.h
 * Class Name: JMoreStmt
 * Purpose: Header file for JMoreStmt class
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

#ifndef JMORESTMT_H
#define JMORESTMT_H
using namespace std;
#include <string>
#include <vector>
#include "Statement.h"

class JMoreStmt : public Statement
{
  public:
    JMoreStmt();
    ~JMoreStmt();
    void compile(string&);
    void run();
    int run(vector<Statement*>&);
    string serialize();

  private:

};

#endif
