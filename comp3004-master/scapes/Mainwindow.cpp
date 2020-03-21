/**
 * File Name: Mainwindow.cpp
 * Class Name: Mainwindow
 * Purpose: 
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

#include "Mainwindow.h"
#include "ui_mainwindow.h"
#include "Program.h"
#include "LineNumberArea.h"

/**
 * Purpose: Creates the founding/parent objects and instances for the QT application.
 *
 * @param Qwidget *parent
 * */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    QCoreApplication::setAttribute(Qt::AA_DontUseNativeDialogs);
    currentFile = "Untitled.scapl";
    setWindowTitle(currentFile);
    IsExecutable = false;
}


/**
 * Purpose: Deletes the ui object created by the MainWindow constructor.
 * */
MainWindow::~MainWindow()
{
    delete ui;
}


/**
 * Purpose: When `New` is clicked, everything in text window is cleared and the user starts anew.
 *
 * @return void
 * */
void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    setWindowTitle("Untitled.scapl");
    currentFile = "Untitled.scapl";
    ui->textEdit->setPlainText(QString());
}


/**
 * Purpose: When `Open` is clicked, a dialog window opens up giving the user the option to open a program in SCAPES.
 *
 * @return void
 * */
void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName();
    QFile file(filename);
    if (filename == "" || !file.open(QFile::ReadOnly | QFile::Text)){
        return;
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setPlainText(text);
    file.close();
}


/**
 * Purpose: When `Save As` is clicked, a dialog window opens up giving the user the option to save their current program to a file.
 *
 * @return void
 * */
void MainWindow::on_actionSave_As_triggered()
{
    QString filename = QFileDialog::getSaveFileName();
    QFile file(filename);
    if (filename == "" || !file.open(QFile::WriteOnly | QFile::Text)){
        return;
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


/**
 * Purpose: When `Exit` is clicked, the SCAPES program terminates.
 *
 * @return void
 * */
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


/**
 * Purpose: When `Copy` is clicked, the text that has been highlighted by the user in SCAPES is copied (ala Ctrl-C).
 *
 * @return void
 * */
void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


/**
 * Purpose: When `Paste` is clicked, whatever has most recently been copied or cut is pasted into the text window (ala Ctrl-V).
 *
 * @return void
 * */
void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


/**
 * Purpose: When `Cut` is clicked, whatever is highlighted by the user in SCAPES is copied and removed (ala Ctrl-X).
 *
 * @return void
 * */
void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


/**
 * Purpose: When `Undo` is clicked, the most recent operation done by the user in SCAPES is undone (ala Ctrl-Z).
 *
 * @return void
 * */
void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


/**
 * Purpose: When `Redo` is clicked, the most recent operation done by the user in SCAPES is redone (ala Ctrl-Shift-Z).
 *
 * @return void
 * */
void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


/**
 * Purpose: When `Compile` is clicked, SCAPES attempts to compile the program that is currently in the text window.
 *
 * @return void
 * */
void MainWindow::on_actionCompile_triggered()
{
    string currentfile = currentFile.toLocal8Bit().constData();
    if (currentfile != "Untitled.scapl" && currentfile.substr(currentfile.length() - 6) != ".scapl"){
        QMessageBox::warning(this, "Scapes", "Please compile a .scapl program!");
        return;
    }
    QString text = ui->textEdit->toPlainText();
    QStringList splitscapl = text.split('\n');
    vector<string> commands;
    string filename = currentFile.toLocal8Bit().constData();
    if (filename == ""){
        filename = "newfile";
    }
    Program prog;
    prog.setFileName(filename);
    for (int i = 0; i < splitscapl.size(); ++i) {
        prog.populateCommands(commands, splitscapl.at(i));
    }
    prog.cleanUpCommands(commands);
    prog.compile(commands);
    prog.clean();
    QString compilelogs = QString::fromStdString(prog.getCompileLogs());
    if (prog.getCompileStatus()){
        IsExecutable = true;
        QMessageBox compile;
        compile.setText("Your SCAPL program compiled successfully! Click on Show Details for more information.");
        compile.setWindowTitle("Scapes: Compilation Output");
        QPixmap pixmap = QPixmap(":/Icons/Scapes.png");
        compile.setWindowIcon(QIcon(pixmap));
        compile.setIcon(QMessageBox::Information);
        compile.setDetailedText(compilelogs);
        compile.exec();
    }
    else{
        IsExecutable = false;
        using namespace std;
        size_t found = currentfile.find_last_of("/\\");
        QString deleteFile = QString::fromStdString(currentfile.substr(found+1));
        QFile file(deleteFile + ".o");
        file.remove();
        QMessageBox compile;
        compile.setText("Your SCAPL program did not compile successfully! Click on Show Details for more information.");
        compile.setWindowTitle("Scapes: Compilation Output");
        QPixmap pixmap = QPixmap(":/Icons/Scapes.png");
        compile.setWindowIcon(QIcon(pixmap));
        compile.setIcon(QMessageBox::Critical);
        compile.setDetailedText(compilelogs);
        compile.exec();
    }
}


/**
 * Purpose: When `Execute` is clicked, SCAPES attempts to execute the program that is currently in the text window.
 *
 * @return void
 * */
void MainWindow::on_actionExecute_triggered()
{
    string currentfile = currentFile.toLocal8Bit().constData();
    if (currentfile != "Untitled.scapl" && currentfile.substr(currentfile.length() - 6) != ".scapl" && currentfile.substr(currentfile.length() - 8) != ".scapl.o"){
        QMessageBox::warning(this, "Scapes", "This file cannot be executed in SCAPES!");
        return;
    }
    if (currentfile.substr(currentfile.length() - 6) == ".scapl"){
        on_actionCompile_triggered();
        if(!IsExecutable){
            return;
        }
    }
    Program prog;
    vector<string> xml_lines;
    QStringList splitxml;
    if (currentfile.substr(currentfile.length() - 8) != ".scapl.o"){
        QFile file(QString::fromStdString(currentfile) + ".o");
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream in(&file);
        QString text = in.readAll();
        file.close();
        splitxml = text.split('\n');
    }
    else{
        QString textinscapes = ui->textEdit->toPlainText();
        splitxml = textinscapes.split('\n');
    }
    for (int i = 0; i < splitxml.size(); ++i) {
        xml_lines.push_back(splitxml[i].toLocal8Bit().constData());
    }
    prog.execute(xml_lines);
    prog.clean();
    QString executeLogs = QString::fromStdString(prog.getExecuteLogs());
    if (prog.getExecuteStatus()){
        QMessageBox execute;
        execute.setText("Your SCAPL program executed successfully! Click on Show Details for more information.");
        execute.setWindowTitle("Scapes: Execute Output");
        QPixmap pixmap = QPixmap(":/Icons/Scapes.png");
        execute.setWindowIcon(QIcon(pixmap));
        execute.setIcon(QMessageBox::Information);
        execute.setDetailedText(executeLogs);
        execute.exec();
    }
    else{
        QMessageBox execute;
        execute.setText("Your SCAPL program did not execute successfully! Click on Show Details for more information.");
        execute.setWindowTitle("Scapes: Execute Output");
        QPixmap pixmap = QPixmap(":/Icons/Scapes.png");
        execute.setWindowIcon(QIcon(pixmap));
        execute.setIcon(QMessageBox::Critical);
        execute.setDetailedText(executeLogs);
        execute.exec();
    }
}
