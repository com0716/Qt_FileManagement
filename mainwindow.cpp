#include "mainwindow.h"
#include <QGridLayout>
#include "admin.h"
#include "admin_manage_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *pWidget = new QWidget();
    this->setCentralWidget(pWidget);

    pUsernameLabel = new QLabel(tr("用户名"));
    pUsernameEdit = new QLineEdit();
    pPasswordLabel = new QLabel(tr("密码"));
    pPasswordEdit = new QLineEdit();
    pPasswordEdit->setEchoMode(QLineEdit::Password);
    pLoginBtn = new QPushButton(tr("登录"));
    pResetBtn = new QPushButton(tr("清除输入"));

    QGridLayout *pMainLayout = new QGridLayout(pWidget);
    pMainLayout->addWidget(pUsernameLabel, 0, 0);
    pMainLayout->addWidget(pUsernameEdit, 0, 1);
    pMainLayout->addWidget(pPasswordLabel, 1, 0);
    pMainLayout->addWidget(pPasswordEdit, 1, 1);


    QGridLayout *pBottomLayout = new QGridLayout();
    pBottomLayout->addWidget(pLoginBtn, 0, 0);
    pBottomLayout->addWidget(pResetBtn, 0, 1);
    pBottomLayout->setColumnStretch(0, 1);
    pBottomLayout->setColumnStretch(1, 1);

    pMainLayout->addLayout(pBottomLayout, 2, 0, 1, 2);
    //设置边距
    pMainLayout->setMargin(15);

    //设置间距
    pMainLayout->setSpacing(10);

    //设置对话框大小不可改变
    pMainLayout->setSizeConstraint(QLayout::SetFixedSize);

    //槽函数
    connect(pLoginBtn, SIGNAL(clicked()), this, SLOT(onLogin()));
    connect(pResetBtn, SIGNAL(clicked()), this, SLOT(onReset()));
}

MainWindow::~MainWindow()
{

}

//管理员登录
void MainWindow::onLogin()
{
    //1 获取登录用户的用户名和密码
    QString username = pUsernameEdit->text().trimmed();
    QString password = pPasswordEdit->text().trimmed();

    //2 验证用户名和密码的合法性
    if (username=="" || password=="")
    {
        QMessageBox::information(NULL, tr("警告"), tr("用户名或密码不能为空"));
        return ;
    }

    Admin *pAdmin = new Admin(username, password);
    if (pAdmin->isLogin())
    {
        //验证通过，成功登录，进入管理员操作界面
        this->close();

        //先关闭这个窗口，然后创建新的窗口，暂时这样处理，不知道是不是会造成资源的浪费
        AdminManageWindow *pManageWindow = new AdminManageWindow(pAdmin);
        pManageWindow->show();
        moveToCenter(*pManageWindow);
    }
    else
    {
        onReset();
    }
}

void MainWindow::onReset()
{
    pUsernameEdit->setText("");
    pPasswordEdit->setText("");
}

//键盘时间捕捉
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Return || event->key()==Qt::Key_Enter)
    {
        onLogin();
    }
}
