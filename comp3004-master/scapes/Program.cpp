/**
 * File Name: Program.cpp
 * Class Name: Program
 * Purpose: This class handles the contol flow of the program.
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

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <QMessageBox>
#include <locale>
#include <sstream>
using namespace std;

#include "Program.h"

/**
 * Purpose: Program class constructor. Initializes attributes.
 * */
Program::Program()
{
  oldFile = false;
  compileStatus = false;
  executeStatus = false;
  compilelogs = "";
  executeLogs = "";
  compileFailedLogs = "";
  compileSucceededLogs = "";
  executeFailedLogs = "";
  executeSucceededLogs = "";
}


/**
 * Purpose: Program class deconstructor.
 * */
Program::~Program(){}


/**
 * Purpose: Checks the syntax of an array element operand.
 *
 * @param lineIndex size_t&
 * @param operand string&
 * @param arrayIndex int&
 * @param arrayName string&
 *
 * @return size_t
 * 2 if the operand is not an array element
 * 1 if there is a syntax error
 * 0 if the array element syntax is corrct
 * */
size_t Program::arrayCheck(size_t& lineIndex, string& operand, int& arrayIndex, string& arrayName)
{
  size_t i = lineIndex;
  string oper = operand;

  size_t j = 0;

  if (oper.substr(j,1).compare("$") == 0) { // first check if this operand is an array element
    if (oper.size() == 1) { // nothing after $
      compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": An array variable and index must be specified.\n";
      compileStatus = false;
      return 1;
    }

    arrayName = "";
    for (j = 1; oper.substr(j,1).compare("+") != 0 && j < oper.size() ; ++j) { // get array variable
      arrayName += oper.substr(j,1);
    }

    if (j == oper.size()) { // no '+'
      compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": An index for the array must be specified.\n";
      compileStatus = false;
      return 1;
    }

    if (oper.substr(j,1).compare("+") == 0 && oper.size() == j+1) { // nothing after '+'
      compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": An index for the array must be specified.\n";
      compileStatus = false;
      return 1;
    }

    for (size_t index = 0; index < dciVars.size() ; ++index) { // check if variable has already been declared
      if (arrayName.compare(dciVars[index]->getName()) == 0) {
        compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + arrayName + " has been declared as an integer variable. It cannot be used to store an array.\n";
        compileStatus = false;
        return 1;
      }
    }

    bool declStatus = false;
    for (size_t index = 0; index < dcaVars.size() ; ++index) { // check if the array variable has been declared
      if (arrayName.compare(dcaVars[index]->getName()) == 0) {
        declStatus = true;
        break;
      }
    }

    if (declStatus == false) { // deal with error
      compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + arrayName + " has not been declared.\n";
      compileStatus = false;
      return 1;
    }

    string indexPos = "";
    for (size_t index = j+1; index < oper.size() ; ++index) { // collect array index postion
      indexPos += oper.substr(index,1);
    }

    for (size_t index = 0; index < dcaVars.size() ; ++index) { // check if the array index is a declared array variable
      if (indexPos.compare(dcaVars[index]->getName()) == 0) {
        compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + indexPos + " has been declared as an array. An array cannot be an index value.\n";
        compileStatus = false;
        return 1;
      }
    }

    for (size_t index = 0; index < dciVars.size() ; ++index) { // check if the array index is a declared integer variable
      if (indexPos.compare(dciVars[index]->getName()) == 0) {
        //arrayIndex = dciVars[index]->getValue();
        return 0; // successful
      }
    }

    indexPos = "";
    for (size_t index = j+1; index < oper.size() ; ++index) { // collect array index postion and see if it a number.
      if (oper.substr(index,1).compare("0") == 0 || oper.substr(index,1).compare("1") == 0 || oper.substr(index,1).compare("2") == 0 || oper.substr(index,1).compare("3") == 0 ||
          oper.substr(index,1).compare("4") == 0 || oper.substr(index,1).compare("5") == 0 || oper.substr(index,1).compare("6") == 0 || oper.substr(index,1).compare("7") == 0 ||
          oper.substr(index,1).compare("8") == 0 || oper.substr(index,1).compare("9") == 0) { // index position must be a number
        indexPos += oper.substr(index,1);
        continue;
      }
      // error if this index character is not a number. At this point, it is neither a number nor a declared integer variable.
      compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": An index must be a number or a declared integer variable.\n";
      compileStatus = false;
      return 1;
    }
    int number = 0;                       // converting string to int
    istringstream convert(indexPos);      // converting string to int
    if (!(convert >> number)) number = 0; // converting string to int
    arrayIndex = number;
    if (arrayIndex > 2147483647) {
      compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": An integer cannot be more than 2147483647.\n";
      compileStatus = false;
      return 1;
    }

    if (declStatus == true) {
      for (size_t index = 0; index < dcaVars.size(); ++index) { // check for out of bounds index
        if (arrayName.compare(dcaVars[index]->getName()) == 0) {
          int maxSize = dcaVars[index]->getSize();
          if (arrayIndex >= maxSize) {
            compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + oper + " is trying to access an array element that does not exist (out of bounds).\n";
            compileStatus = false;
            return 1;
          }
        }
      }
    }
    return 0; // successful
  } else {
    return 2;
  }
}


/**
 * Purpose: Takes in a statement string with the label removed and compiles it if there are no syntax errors.
 *
 * @param l string&
 * @param s string&
 * @param ii size_t&
 * @return void
 * */
