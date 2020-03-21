 /**
 * File Name: ReadStmt.h
 * Class Name: ReadStmt
 * Purpose: Header file for ReadStmt class
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

#ifndef READSTMT_H
#define READSTMT_H
using namespace std;
#include <string>
#include "Statement.h"

class ReadStmt : public Statement
{
  public:
    ReadStmt();
    ~ReadStmt();
    void compile(string&);
    void run();
    int run(vector<Statement*>&);
    string serialize();
    int readValue(const string&);
  private:

};

#endif
