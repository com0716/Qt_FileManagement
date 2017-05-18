#include "file_add_dlg.h"
#include <QGridLayout>
#include <QFileDialog>

FileAddDlg::FileAddDlg(QWidget *parent)
    : QDialog(parent)
{
    isConfirmed = false;

    pFileLabel = new QLabel(tr("上传文件"));
    pFileNameEdit = new QLineEdit();
    pOpenFileBtn = new QPushButton(tr("打开文件"));

    pFileDesc = new QLabel(tr("添加描述"));
    pFileDescText = new QTextEdit();

    pConfirmBtn = new QPushButton(tr("确认"));
    pCancelBtn = new QPushButton(tr("取消"));

    QGridLayout *pMainLayout = new QGridLayout(this);
    pMainLayout->addWidget(pFileLabel, 0, 0);
    pMainLayout->addWidget(pFileNameEdit, 0, 1);
    pMainLayout->addWidget(pOpenFileBtn, 0, 2);
    pMainLayout->addWidget(pFileDesc, 1, 0);
    pMainLayout->addWidget(pFileDescText, 1, 1, 1, 2);

    QGridLayout *pBottomLayout = new QGridLayout();
    pBottomLayout->addWidget(pConfirmBtn, 0, 0);
    pBottomLayout->addWidget(pCancelBtn, 0, 1);
    pBottomLayout->setColumnStretch(0, 1);
    pBottomLayout->setColumnStretch(1, 1);

    pMainLayout->addLayout(pBottomLayout, 2, 1, 1, 2);
    //设置边距
    pMainLayout->setMargin(15);
    //设置间距
    pMainLayout->setSpacing(10);
    //设置对话框大小不可改变
    pMainLayout->setSizeConstraint(QLayout::SetFixedSize);

    //槽函数
    connect(pOpenFileBtn, SIGNAL(clicked()), this, SLOT(onOpenFile()));
    connect(pConfirmBtn, SIGNAL(clicked()), this, SLOT(onConfirm()));
    connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(onCancel()));
}

FileAddDlg::~FileAddDlg()
{

}

bool FileAddDlg::confirm()
{
    return this->isConfirmed;
}

QString FileAddDlg::getFileName()
{
    return this->fname;
}

QString FileAddDlg::getFilePath()
{
    return this->fpath;
}

QString FileAddDlg::getFileDesc()
{
    return this->fdesc;
}

int FileAddDlg::getFileSize()
{
    return this->size;
}

void FileAddDlg::onConfirm()
{
    /*name = pUsernameEdit->text().trimmed();
    grade = pGradeComboBox->currentIndex()+1;
    password = pPasswordEdit->text().trimmed();
    if (name == "" || password == "")
    {
        QMessageBox::information(NULL, tr("提示"), tr("访客昵称或者密码不能为空"));
    }else
    {
        isConfirmed = true;
        close();
    }*/

}

void FileAddDlg::onCancel()
{
    isConfirmed = false;
    close();
}

void FileAddDlg::onOpenFile()
{
    QString filename=QFileDialog::getOpenFileName(this,
                                             tr("选择要上传的文件"),
                                             "",
                                             tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(filename.isEmpty())
    {
        return;
    }

    pFileNameEdit->setText(filename);


}