void Program::parse(string& l, string& s, size_t& ii)
{
  string line = l;
  string str = s;
  size_t i = ii;

  size_t j = 0; // current index of labelless string

  if (str.empty() == true) {
    compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": This statement has no instruction.\n";
    compileStatus = false;
  }

  size_t findColon = str.find(":");
  if (findColon != string::npos) {
    compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": A statement can only have one colon.\n";
    compileStatus = false;
    return;
  }

  if (str.size() < 3) { // only comment statements can be shorter than 3.
    compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": A non-comment instruction must be 3 characters long.\n";
    compileStatus = false;
    return;
  }

  if (str.size() == 3) { // if size is exactly 3, the instruction must be 'end'.
    if (str.compare("end") == 0) { // if the instruction is 'end', deal with it.
      EndStmt* end = new EndStmt;
      end->compile(line);
      compileSucceededLogs += "EndStmt compiled.\n\n";
      serializeToFile(end->serialize());
      stat.push_back(end);
      return;
    } else if (str.compare("prt") == 0 || str.compare("cmp") == 0 || str.compare("jls") == 0 || str.compare("dca") == 0 ||
               str.compare("rdi") == 0 || str.compare("dci") == 0 || str.compare("jeq") == 0 || str.compare("mov") == 0 ||
               str.compare("jmr") == 0 || str.compare("jmp") == 0 || str.compare("add") == 0) // is it a valid instruction?
    {
      compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": This instruction requires at least one operand.\n";
      compileStatus = false;
      return;
    } else { // then it must be garbage
      compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": No such instruction exists in the SCAPL language.\n";
      compileStatus = false;
      return;
    }
  }

  if (str.substr(0,3).compare("end") == 0 && str.size() > 3) {
    compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": Nothing can come after an end instruction.\n";
    compileStatus = false;
    return;
  }

  string oper1 = ""; // stores first operand
  string oper2 = ""; // stores second operand
  if (str.substr(3,1).compare(" ") == 0) { // is there a space after instruction? collect operands
    if (str.substr(0,3).compare("prt") == 0 || str.substr(0,3).compare("rdi") == 0 || str.substr(0,3).compare("jls") == 0 ||
        str.substr(0,3).compare("dci") == 0 || str.substr(0,3).compare("jeq") == 0 ||
        str.substr(0,3).compare("jmr") == 0 || str.substr(0,3).compare("jmp") == 0 ) { // Is this a one-operand instruction?
      for (j = 4 ; j < str.size() ; ++j) { // collect the first operand
        if (str.substr(j,1).compare(" ") == 0) { // no spaces allowed within a variable except prt with ""
          if (str.substr(0,3).compare("prt") == 0 && str.substr(4,1).compare("\"") == 0) {
            oper1 += str.substr(j,1);
            continue;
          }
          compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": This instruction can only have one operand.\n";
          compileStatus = false;
          return;
        }
        oper1 += str.substr(j,1);
      }

      // return all one-operand instructions
      if (str.substr(0,3).compare("dci") == 0) {
        for (size_t index = 0; index < dcVars.size() ; ++index) { // check if operand 1 has already been declared
          if (oper1.compare(dcVars[index]->getName()) == 0) {
            compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + oper1 + " has already been declared.\n";
            compileStatus = false;
            return;
          }
        }

        if (str.substr(4,1).compare("$") == 0) { // check if operand has array element syntax
          compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": This instruction cannot take array elements as an operand.\n";
          compileStatus = false;
          return;
        }

        // check if operand is a number
        string numCount = "";
        for (j = 0; j < oper1.size() ; ++j) { // check if operand is a number
          if (oper1.substr(j,1).compare("0") == 0 || oper1.substr(j,1).compare("1") == 0 || oper1.substr(j,1).compare("2") == 0 || oper1.substr(j,1).compare("3") == 0 ||
              oper1.substr(j,1).compare("4") == 0 || oper1.substr(j,1).compare("5") == 0 || oper1.substr(j,1).compare("6") == 0 || oper1.substr(j,1).compare("7") == 0 ||
              oper1.substr(j,1).compare("8") == 0 || oper1.substr(j,1).compare("9") == 0) { // operand 2 must be a number
            numCount += oper1.substr(j,1);
            continue;
          }
        }

        if (numCount.size() == oper1.size()) { // oper1 is a number
          compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": This instruction does not take a number as operand.\n";
          compileStatus = false;
          return;
        }

        // proceed with declaration
        IntVariable* var = new IntVariable(oper1);
        dcVars.push_back(var);
        dciVars.push_back(var);
        DeclIntStmt* decl = new DeclIntStmt;
        decl->compile(line);
        compileSucceededLogs += "DeclIntStmt compiled.\n";
        serializeToFile(decl->serialize());
        stat.push_back(decl);
        return;
      }

      if (str.substr(0,3).compare("rdi") == 0) {

        // check if the operand is an array element
        int arrayIndex = 0; // for storing index after calling arrayCheck()
        string arrayName = ""; // for storing the name of the  array variable after calling arrayCheck()
        size_t arrayCheckResult = arrayCheck(i, oper1, arrayIndex, arrayName);
        if (arrayCheckResult == 0) {
          ReadStmt* read = new ReadStmt;
          read->compile(line);
          compileSucceededLogs += "ReadStmt compiled.\n";
          serializeToFile(read->serialize());
          stat.push_back(read);
          return;
        } else if (arrayCheckResult == 1) {
          return;
        }


        // the operand must be an integer variable
        for (size_t index = 0; index < dcaVars.size() ; ++index) { // check if operand 1 has been declared as an array
          if (oper1.compare(dcaVars[index]->getName()) == 0) {
            compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": Incorrect syntax for reading values into an array.\n";
            compileStatus = false;
            return;
          }
        }

        for (size_t index = 0; index < dciVars.size() ; ++index) { // check if operand 1 has been declared as an integer
          if (oper1.compare(dciVars[index]->getName()) == 0) {
            rdiVars.push_back(dciVars[index]);
            ReadStmt* read = new ReadStmt;
            read->compile(line);
            compileSucceededLogs += "ReadStmt compiled.\n";
            serializeToFile(read->serialize());
            stat.push_back(read);
            return;
          }
        }

        compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + oper1 + " is an undeclared variable.\n";
        compileStatus = false;
        return;
      }

      if (str.substr(0,3).compare("jmp") == 0) {
        jLabels.push_back(oper1); // will be checked at end of program compilation
        JumpStmt* jmp = new JumpStmt;
        jmp->compile(line);
        compileSucceededLogs += "JumpStmt compiled.\n";
        serializeToFile(jmp->serialize());
        stat.push_back(jmp);
        return;
      }

      if (str.substr(0,3).compare("jmr") == 0) {
        jLabels.push_back(oper1); // will be checked at end of program compilation
        JMoreStmt* jmr = new JMoreStmt;
        jmr->compile(line);
        compileSucceededLogs += "JMoreStmt compiled.\n";
        serializeToFile(jmr->serialize());
        stat.push_back(jmr);
        return;
      }

      if (str.substr(0,3).compare("jeq") == 0) {
        jLabels.push_back(oper1); // will be checked at end of program compilation
        JEqStmt* jeq = new JEqStmt;
        jeq->compile(line);
        compileSucceededLogs += "JEqStmt compiled.\n";
        serializeToFile(jeq->serialize());
        stat.push_back(jeq);
        return;
      }

      if (str.substr(0,3).compare("jls") == 0) {
        jLabels.push_back(oper1); // will be checked at end of program compilation
        JLessStmt* jls = new JLessStmt;
        jls->compile(line);
        compileSucceededLogs += "JLessStmt compiled.\n";
        serializeToFile(jls->serialize());
        stat.push_back(jls);
        return;
      }

      if (str.substr(0,3).compare("prt") == 0) {
        // check if the operand is a string
        if (str.substr(4,1).compare("\"") == 0) {
          string toPrint = "";
          for (j = 5; str.substr(j,1).compare("\"") != 0 && j < str.size() ; ++j) {
            toPrint += str.substr(j,1);
            continue;
          }

          if (j+1 == str.size() && str.substr(j,1).compare("\"") == 0) {
            PrintStmt* prt = new PrintStmt;
            prt->compile(line);
            compileSucceededLogs += "PrintStmt compiled.\n";
            serializeToFile(prt->serialize());
            stat.push_back(prt);
            return;
          }

          compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": A string must have closing quotation marks.\n";
          compileStatus = false;
          return;
        }

        // check if the operand is an array element
        int arrayIndex = 0; // for storing index after calling arrayCheck()
        string arrayName = ""; // for storing the name of the  array variable after calling arrayCheck()
        size_t arrayCheckResult = arrayCheck(i, oper1, arrayIndex, arrayName);
        if (arrayCheckResult == 0) {
          PrintStmt* prt = new PrintStmt;
          prt->compile(line);
          compileSucceededLogs += "PrintStmt compiled.\n";
          serializeToFile(prt->serialize());
          stat.push_back(prt);
          return;
        } else if (arrayCheckResult == 1) {
          return;
        }

        // operand is probably a variable
        for (size_t index = 0; index < rdiVars.size() ; ++index) { // check if oper1 has been read
          if (oper1.compare(rdiVars[index]->getName()) == 0) {
            PrintStmt* prt = new PrintStmt;
            prt->compile(line);
            compileSucceededLogs += "PrintStmt compiled.\n";
            serializeToFile(prt->serialize());
            stat.push_back(prt);
            return;
          }
        }

        compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + oper1 + " has not been read.\n";
        compileStatus = false;
        return;
      }

    } else if (str.substr(0,3).compare("cmp") == 0 || str.substr(0,3).compare("dca") == 0 ||
               str.substr(0,3).compare("mov") == 0 || str.substr(0,3).compare("add") == 0) { // check for all two-operand instructions
      for (j = 4 ; j < str.size() ; ++j) { // collect the first of two operands
        if (str.substr(j,1).compare(" ") == 0) { // if there is a space, start collecting the second operand
          for (++j; j < str.size() ; ++j) { // collect the second operand
            if (str.substr(j,1).compare(" ") == 0) {
              compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": This instruction can only have two operands.\n";
              compileStatus = false;
              return;
            }
            oper2 += str.substr(j,1);
          }

          // Is this a dca statement?
          if (str.substr(0,3).compare("dca") == 0) {
            for (size_t index = 0; index < dcVars.size() ; ++index) { // check if operand 1 has already been declared
              if (oper1.compare(dcVars[index]->getName()) == 0) {
                compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + oper1 + " has already been declared.\n";
                compileStatus = false;
                return;
              }
            }

            if (oper1.substr(0,1).compare("$") == 0) { // check if operand has array element syntax
              compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ":  This instruction cannot take array elements as an operand.\n";
              compileStatus = false;
              return;
            }

            if (oper2.substr(0,1).compare("$") == 0) { // check if operand has array element syntax
              compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ":  This instruction cannot take array elements as an operand.\n";
              compileStatus = false;
              return;
            }

            // check if oper1 is a number
            string numCount = "";
            for (j = 0; j < oper1.size() ; ++j) { // check if operand is a number
              if (oper1.substr(j,1).compare("0") == 0 || oper1.substr(j,1).compare("1") == 0 || oper1.substr(j,1).compare("2") == 0 || oper1.substr(j,1).compare("3") == 0 ||
                  oper1.substr(j,1).compare("4") == 0 || oper1.substr(j,1).compare("5") == 0 || oper1.substr(j,1).compare("6") == 0 || oper1.substr(j,1).compare("7") == 0 ||
                  oper1.substr(j,1).compare("8") == 0 || oper1.substr(j,1).compare("9") == 0 || oper1.substr(j,1).compare("-") == 0) {
                numCount += oper1.substr(j,1);
                continue;
              }
            }

            if (numCount.size() == oper1.size()) { // oper1 is a number
              compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": This instruction does not take a number as operand.\n";
              compileStatus = false;
              return;
            }

            bool notRead = false;
            for (size_t index = 0; index < dciVars.size(); ++index) { // check if oper2 is an integer variable
              if (oper2.compare(dciVars[index]->getName()) == 0) {
                for (size_t index2 = 0; index2 < rdiVars.size(); ++index2) {
                  if (dciVars[index]->getName().compare(rdiVars[index2]->getName()) == 0) {
                    ArrayVariable* var = new ArrayVariable(oper1, 0);
                    dcVars.push_back(var);
                    dcaVars.push_back(var);
                    DeclArrStmt* dca = new DeclArrStmt;
                    dca->compile(line);
                    compileSucceededLogs += "DeclArrStmt compiled.\n";
                    serializeToFile(dca->serialize());
                    stat.push_back(dca);
                    return;
                  }
                  notRead = true;
                }
                if (notRead == true || rdiVars.size() == 0) {
                  cout << "SCAPL Syntax Error at line " << i+1 << ": " << oper2 << " has not been read." << endl;
                  compileStatus = false;
                  return;
                }
              }
            }


            string arraySize = "";
            for (j = 0; j < oper2.size() ; ++j) { // check if operand 2 is a number
              if (oper2.substr(j,1).compare("0") == 0 || oper2.substr(j,1).compare("1") == 0 || oper2.substr(j,1).compare("2") == 0 || oper2.substr(j,1).compare("3") == 0 ||
                  oper2.substr(j,1).compare("4") == 0 || oper2.substr(j,1).compare("5") == 0 || oper2.substr(j,1).compare("6") == 0 || oper2.substr(j,1).compare("7") == 0 ||
                  oper2.substr(j,1).compare("8") == 0 || oper2.substr(j,1).compare("9") == 0 || oper2.substr(j,1).compare("-") == 0) { // operand 2 must be a number
                arraySize += oper2.substr(j,1);
                continue;
              }
              // error if operand 2 character is not a number
              compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": The second operand of a dca instruction must be a number or a declared integer variable.\n";
              compileStatus = false;
              return;
            }

            int maxSize = 0;                         // converting string to int
            istringstream convert(arraySize);        // converting string to int
            if (!(convert >> maxSize)) maxSize = 0;  // converting string to int

            if (maxSize <= 0) {
              compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": The size of an array must be at least 1.\n";
              compileStatus = false;
              return;
            }

            ArrayVariable* var = new ArrayVariable(oper1, maxSize);
            dcVars.push_back(var);
            dcaVars.push_back(var);
            DeclArrStmt* dca = new DeclArrStmt;
            dca->compile(line);
            compileSucceededLogs += "DeclArrStmt compiled.\n";
            serializeToFile(dca->serialize());
            stat.push_back(dca);
            return;
          }

          // is this a cmp statement?
          if (str.substr(0,3).compare("cmp") == 0) {
            string oper;
            for (size_t stage = 1; stage < 3 ; ++stage) { // loop twice. One for oper1, the other for oper2
              bool breakLoop = false;

              if (stage == 1) { // checking oper1
                oper = oper1;
              } else { // checking oper2
                oper = oper2;
              }

              // check if the operand is an array element
              int arrayIndex = 0; // for storing index after calling arrayCheck()
              string arrayName = ""; // for storing the name of the  array variable after calling arrayCheck()
              size_t arrayCheckResult = arrayCheck(i, oper, arrayIndex, arrayName);
              if (arrayCheckResult == 0) {
                if (stage == 2) {
                  CompStmt* cmp = new CompStmt;
                  cmp->compile(line);
                  compileSucceededLogs += "CompStmt compiled.\n";
                  serializeToFile(cmp->serialize());
                  stat.push_back(cmp);
                  return;
                }
                continue;
              } else if (arrayCheckResult == 1) {
                return;
              }

              // check if the operand has been read
              for (size_t index = 0; index < dcaVars.size() ; ++index) { // check if it is an array variable
                if (oper.compare(dcaVars[index]->getName()) == 0) {
                  compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + oper + " has been declared as an array. Only integers can be compared.\n";
                  compileStatus = false;
                  return;
                }
              }

              for (size_t index = 0; index < dciVars.size() ; ++index) { // check if it is an integer variable
                if (oper.compare(dciVars[index]->getName()) == 0) {
                  for (size_t index = 0; index < rdiVars.size() ; ++index) { // check if the integer variable has been read. Return if so.
                    if (oper.compare(rdiVars[index]->getName()) == 0) {
                      if (stage == 2) {
                        CompStmt* cmp = new CompStmt;
                        cmp->compile(line);
                        compileSucceededLogs += "CompStmt compiled.\n";
                        serializeToFile(cmp->serialize());
                        stat.push_back(cmp);
                        return;
                      }
                      breakLoop = true; // oper1 is fine. Check oper2.
                      break;
                    }
                  }
                  if (breakLoop == true) { // oper1 is fine. Check oper2.
                    break;
                  }
                  compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + oper + " has been declared but has not been read.\n";
                  compileStatus = false;
                  return;
                }
              }

              if (breakLoop == true) { // oper1 is fine. Check oper2.
                continue;
              }

              for (j = 0; j < oper.size() ; ++j) { // check if the operand is a number
                if (oper.substr(j,1).compare("0") == 0 || oper.substr(j,1).compare("1") == 0 || oper.substr(j,1).compare("2") == 0 || oper.substr(j,1).compare("3") == 0 ||
                    oper.substr(j,1).compare("4") == 0 || oper.substr(j,1).compare("5") == 0 || oper.substr(j,1).compare("6") == 0 || oper.substr(j,1).compare("7") == 0 ||
                    oper.substr(j,1).compare("8") == 0 || oper.substr(j,1).compare("9") == 0) { // operand 2 must be a number
                  continue;
                }
                // oper is not a number, not an array element, and not an integer variable. It is garbage.
                compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + oper + " is not a number, an array element, nor an integer variable.\n";
                compileStatus = false;
                return;
              }
              if (stage == 2) {
                CompStmt* cmp = new CompStmt;
                cmp->compile(line);
                compileSucceededLogs += "CompStmt compiled.\n";
                serializeToFile(cmp->serialize());
                stat.push_back(cmp);
                return;
              }

            } // end main loop
          }

          // is this a mov statement?
          if (str.substr(0,3).compare("mov") == 0) {
            string oper;
            for (size_t stage = 1; stage < 3 ; ++stage) { // loop twice. One for oper1, the other for oper2
              bool breakLoop = false;

              if (stage == 1) { // checking oper1
                oper = oper1;
              } else { // checking oper2
                oper = oper2;
              }

              // check if the operand is an array element
              int arrayIndex = 0; // for storing index after calling arrayCheck()
              string arrayName = ""; // for storing the name of the  array variable after calling arrayCheck()
              size_t arrayCheckResult = arrayCheck(i, oper, arrayIndex, arrayName);
              if (arrayCheckResult == 0) {
                if (stage == 2) {
                  MovStmt* mov = new MovStmt;
                  mov->compile(line);
                  compileSucceededLogs += "MovStmt compiled.\n";
                  serializeToFile(mov->serialize());
                  stat.push_back(mov);
                  return;
                }
                continue;
              } else if (arrayCheckResult == 1) {
                return;
              }

              // check if the operand has been read
              for (size_t index = 0; index < dcaVars.size() ; ++index) { // check if it is an array variable
                if (oper.compare(dcaVars[index]->getName()) == 0) {
                  compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + oper + " has already been declared as an array. Only integers can be compared.\n";
                  compileStatus = false;
                  return;
                }
              }

              for (size_t index = 0; index < dciVars.size() ; ++index) { // check if it is an integer variable
                if (oper.compare(dciVars[index]->getName()) == 0) {
                  for (size_t index = 0; index < rdiVars.size() && stage == 1; ++index) { // check if the oper1 has been read.
                    if (oper.compare(rdiVars[index]->getName()) == 0) {
                      breakLoop = true;
                      break;
                    }
                  }

                  if (stage == 1 && breakLoop == false) { // oper1 has not been read
                    compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + oper + " has been declared but has not been read.\n";
                    compileStatus = false;
                    return;
                  }

                  if (breakLoop == true) {
                    break;
                  }

                  if (stage == 2) { // return if oper2 has been declared but not read. That's what we want
                    rdiVars.push_back(dciVars[index]); // add to read variables since it should have a value after mov is executed.
                    MovStmt* mov = new MovStmt;
                    mov->compile(line);
                    compileSucceededLogs += "MovStmt compiled.\n";
                    serializeToFile(mov->serialize());
                    stat.push_back(mov);
                    return;
                  }
                }
              }

              if (breakLoop == true) { // oper1 is fine. Check oper2.
                continue;
              }

              if (stage == 2) {
                compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + oper + " is neither an array element, nor an integer variable.\n";
                compileStatus = false;
                return;
              }

              for (j = 0; j < oper.size() ; ++j) { // check if the operand is a number. Only oper1 should get here.
                if (oper.substr(j,1).compare("0") == 0 || oper.substr(j,1).compare("1") == 0 || oper.substr(j,1).compare("2") == 0 || oper.substr(j,1).compare("3") == 0 ||
                    oper.substr(j,1).compare("4") == 0 || oper.substr(j,1).compare("5") == 0 || oper.substr(j,1).compare("6") == 0 || oper.substr(j,1).compare("7") == 0 ||
                    oper.substr(j,1).compare("8") == 0 || oper.substr(j,1).compare("9") == 0) {
                  continue;
                }
                // oper is not a number, not an array element, and not an integer variable. It is garbage.
                compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + oper + " is not a number, an array element, nor an integer variable.\n";
                compileStatus = false;
                return;
              }
            }
          }

          // is this an add statement?
          if (str.substr(0,3).compare("add") == 0) {
            string oper;
            for (size_t stage = 1; stage < 3 ; ++stage) { // loop twice. One for oper1, the other for oper2
              bool breakLoop = false;

              if (stage == 1) { // checking oper1
                oper = oper1;
              } else { // checking oper2
                oper = oper2;
              }

              // check if the operand is an array element
              int arrayIndex = 0; // for storing index after calling arrayCheck()
              string arrayName = ""; // for storing the name of the  array variable after calling arrayCheck()
              size_t arrayCheckResult = arrayCheck(i, oper, arrayIndex, arrayName);
              if (arrayCheckResult == 0) {
                if (stage == 2) {
                  AddStmt* add = new AddStmt;
                  add->compile(line);
                  compileSucceededLogs += "AddStmt compiled.\n";
                  serializeToFile(add->serialize());
                  stat.push_back(add);
                  return;
                }
                continue;
              } else if (arrayCheckResult == 1) {
                return;
              }

              // check if the operand has been read
              for (size_t index = 0; index < dcaVars.size() ; ++index) { // check if it is an array variable
                if (oper.compare(dcaVars[index]->getName()) == 0) {
                  compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + oper + " has already been declared as an array. Only integers can be compared.\n";
                  compileStatus = false;
                  return;
                }
              }

              for (size_t index = 0; index < dciVars.size() ; ++index) { // check if it is an integer variable
                if (oper.compare(dciVars[index]->getName()) == 0) {
                  for (size_t index = 0; index < rdiVars.size() ; ++index) { // check if the integer variable has been read. Return if so.
                    if (oper.compare(rdiVars[index]->getName()) == 0) {
                      if (stage == 2) {
                        AddStmt* add = new AddStmt;
                        add->compile(line);
                        compileSucceededLogs += "AddStmt compiled.\n";
                        serializeToFile(add->serialize());
                        stat.push_back(add);
                        return;
                      }
                      breakLoop = true; // oper1 is fine. Check oper2.
                      break;
                    }
                  }
                  if (breakLoop == true) { // oper1 is fine. Check oper2.
                    break;
                  }
                  compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + oper + " has been declared but has not been read.\n";
                  compileStatus = false;
                  return;
                }
              }

              if (breakLoop == true) { // oper1 is fine. Check oper2.
                continue;
              }

              if (stage == 2) {
                compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + oper + " is neither an array element, nor an integer variable.\n";
                compileStatus = false;
                return;
              }

              for (j = 0; j < oper.size() ; ++j) { // check if the operand is a number. Only oper1 should get here.
                if (oper.substr(j,1).compare("0") == 0 || oper.substr(j,1).compare("1") == 0 || oper.substr(j,1).compare("2") == 0 || oper.substr(j,1).compare("3") == 0 ||
                    oper.substr(j,1).compare("4") == 0 || oper.substr(j,1).compare("5") == 0 || oper.substr(j,1).compare("6") == 0 || oper.substr(j,1).compare("7") == 0 ||
                    oper.substr(j,1).compare("8") == 0 || oper.substr(j,1).compare("9") == 0) {
                  continue;
                }
                // oper is not a number, not an array element, and not an integer variable. It is garbage.
                compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": " + oper + " is not a number, an array element, nor an integer variable.\n";
                compileStatus = false;
                return;
              }
            }
          }

        }
        oper1 += str.substr(j,1);
      }

      // cmp didn't get a second operand
      compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": This instruction needs a second operand.\n";
      compileStatus = false;
      return;

    } else { // error. garbage instruction
      compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": No such instruction exists in the SCAPL language.\n";
      compileStatus = false;
      return;
    }
  } else { // error. no space after instruction.
    compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": Invalid instruction.\n";
    compileStatus = false;
    return;
  }
  return ;
}


