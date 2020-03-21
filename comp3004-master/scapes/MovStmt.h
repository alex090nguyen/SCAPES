 /**
 * File Name: MovStmt.h
 * Class Name: MovStmt
 * Purpose: Header file for MovStmt class
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

#ifndef MOVSTMT_H
#define MOVSTMT_H
using namespace std;
#include <string>
#include "Statement.h"

class MovStmt : public Statement
{
  public:
    MovStmt();
    ~MovStmt();
    void compile(string&);
    void run();
    int run(vector<Statement*>&);
    string serialize();

  private:

};

#endif
