#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global_header.h"
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent * event);//键盘事件捕捉

private:
    QLabel *pUsernameLabel;
    QLineEdit *pUsernameEdit;
    QLabel *pPasswordLabel;
    QLineEdit *pPasswordEdit;
    QPushButton *pLoginBtn;
    QPushButton *pResetBtn;

private slots:
    void onLogin();
    void onReset();
};

#endif // MAINWINDOW_H
