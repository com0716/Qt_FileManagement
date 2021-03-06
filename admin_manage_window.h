#ifndef ADMIN_MANAGE_WINDOW_H
#define ADMIN_MANAGE_WINDOW_H

#include "global_header.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QMdiArea>
#include "admin.h"
#include <QAction>
#include <QMenuBar>
#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

//可操作表单类型定义
enum {
    CURRENT_TABLE_GUEST = 0x00,
#define CURRENT_TABLE_GUEST CURRENT_TABLE_GUEST
    CURRENT_TABLE_FILE,
#define CURRENT_TABLE_FILE CURRENT_TABLE_FILE
};
/*
2 管理员-界面设计
    2.1 登录界面
        用户名
        密码
    2.2 管理界面
        2.2.1 管理菜单
            查看访客表
            查看文件表

            退出
        2.2.2 操作菜单
            访客表的增删改查
            文件表的增删改查
        2.2.3 窗口菜单行为
            层叠
            并列
        2.2.4 帮助菜单
            帮助
            关于
*/
class AdminManageWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AdminManageWindow(Admin *pAdmin);
    void closeEvent(QCloseEvent *event);

private:
    unsigned int uCurrentTableId;
    //表的标题
    QLabel *pTableLabel;

    //按键
    QPushButton *pAddBtn;
    QPushButton *pDeleteBtn;
    QPushButton *pUpdateBtn;
    QPushButton *pRetrieveBtn;

    //分页按键
    QPushButton *pFirstPageBtn;
    QPushButton *pPrePageBtn;
    QPushButton *pNextPageBtn;
    QPushButton *pLastPageBtn;
    QComboBox *pJumpToPageComboBox;

    //图片显示区
    QLabel *pImageLabel;


    //管理员信息
    Admin *pAdmin;

    //显示框架
    //QMdiArea *pMdiArea;
    QTableView *pTableView;

    //管理菜单及菜单行为
    QMenu *pAdminMenu;
    QAction *pGuestDisplayAction;
    QAction *pFileDisplayAction;
    QAction *pExitAction;

    //操作菜单及菜单行为
    QMenu *pOperatorMenu;
    QAction *pAddAction;
    QAction *pDeleteAction;
    QAction *pUpdateAction;
    QAction *pRetrieveAction;

    //帮助菜单及菜单行为
    QMenu *pHelpMenu;
    QAction *pHelpAction;
    QAction *pAboutAction;

private:
    void createActions();
    void createMenus();

private slots:
    void onGuestDisplay();
    void onFileDisplay();
    void onExit();

    void onHelp();
    void onAbout();

    //按键事件槽函数
    void onAddBtnClicked();
    void onDeleteBtnClicked();
    void onUpdateBtnClicked();
    void onRetrieveBtnClicked();

    void onFirstPageBtnClicked();
    void onPrePageBtnClicked();
    void onNextPageBtnClicked();
    void onLastPageBtnClicked();
    void onJumpToPageComboBoxIndexChanged();

    void onTableViewClicked();
};

#endif // ADMIN_MANAGE_WINDOW_H
