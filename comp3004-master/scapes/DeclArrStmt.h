 /**
 * File Name: DeclArrStmt.h
 * Class Name: DeclArrStmt
 * Purpose: Header file for DeclArrStmt class
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

#ifndef DECLARRSTMT_H
#define DECLARRSTMT_H
using namespace std;
#include <string>
#include "Statement.h"

class DeclArrStmt : public Statement
{
  public:
    DeclArrStmt();
    ~DeclArrStmt();
    void compile(string&);
    void run();
    int run(vector<Statement*>&);
    string serialize();
    int live; // used for knowing if a variable can be referenced
    int* array;
    void setArray(int, int);
    int getArray(int);

  private:

};

#endif
