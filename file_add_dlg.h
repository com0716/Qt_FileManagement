#ifndef FILE_ADD_DLG_H
#define FILE_ADD_DLG_H

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
    QString getFilePath();
    QString getFileDesc();
    int getFileSize();

private:
    bool isConfirmed;
    QString fpath;
    QString fname;
    QString fdesc;
    int size;

    QLabel *pFileLabel;
    QLineEdit *pFileNameEdit;
    QPushButton *pOpenFileBtn;

    QLabel *pFileDesc;
    QTextEdit *pFileDescText;

    QPushButton *pConfirmBtn;
    QPushButton *pCancelBtn;

private slots:
    void onConfirm();
    void onCancel();
    void onOpenFile();
};

#endif // FILE_ADD_DLG_H
