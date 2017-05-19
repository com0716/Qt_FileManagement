#ifndef FILE_ADD_DLG_H
#define FILE_ADD_DLG_H

#include "global_header.h"
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>

class FileAddDlg : public QDialog
{
    Q_OBJECT

public:
    FileAddDlg(QWidget *parent = 0);
    ~FileAddDlg();

    bool confirm();
    QString getFileName();
    QString getFileDesc();

private:
    bool isConfirmed;
    QString fname;
    QString fdesc;

    QLabel *pFileLabel;
    QLineEdit *pFileNameEdit;
    QPushButton *pOpenFileBtn;

    QLabel *pFileDesc;
    QLineEdit *pFileDescEdit;

    QLabel *pPreviewLabel;
    QLabel *pImageLabel;

    QPushButton *pConfirmBtn;
    QPushButton *pCancelBtn;

private slots:
    void onConfirm();
    void onCancel();
    void onOpenFile();
};

#endif // FILE_ADD_DLG_H