/**
 * Purpose: Takes in a vector containing every line of statements in the program per index. Compiles each line while
 *          checking for syntax errors.
 *
 * @param input vector<string>&
 * @return void
 * */
void Program::compile(vector<string>& input)
{
  // Start of compilation
  compileSucceededLogs += "--------- Compilation Initiated ----------\n\n";
  compileStatus = true;

  for (size_t i = 0; i < input.size() ; ++i) { // loop through every line. start loop 1
    bool breakLoop2 = false;
    bool breakLoop3 = false;
    //size_t check = 0; // number of colons in line
    size_t j = 0; // line index
    string line = input[i];

    if (line.empty()) { // ignore empty lines
      continue;
    }

    if (line.substr(0,1) == "#") { // ignore comments
      continue;
    }

    /*
    for (j = 0; j < line.size() ; ++j) { // search for multiple occurences of ':'
      if (line.substr(j,1).compare(":") == 0) {
        check++;
      }
    }
    if (check > 1) { // check for number of colons
      cout << "SCAPL Syntax Error at line " << i+1 << ": A statement must not have more than one colon." << endl;
      continue;
    }
    */

    size_t findLabel = line.find(":");
    string label = ""; // stores a label if one is present

    if (findLabel != string::npos) { // check if this character has a label
        if (line.substr(j,1).compare(":") == 0) {
          compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": There must be a label before a colon.\n";
          compileStatus = false;
          continue;
        }

        for (; line.substr(j,1).compare(" ") != 0 ; ++j) { // loop while this is not a space. Dealing with spaces while parsing a label. start loop 4
          label += line.substr(j,1); // build label string
          if (line.substr(j+1,1).compare(":") == 0) {
            j = j + 2; // move past colon
            break;
          }

          if (line.substr(j+1,1).compare(" ") == 0 && line.substr(j+2,1).compare(":") != 0) { // check that the next two characters are correct
            compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": There can be only one label in a statement.\n";
            compileStatus = false;
            breakLoop2 = true;
            break;
          }
        } // end loop 4

        if (breakLoop2) { // go to next line
          continue;
        }

        if (labelVars.empty() == true) { // check if there are any other labels before this line in the program
          Label* labelObject = new Label(label);
          labelVars.push_back(labelObject);
        } else {
          for (size_t index = 0; index < labelVars.size() ; ++index) { // check if a similar label already exists
            if (label.compare(labelVars[index]->name) == 0) {
              compileFailedLogs += "SCAPL Syntax Error at line " + to_string(i+1) + ": The same label cannot be assigned to more than one statement.\n";
              compileStatus = false;
              breakLoop3 = true;
              break;
            }
          }

          if (breakLoop3) {
            continue;
          }
          Label* labelObject = new Label(label);
          labelVars.push_back(labelObject); // add this label to vector of existing labels
        }

        if (line.substr(j,1).compare(" ") == 0) { // check for space after colon
          ++j;
        }

        string str = "";
        for (; j < line.size() ; ++j) { // collect the rest of the string for more processing.
          str += line.substr(j,1);
        }

        parse(line, str, i);
        continue;

    } else { // statement has no label
      parse(line, line, i);
    }
  } // end loop 1

  // check if the label operands are correct
  bool test[jLabels.size()];
  for (size_t index = 0; index < jLabels.size() ; ++index) { // populate an empty array with falses to match jLabels size
    test[index] = false;
  }

  for (size_t index = 0; index < jLabels.size() ; ++index) { // find the correct indices in jLabel and set to true
    for (size_t index2 = 0; index2 < labelVars.size() ; ++index2) {
      if (jLabels[index].compare(labelVars[index2]->name) == 0) {
        test[index] = true;
      }
    }
  }

  for (size_t index = 0; index < jLabels.size() ; ++index) { // print label errors
    if (test[index] == false) {
      compileFailedLogs += "SCAPL Label Error: " + jLabels[index] + " is not a label in this program.\n";
      compileStatus = false;
    }
  }

  // end of compilation
  compileSucceededLogs += "--------- Compilation Completed ----------";
  if (getCompileStatus()){
      compilelogs = compileSucceededLogs;
  }
  else{
      compilelogs = compileFailedLogs;
  }
  serializeToFile("\n\n\n\n\n\n\n\n\n"); // prevents errors when parsing the XML
}


