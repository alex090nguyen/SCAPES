/**
* File Name: Program.h
* Class Name: Program
* Purpose: Header file for Program class
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

#ifndef PROGRAM_H
#define PROGRAM_H
using namespace std;
#include <string>
#include <vector>
#include <QStringList>
#include "Statement.h"
#include "CompStmt.h"
#include "DeclIntStmt.h"
#include "EndStmt.h"
#include "JumpStmt.h"
#include "PrintStmt.h"
#include "ReadStmt.h"
#include "JMoreStmt.h"
#include "JEqStmt.h"
#include "DeclArrStmt.h"
#include "MovStmt.h"
#include "JLessStmt.h"
#include "AddStmt.h"
#include "Variable.h"
#include "IntVariable.h"
#include "ArrayVariable.h"

class Program
{
 public:
   Program();
   ~Program();
   void compile(vector<string>&);
   void execute(vector<string>&);
   void populateCommands(vector<string>&, const QString&);
   void cleanUpCommands(vector<string>&);
   void serializeToFile(const string&);
   void setFileName(const string&);
   bool getCompileStatus() const;
   bool getExecuteStatus() const;
   void print();
   void clean();
   vector<Statement*> stat;
   const string getCompileLogs() const;
   const string getExecuteLogs() const;

 private:
   int comparisonFlag;
   vector<Variable*> dcVars;
   vector<IntVariable*> dciVars;
   vector<ArrayVariable*> dcaVars;
   vector<Variable*> rdiVars;
   vector<Label*> labelVars;
   vector<string> jLabels;
   string filename;
   string compileFailedLogs;
   string compileSucceededLogs;
   string compilelogs;
   string executeFailedLogs;
   string executeSucceededLogs;
   string executeLogs;
   bool oldFile;
   bool compileStatus;
   bool executeStatus;
   void parse(string&, string&, size_t&);
   void parseXML(vector<string>&);
   size_t arrayCheck(size_t&, string&, int&, string&);

};

#endif
