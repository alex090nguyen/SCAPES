/* * * * * * * * * * * * * * * * * * * * * * * * * */
/*  Program: SCAPES                                */
/*  Team: DORCS                                    */
/*  Team Members:                                  */
/*  - Alexander Nguyen (100908039)                 */
/*  - Emmanuel Elite (100878873)                   */
/*  - Kyle Bechtel (100979669)                     */
/*  - Nem Zutkovic (101085982)                     */
/*  Date: 12/05/2019                               */
/* * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Mainwindow.h"
#include <QApplication>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