/**
 * Purpose: Runs the program
 * 
 * @param input vector<string>&
 * @return void
 * */
void Program::execute(vector<string>& input)
{
    executeStatus = true;
    string targetLabel = "";
    int mostRecentComparison = 0;
    // 0 for nothing
    // 11 for equal
    // 12 for greater than
    // 13 for less than
    int state = 0;
    // 0 for nothing
    // 1 for end
    // 2 for unconditional jump
    // 3 for equal jump
    // 4 for geq jump
    // 5 for leq jump
    // 11 for just evaluated an equal comparison
    // 12 for just evaluated a geq comparison
    // 13 for just evaluated a leq comparison

    executeSucceededLogs += "--------- Execution Initiated ----------\n\n";
    try {
        parseXML(input);
        // run the main execution loop
        cout << "debug execute loop stats:" << endl;
        cout << "size: " << stat.size() << endl;
        size_t i = 0;
        while (i < stat.size()) {
            //cout << "Looping stat at position: " << i << endl;
            //cout << "operand_one: " << stat[i]->operand_one->name << endl;
            state = stat[i]->run(stat);
            //cout << "operand_one: " << stat[i]->operand_one->name << endl; // this causes seg fault for end cause end has no op_one
            cout << "CHECK STATE HERE" << endl;
            cout << "state: " << state << endl;

            if (state == 1){
                // exit running
                cout << "EXIT HERE" << endl;
                // just set i to something that ends the while loop
                i = stat.size()+100;
            } else if (state == 2) { // set i to desired value with no checking
                cout << "state is 2" << endl;
                //do a lookup for i here and call ita  day
                targetLabel = stat[i]->operand_one->name;
                for (size_t x = 0; x < stat.size(); ++x){
                    if (stat[x]->getLabel().compare(targetLabel) == 0) {
                        i = x-1; // -1 allows for increment at end if loop
                        break;
                    }
                }
            } else if (state == 3){ // equal jump
                cout << "state is 3" << endl;
                if (mostRecentComparison == 11){
                    targetLabel = stat[i]->operand_one->name;
                    for (size_t x = 0; x < stat.size(); ++x){
                        if (stat[x]->getLabel().compare(targetLabel) == 0) {
                            i = x-1;                    
                            break;
                        }
                    }
                }
            } else if (state == 4) { // geq jump
                cout << "state is 4" << endl;
                if (mostRecentComparison == 12){
                    targetLabel = stat[i]->operand_one->name;
                    for (size_t x = 0; x < stat.size(); ++x){
                        if (stat[x]->getLabel().compare(targetLabel) == 0) {
                            i = x-1;                    
                            break;
                        }
                    }
                }
            } else if (state == 5){ //leq jump
                cout << "state is 5" << endl;
                if (mostRecentComparison == 13){
                    targetLabel = stat[i]->operand_one->name;
                    for (size_t x = 0; x < stat.size(); ++x){
                        if (stat[x]->getLabel().compare(targetLabel) == 0) {
                            i = x -1;
                            break;
                        }
                    }
                }
            } else if (state == 11) {
                cout << "state is 11" << endl;
                mostRecentComparison = 11;
            } else if (state == 12) {
                cout << "state is 12" << endl;
                mostRecentComparison = 12;
            } else if (state == 13) {
                cout << "state is 13" << endl;
                mostRecentComparison = 13;
            }
            i++;
        }
        executeStatus = true;
        executeSucceededLogs += "--------- Execution Complete ----------";
    } catch(...){
        executeStatus = false;
        executeFailedLogs = "Runtime error!";
    }
    if (getExecuteStatus()){
        executeLogs = executeSucceededLogs;
    }
    else{
        executeLogs = executeFailedLogs;
    }
}


