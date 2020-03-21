 /**
 * File Name: CodeEditor.h
 * Class Name: CodeEditor
 * Purpose: Header file for CodeEditor class
 *
 * Team: DORCS
 * Team Members:
 * 	- Alexander Nguyen (100908039)
 *	- Emmanuel Elite (100878873)
 *	- Kyle Bechtel (100979669)
 *	- Nem Zutkovic (101085982)
 *
 * Reference/Resource
 * https://doc.qt.io/qt-5/qtwidgets-widgets-codeeditor-example.html
 *
 * Date: 12/05/2019
 * */

#ifndef QTEXTEDITHIGHLIGHER_H
#define QTEXTEDITHIGHLIGHER_H

#include <QPlainTextEdit>
#include <QWidget>
#include <QScrollBar>
#include <QTextBlock>
#include <QPainter>
#include <QAbstractTextDocumentLayout>
#include <QRectF>

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
};

#endif // QTEXTEDITHIGHLIGHER_H
