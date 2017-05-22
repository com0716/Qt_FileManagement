#include "guest_add_dlg.h"
#include <QGridLayout>

GuestAddDlg::GuestAddDlg(QWidget *parent)
    : QDialog(parent)
{
    isConfirmed = false;

    pUsernameLabel = new QLabel(tr("访客昵称"));
    pUsernameEdit = new QLineEdit();
    pGradeLabel = new QLabel(tr("级别"));
    pGradeComboBox = new QComboBox();
    for (int x=1; x<=10; x++)
        pGradeComboBox->addItem(QString("级别%1").arg(x));
    pGradeComboBox->setMaxVisibleItems(5);
    pPasswordLabel = new QLabel(tr("密码"));
    pPasswordEdit = new QLineEdit();
    pPasswordEdit->setEchoMode(QLineEdit::Password);
    pConfirmBtn = new QPushButton(tr("确认"));
    pCancelBtn = new QPushButton(tr("取消"));

    QGridLayout *pMainLayout = new QGridLayout(this);
    pMainLayout->addWidget(pUsernameLabel, 0, 0);
    pMainLayout->addWidget(pUsernameEdit, 0, 1);
    pMainLayout->addWidget(pGradeLabel, 1, 0);
    pMainLayout->addWidget(pGradeComboBox, 1, 1);
    pMainLayout->addWidget(pPasswordLabel, 2, 0);
    pMainLayout->addWidget(pPasswordEdit, 2, 1);


    QGridLayout *pBottomLayout = new QGridLayout();
    pBottomLayout->addWidget(pConfirmBtn, 0, 0);
    pBottomLayout->addWidget(pCancelBtn, 0, 1);
    pBottomLayout->setColumnStretch(0, 1);
    pBottomLayout->setColumnStretch(1, 1);

    pMainLayout->addLayout(pBottomLayout, 3, 0, 1, 2);
    //设置边距
    pMainLayout->setMargin(15);

    //设置间距
    pMainLayout->setSpacing(10);

    //设置对话框大小不可改变
    pMainLayout->setSizeConstraint(QLayout::SetFixedSize);

    //槽函数
    connect(pConfirmBtn, SIGNAL(clicked()), this, SLOT(onConfirm()));
    connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(onCancel()));
}

GuestAddDlg::~GuestAddDlg()
{

}

void GuestAddDlg::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Return || event->key()==Qt::Key_Enter)
    {
        onConfirm();
    }
}

bool GuestAddDlg::confirm()
{
    return this->isConfirmed;
}

QString GuestAddDlg::getName()
{
    return this->name;
}

int GuestAddDlg::getGrade()
{
    return this->grade;
}

QString GuestAddDlg::getPassword()
{
    return this->password;
}

void GuestAddDlg::onConfirm()
{
    name = pUsernameEdit->text().trimmed();
    grade = pGradeComboBox->currentIndex()+1;
    password = pPasswordEdit->text().trimmed();
    if (name.isEmpty() || password.isEmpty())
    {
        QMessageBox::information(NULL, tr("提示"), tr("访客昵称或者密码不能为空"));
    }else
    {
        isConfirmed = true;
        close();
    }
}

void GuestAddDlg::onCancel()
{
    isConfirmed = false;
    close();
}