/**
 * Purpose: parses the XML output from compilation back into objects that can be executed
 *
 * @param input vector<string>&
 * @return void
 * */
void Program::parseXML(vector<string>& input)
{
    size_t pos; // used for string manipulation

    cout << "------ Parsing XML ------ " << endl;
    cout << "statement debug stats:" << endl;
    cout << "size of input: "<< input.size() << endl;
    string str = "";
    string line = "";
    for (size_t i = 0; i < input.size() ; i++) {
        str = input[i];
        line = "";

        // dci block
        if (str.compare("<dci>") == 0) {
           // recreate the line for easy recompilation
           // first check for label
           pos = input[i+4].find("<label>");
           if (pos != string::npos) {
               str = input[i+5];
               pos = str.find("<name>");
               str.erase(0, pos+6);
               pos = str.find("</name>");
               line += str.substr(0, pos);
               line += ": ";
           }

           str = input[i];
           // then add operand
           line += "dci ";
           //line += input[i+2]
           str = input[i+2];
           pos = str.find("<name>");
           str.erase(0, pos+6); // +6 to include the <name>
           pos = str.find("</name>");
           line += str.substr(0, pos);
           //cout << line << endl;

           DeclIntStmt* decl = new DeclIntStmt();
           decl->compile(line);
           stat.push_back(decl);
        }

        //dca block
        // dca arr 10
        if (str.compare("<dca>") == 0) {
           // first check for label
           pos = input[i+7].find("<label>");
           if (pos != string::npos) {
               str = input[i+8];
               pos = str.find("<name>");
               str.erase(0, pos+6);
               pos = str.find("</name>");
               line += str.substr(0, pos);
               line += ": ";
           }

           // add operand one
           str = input[i];
           line += "dca ";
           str = input[i+2];
           pos = str.find("<name>");
           str.erase(0, pos+6); // +6 to include the <name>
           pos = str.find("</name>");
           line += str.substr(0, pos);
           line += " ";

           // add operand two
           str = input[i+5];
           pos = str.find("<name>");
           str.erase(0, pos+6); // +6 to include the <name>
           pos = str.find("</name>");
           line += str.substr(0, pos);

           //cout << line << endl;
           DeclArrStmt* dca = new DeclArrStmt();
           dca->compile(line);
           stat.push_back(dca);
        }

        //rdi block
        if (str.compare("<rdi>") == 0) {
           // recreate the line for easy recompilation
           // first check for label
           pos = input[i+4].find("<label>");
           if (pos != string::npos) {
               str = input[i+5];
               pos = str.find("<name>");
               str.erase(0, pos+6);
               pos = str.find("</name>");
               line += str.substr(0, pos);
               line += ": ";
           }

           // add operand one
           str = input[i];
           line += "rdi ";
           str = input[i+2];
           pos = str.find("<name>");
           str.erase(0, pos+6); // +6 to include the <name>
           pos = str.find("</name>");
           line += str.substr(0, pos);
           //cout << line << endl;

           ReadStmt* read = new ReadStmt();
           read->compile(line);
           stat.push_back(read);
        }

        //prt block
        if (str.compare("<prt>") == 0) {
           // recreate the line for easy recompilation
           // first check for label
           pos = input[i+4].find("<label>");
           if (pos != string::npos) {
               str = input[i+5];
               pos = str.find("<name>");
               str.erase(0, pos+6);
               pos = str.find("</name>");
               line += str.substr(0, pos);
               line += ": ";
           }

           // add operand one
           str = input[i];
           line += "prt ";
           str = input[i+2];
           pos = str.find("<name>");
           str.erase(0, pos+6); // +6 to include the <name>
           pos = str.find("</name>");
           line += str.substr(0, pos);
           //cout << line << endl;

           PrintStmt* prt = new PrintStmt();
           prt->compile(line);
           stat.push_back(prt);
        }

        //mov block
        if (str.compare("<mov>") == 0) {
           // first check for label
           pos = input[i+7].find("<label>");
           if (pos != string::npos) {
               str = input[i+8];
               pos = str.find("<name>");
               str.erase(0, pos+6);
               pos = str.find("</name>");
               line += str.substr(0, pos);
               line += ": ";
           }

           // add operand one
           str = input[i];
           line += "mov ";
           str = input[i+2];
           pos = str.find("<name>");
           str.erase(0, pos+6); // +6 to include the <name>
           pos = str.find("</name>");
           line += str.substr(0, pos);
           line += " ";

           // add operand two
           str = input[i+5];
           pos = str.find("<name>");
           str.erase(0, pos+6); // +6 to include the <name>
           pos = str.find("</name>");
           line += str.substr(0, pos);

           //cout << line << endl;
           MovStmt* mov = new MovStmt();
           mov->compile(line);
           stat.push_back(mov);
        }

        //add block
        if (str.compare("<add>") == 0) {
           // first check for label
           pos = input[i+7].find("<label>");
           if (pos != string::npos) {
               str = input[i+8];
               pos = str.find("<name>");
               str.erase(0, pos+6);
               pos = str.find("</name>");
               line += str.substr(0, pos);
               line += ": ";
           }

           // add operand one
           str = input[i];
           line += "add ";
           str = input[i+2];
           pos = str.find("<name>");
           str.erase(0, pos+6); // +6 to include the <name>
           pos = str.find("</name>");
           line += str.substr(0, pos);
           line += " ";

           // add operand two
           str = input[i+5];
           pos = str.find("<name>");
           str.erase(0, pos+6); // +6 to include the <name>
           pos = str.find("</name>");
           line += str.substr(0, pos);

           //cout << line << endl;
           AddStmt* add = new AddStmt();
           add->compile(line);
           stat.push_back(add);
        }

        //cmp block
        if (str.compare("<cmp>") == 0) {
           // first check for label
           pos = input[i+7].find("<label>");
           if (pos != string::npos) {
               str = input[i+8];
               pos = str.find("<name>");
               str.erase(0, pos+6);
               pos = str.find("</name>");
               line += str.substr(0, pos);
               line += ": ";
           }

           // add operand one
           str = input[i];
           line += "cmp ";
           str = input[i+2];
           pos = str.find("<name>");
           str.erase(0, pos+6); // +6 to include the <name>
           pos = str.find("</name>");
           line += str.substr(0, pos);
           line += " ";

           // add operand two
           str = input[i+5];
           pos = str.find("<name>");
           str.erase(0, pos+6); // +6 to include the <name>
           pos = str.find("</name>");
           line += str.substr(0, pos);

           //cout << line << endl;
           CompStmt* cmp = new CompStmt();
           cmp->compile(line);
           stat.push_back(cmp);
        }

        // jls block
        if (str.compare("<jls>") == 0) {
           // recreate the line for easy recompilation
           // first check for label
           pos = input[i+4].find("<label>");
           if (pos != string::npos) {
               str = input[i+5];
               pos = str.find("<name>");
               str.erase(0, pos+6);
               pos = str.find("</name>");
               line += str.substr(0, pos);
               line += ": ";
           }

           // add operand one
           str = input[i];
           line += "jls ";
           str = input[i+2];
           pos = str.find("<name>");
           str.erase(0, pos+6); // +6 to include the <name>
           pos = str.find("</name>");
           line += str.substr(0, pos);
           //cout << line << endl;

           JLessStmt* jls = new JLessStmt();
           jls->compile(line);
           stat.push_back(jls);
        }

        //jmr block
        if (str.compare("<jmr>") == 0) {
           // recreate the line for easy recompilation
           // first check for label
           pos = input[i+4].find("<label>");
           if (pos != string::npos) {
               str = input[i+5];
               pos = str.find("<name>");
               str.erase(0, pos+6);
               pos = str.find("</name>");
               line += str.substr(0, pos);
               line += ": ";
           }

           // add operand one
           str = input[i];
           line += "jmr ";
           str = input[i+2];
           pos = str.find("<name>");
           str.erase(0, pos+6); // +6 to include the <name>
           pos = str.find("</name>");
           line += str.substr(0, pos);
           //cout << line << endl;

           JMoreStmt* jmr = new JMoreStmt();
           jmr->compile(line);
           stat.push_back(jmr);
        }

        //jeq block
        if (str.compare("<jeq>") == 0) {
           // recreate the line for easy recompilation
           // first check for label
           pos = input[i+4].find("<label>");
           if (pos != string::npos) {
               str = input[i+5];
               pos = str.find("<name>");
               str.erase(0, pos+6);
               pos = str.find("</name>");
               line += str.substr(0, pos);
               line += ": ";
           }

           // add operand one
           str = input[i];
           line += "jeq ";
           str = input[i+2];
           pos = str.find("<name>");
           str.erase(0, pos+6); // +6 to include the <name>
           pos = str.find("</name>");
           line += str.substr(0, pos);
           //cout << line << endl;

           JEqStmt* jeq = new JEqStmt();
           jeq->compile(line);
           stat.push_back(jeq);
        }

        //jmp block
        if (str.compare("<jmp>") == 0) {
           // recreate the line for easy recompilation
           // first check for label
           pos = input[i+4].find("<label>");
           if (pos != string::npos) {
               str = input[i+5];
               pos = str.find("<name>");
               str.erase(0, pos+6);
               pos = str.find("</name>");
               line += str.substr(0, pos);
               line += ": ";
           }

           // add operand one
           str = input[i];
           line += "jmp ";
           str = input[i+2];
           pos = str.find("<name>");
           str.erase(0, pos+6); // +6 to include the <name>
           pos = str.find("</name>");
           line += str.substr(0, pos);
           //cout << line << endl;

           JumpStmt* jmp = new JumpStmt();
           jmp->compile(line);
           stat.push_back(jmp);
        }

        //end block
        if (str.compare("<end>") == 0) {
           // recreate the line for easy recompilation
           // first check for label
           pos = input[i+1].find("<label>");
           if (pos != string::npos) {
               str = input[i+2];
               pos = str.find("<name>");
               str.erase(0, pos+6);
               pos = str.find("</name>");
               line += str.substr(0, pos);
               line += ": ";
           }

           // add operand one
           str = input[i];
           line += "end";

           EndStmt* end = new EndStmt();
           end->compile(line);
           stat.push_back(end);
        }

    }
    cout << "XML parsing finished" << endl;
}


