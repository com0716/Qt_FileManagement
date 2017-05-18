#ifndef GUEST_ADD_DLG_H
#define GUEST_ADD_DLG_H

#include "global_header.h"
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

class GuestAddDlg : public QDialog
{
    Q_OBJECT

public:
    GuestAddDlg(QWidget *parent = 0);
    ~GuestAddDlg();

    bool confirm();
    QString getName();
    int getGrade();
    QString getPassword();

private:
    bool isConfirmed;
    QString name;
    int grade;
    QString password;

    QLabel *pUsernameLabel;
    QLineEdit *pUsernameEdit;
    QLabel *pGradeLabel;
    QComboBox *pGradeComboBox;
    QLabel *pPasswordLabel;
    QLineEdit *pPasswordEdit;

    QPushButton *pConfirmBtn;
    QPushButton *pCancelBtn;

private slots:
    void onConfirm();
    void onCancel();
};

#endif // GUEST_ADD_DLG_H
