#include "admin_manage_window.h"
#include "sqltools.h"
#include <QStandardItemModel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QMdiSubWindow>
#include <QHeaderView>

AdminManageWindow::AdminManageWindow(Admin *pAdmin) : pAdmin(pAdmin)
{
    setWindowTitle(tr("管理员-文件管理"));
    resize(800, 600);

    QWidget *pWidget = new QWidget();
    this->setCentralWidget(pWidget);

    QGridLayout *pMainLayout = new QGridLayout(pWidget);

    /*
    pMdiArea = new QMdiArea();
    pMdiArea->setBackground(Qt::NoBrush);
    pMdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    pMdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    */
    pTableView = new QTableView();
    pTableView->setAttribute(Qt::WA_DeleteOnClose);
    pTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pTableView->showMaximized();

    pAddBtn = new QPushButton(tr("增加条目"));
    pDeleteBtn = new QPushButton(tr("删除条目"));
    pUpdateBtn = new QPushButton(tr("更改条目"));
    pRetrieveBtn = new QPushButton(tr("查询条目"));

    //界面右侧布局
    QVBoxLayout *pRightLayout = new QVBoxLayout();
    pRightLayout->addWidget(pAddBtn, 0);
    pRightLayout->addWidget(pDeleteBtn, 1);
    pRightLayout->addWidget(pUpdateBtn, 2);
    pRightLayout->addWidget(pRetrieveBtn, 3);

    //左侧
    pMainLayout->addWidget(pTableView, 0, 0, 2, 1);
    //右侧
    pMainLayout->addLayout(pRightLayout, 0, 1);

    onGuestDisplay();

    createActions();
    createMenus();

    //槽函数
    connect(pAddBtn, SIGNAL(clicked()), this, SLOT(onAddBtnClicked()));
}

void AdminManageWindow::closeEvent(QCloseEvent *event)
{
    //1 使用函数的返回值判断按下的键是什么
    QMessageBox::StandardButton button;

    button = QMessageBox::question(this,
                                   tr("提示"),
                                   tr("是否退出程序？"),
                                   QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

void AdminManageWindow::createActions()
{
    //1 管理菜单行为建立
    //1.1 访客信息显示
    pGuestDisplayAction = new QAction(tr("显示访客表"), this);
    pGuestDisplayAction->setShortcut(tr("ctrl+u"));
    connect(pGuestDisplayAction, SIGNAL(triggered()), this, SLOT(onGuestDisplay()));

    //1.2 文件信息显示
    pFileDisplayAction = new QAction(tr("显示文件表"), this);
    pFileDisplayAction->setShortcut(tr("ctrl+d"));
    connect(pFileDisplayAction, SIGNAL(triggered()), this, SLOT(onFileDisplay()));

    //1.3 退出行为
    pExitAction = new QAction(tr("退出"), this);
    pExitAction->setShortcut(tr("ctrl+w"));
    connect(pExitAction, SIGNAL(triggered()), this, SLOT(onExit()));

    /*
    //3 窗口菜单行为建立
    //3.1 窗口层叠
    pCascadeAction = new QAction(tr("层叠"), this);
    pCascadeAction->setShortcut(tr("ctrl+q"));
    connect(pCascadeAction, SIGNAL(triggered()), this, SLOT(onCascade()));

    //3.2 窗口并列
    pTileAction = new QAction(tr("并列"), this);
    pTileAction->setShortcut(tr("ctrl+r"));
    connect(pTileAction, SIGNAL(triggered()), this, SLOT(onTile()));
    */

    //4 帮助菜单行为建立
    //4.1 帮助
    pHelpAction = new QAction(tr("帮助"), this);
    pHelpAction->setShortcut(tr("ctrl+s"));
    connect(pHelpAction, SIGNAL(triggered()), this, SLOT(onHelp()));

    //4.2 关于
    pAboutAction = new QAction(tr("关于"), this);
    pAboutAction->setShortcut(tr("ctrl+t"));
    connect(pAboutAction, SIGNAL(triggered()), this, SLOT(onAbout()));
}

void AdminManageWindow::createMenus()
{
    //1 管理菜单
    pAdminMenu = menuBar()->addMenu(tr("管理"));
    pAdminMenu->addAction(pGuestDisplayAction);
    pAdminMenu->addAction(pFileDisplayAction);
    pAdminMenu->addSeparator();//加入分隔符
    pAdminMenu->addAction(pExitAction);

    /*//3 窗口菜单
    pWindowMenu= menuBar()->addMenu(tr("窗口"));
    pWindowMenu->addAction(pCascadeAction);
    pWindowMenu->addAction(pTileAction);
    */

    //4 帮助菜单
    pHelpMenu= menuBar()->addMenu(tr("帮助"));
    pHelpMenu->addAction(pHelpAction);
    pHelpMenu->addSeparator();//加入分隔符
    pHelpMenu->addAction(pAboutAction);
}

void AdminManageWindow::onGuestDisplay()
{
    QStandardItemModel *pItemModel = pAdmin->guestDisplay();
    if (pItemModel == NULL)
    {
        return ;
    }
    /*QTableView *pTableView = new QTableView();

    pMdiArea->addSubWindow(pTableView);
    pTableView->setAttribute(Qt::WA_DeleteOnClose);
    pTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pTableView->setWindowTitle("访客信息表");
    pTableView->setModel(pItemModel);
    pTableView->showMaximized();*/

    pTableView->setWindowTitle("访客信息表");
    pTableView->setModel(pItemModel);
}

void AdminManageWindow::onFileDisplay()
{
    QStandardItemModel *pItemModel = pAdmin->fileDisplay();
    if (pItemModel == NULL)
    {
        return ;
    }
    /*QTableView *pTableView = new QTableView();

    pMdiArea->addSubWindow(pTableView);
    pTableView->setAttribute(Qt::WA_DeleteOnClose);
    pTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pTableView->setWindowTitle("文件信息表");
    pTableView->setModel(pItemModel);
    pTableView->showMaximized();*/

    pTableView->setWindowTitle("文件信息表");
    pTableView->setModel(pItemModel);
}

void AdminManageWindow::onExit()
{
    close();
}

void AdminManageWindow::onCascade()
{
    //pMdiArea->cascadeSubWindows();
}

void AdminManageWindow::onTile()
{
    //pMdiArea->tileSubWindows();
}

void AdminManageWindow::onHelp()
{
    QMessageBox::information(this, "帮助", "自学");
}

void AdminManageWindow::onAbout()
{
    QMessageBox::about(this, "关于", "版权所有，免费使用");
}

void AdminManageWindow::onAddBtnClicked()
{
    int row = pTableView->currentIndex().row();
    qDebug()<<row;
}