/**
 * Purpose: Takes an empty vector and populates it with SCAPL commands line by line.
 *
 * @param input vector<string>&
 * @param &textSplited QString
 * @return void
 * */
void Program::populateCommands(vector<string>& input, const QString &textSplited)
{
    input.push_back(textSplited.toLocal8Bit().constData());
}


/**
 * Purpose: Removes all the extra whitespace in the SCAPL program that is written or loaded by the user.
 *
 * @param input vector<string>&
 * @return void
 * */
void Program::cleanUpCommands(vector<string>& input)
{
    for (size_t i = 0; i < input.size(); ++i) {
        size_t pointer = 0;
        bool  space = true;
        for (size_t j = 0; j < input[i].size(); ++j) {
            if(input[i][j] != ' ') {
                input[i][pointer] = input[i][j];
                pointer++;
                space = false;
            }
            else if (!space) {
                input[i][pointer] = ' ';
                pointer++;
                space = true;
            }
        }
        if (space && input[i] != "" && input[i].find_first_not_of(' ') != std::string::npos) {
            input[i].resize(pointer - 1);
        }
        else {
            input[i].resize(pointer);
        }
    }
}


/**
 * Purpose: Takes XML data as input and writes that data to a file.
 *
 * @param input string&
 * @return void
 * */
