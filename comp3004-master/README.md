# SCAPES

## Team Number/Name: 19 - Dorcs 
### Student Name & Numbers
* Alexander Nguyen (100908039)
* Emmanuel Elite (100878873)
* Kyle Bechtel (100979669)
* Nem Zutkovic (101085982)

## Introduction
The School of Computer science Assembly Programming Environment System (SCAPES) is a development
environment that allows a user to write, compile, and execute basic programs written in the School of
Computer science Assembly Programming Language (SCAPL) language.

### The Deliverable #2 requires us to implement the following features:
* Compile an existing program that may contain all the instructions in the SCAPL instruction set, as specified in Table 1 of the SCAPES project description.
* Execute an existing program that has been compiled by SCAPES.

## Design Pattern: Strategy
This pattern is necessary to our design because it enable an algorithm’s behavior to be selected at runtime. By encapsulating the single interface (Statement) and by making it an abstract class, we can then use different concrete classes, in this case the different statement types. 

## Header Files
AddStmt.h

ArrayVariable.h

CodeEditor.h

CompStmt.h

DeclArrStmt.h

DeclIntStmt.h

EndStmt.h

IntVariable.h

JEqStmt.h

JLessStmt.h

JMoreStmt.h

JumpStmt.h

Label.h

LineNumberArea.h

Mainwindow.h

MovStmt.h

Operand.h

PrintStmt.h

Program.h

ReadStmt.h

Statement.h

Variable.h
  
## Source Files
AddStmt.cpp

ArrayVariable.cpp

CodeEditor.cpp

CompStmt.cpp

DeclArrStmt.cpp

DeclIntStmt.cpp

EndStmt.cpp

IntVariable.cpp

JEqStmt.cpp

JLessStmt.cpp

JMoreStmt.cpp

JumpStmt.cpp

Label.cpp

Main.cpp

Mainwindow.cpp

MovStmt.cpp

Operand.cpp

PrintStmt.cpp

Program.cpp

ReadStmt.cpp

Statement.cpp

Variable.cpp

## System Files
launch.sh

mainwindow.ui

resources.qrc

scapes.pro

## Data
### Input Files
* sampleprog1.scapl
* sampleprog2.scapl

#### Output Files (After Successful Compilation)
* sampleprog1.scapl.o
* sampleprog2.scapl.o
* Untitled.scapl.o (if no file name specified)

### Makefile
* Created during compilation.

## Compilation
### Requirements
* [VirtualBox](https://www.virtualbox.org/wiki/Downloads)
* [VirtualBox Extension Pack](https://www.virtualbox.org/wiki/Downloads)
* [COMP3004-F19 VM](https://carleton.ca/scs/technical-support/virtual-machines/)

### Installation & Launch Instructions
* `tar -xvf scapes.tar`
* `cd scapes`
* `./launch.sh`

## Operating Instructions
* Create new program
  * File > New or click the New icon in shortcut bar
* Save a SCAPL program
  * File > Save As or click the Save icon in shortcut bar
  * Select a location
  * Name file with .scapl extension
  * Click Save button
* Compile new program (without saving)
  * Program > Compile or click the Compile icon in the shortcut bar
  * Untitled.scapl.o will be generated in the default saved location upon successful compilation
  * Dialog box will display compilation status/details
* Compile an existing program that contains SCAPL instructions
  * File > Load or click the Load icon in the shortcut bar
  * Select a .scapl program
  * Program > Compile or click the Compile icon in the shortcut bar
  * A .o file with the file name will be generated upon successful compilation
  * Dialog box will display compilation status/details
* Execute new program (without saving)
  * Program > Execute or click the Execute icon in the shortcut bar
  * The system will attempt to compile the program
  * Untitled.scapl.o will be generated in the default saved location upon successful compilation
  * Dialog box will display compilation status/details
  * Dialog box will display execution status/details
* Execute uncompiled SCAPL program
  * File > Load or click the Load icon in the shortcut bar
  * Select a .scapl program
  * Program > Execute or click the Execute icon in the shortcut bar
  * A .o file with the file name will be generated upon successful compilation
  * Dialog box will display compilation status/details
  * Dialog box will display execution status/details
* Execute an existing program that has been compiled by SCAPES
  * File > Load or click the Load icon in the shortcut bar
  * Select a .o file
  * Program > Execute or click the Execute icon in the shortcut bar
  * Dialog box will display execution status/details
  
* Additional system features:
  * Edit > Copy
  * Edit > Paste
  * Edit > Cut
  * Edit > Undo
  * Edit > Redo

## Reference/Resource
* https://doc.qt.io/qt-5/qtwidgets-widgets-codeeditor-example.html

### Maintainers
* [Alexander N.](https://github.com/alex090nguyen)
* [Emmanuel E.](https://github.com/madrets)
* [Kyle B.](https://github.com/kylebechtel96)
* [Nem Z.](https://github.com/nemzutkovic)
