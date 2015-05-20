#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include "GLWidget.h"

class QAction;
class QLabel;
class QPushButton;
class GLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void open();

private:
    QLabel *msgLabel;
    QPushButton *loadButton;
    GLWidget* glWindow;
};

#endif // MAINWINDOW_H