void Program::serializeToFile(const string& input)
{
  ifstream infile(filename + ".o");
  ofstream serializedfile;
  if(infile.good() && !oldFile){
    serializedfile.open(filename + ".o", ios::trunc);
  }
  else{
    serializedfile.open(filename + ".o", ios::app);
  }
  oldFile = true;
  serializedfile << input;
  serializedfile.close();
}


/**
 * Purpose: Retrieves the actual filename from the current file we are trying to compile.
 *
 * @return void
 * */
void Program::setFileName(const string& currentfilename)
{
    size_t found = currentfilename.find_last_of("/\\");
    filename = currentfilename.substr(found+1);
}


/**
 * Purpose: Used to retrieve the compilation status from the Program class. False == failed to compile. True == successfuly compiled.
 *
 * @return bool
 * */
bool Program::getCompileStatus() const
{
    return compileStatus;
}


/**
 * Purpose: Used to retrieve the execute status from the Program class. False == failed to execute. True == successfuly executed.
 *
 * @return bool
 * */
bool Program::getExecuteStatus() const
{
    return executeStatus;
}


/**
 * Purpose: None
 * @return void
 * */
void Program::print(){}


/**
 * Purpose: Program class cleaning function (used in place of destructor).
 * 
 * @return void
 **/
void Program::clean()
{
    for (unsigned i=0; i < stat.size(); i++){
       stat[i]->clean();
    }
    stat.clear();
}


/**
 * Purpose: Get compile-time logs
 * 
 * @return string
 **/
const string Program::getCompileLogs() const
{
    return compilelogs;
}


/**
 * Purpose: Get run-time logs
 *
 * @return string
 **/
const string Program::getExecuteLogs() const
{
    return executeLogs;
}
