#include "admin.h"
#include "sqltools.h"

Admin::Admin(QString name, QString password)
{
    this->name = name;

    //MD5加密
    this->password = md5(password);
}

bool Admin::isLogin()
{
    //1 数据库操作
    SqlTools sqlTools;
    QStandardItemModel *pItemModel = NULL;

    //1.1 建立连接
    int ret = sqlTools.connect();
    if (ret < 0)
    {
        QMessageBox::information(NULL, "错误", sqlTools.getErrors());
        return false;
    }
    //1.2 执行sql语句
    QString sql = QString("SELECT password FROM admin WHERE name='%1';").arg(this->name);
    ret = sqlTools.executeDql(sql, &pItemModel);
    if (ret < 0)
    {
        if (ret == -1)
        {
            QMessageBox::information(NULL, "错误", sqlTools.getErrors());
        }else if (ret == -2)
        {
            QMessageBox::information(NULL, "错误", "该用户名不存在");
        }
        return false;
    }
    //1.3 释放连接
    sqlTools.disconnect();

    //2 判断结果
    const QString sqlPassword = pItemModel->index(0,0).data(0).toString();
    delete pItemModel; pItemModel = NULL;
    if (sqlPassword != this->password)
    {
        return false;
    }

    return true;
}

QStandardItemModel *Admin::guestDisplay()
{
    //1 数据库操作
    SqlTools sqlTools;
    QStandardItemModel *pItemModel = NULL;

    //1.1 建立连接
    int ret = sqlTools.connect();
    if (ret < 0)
    {
        QMessageBox::information(NULL, "错误", sqlTools.getErrors());
        return NULL;
    }
    //1.2 执行sql语句
    QString sql = "SELECT name, grade, password FROM guest;";
    ret = sqlTools.executeDql(sql, &pItemModel);
    if (ret < 0)
    {
        if (ret == -1)
        {
            QMessageBox::information(NULL, "错误", sqlTools.getErrors());
        }else if (ret == -2)
        {
            QMessageBox::information(NULL, "错误", "访客表没有符合要求的信息");
        }
        return NULL;
    }
    //1.3 释放连接
    sqlTools.disconnect();

    pItemModel->setHeaderData(0, Qt::Horizontal, tr("访客姓名"));
    pItemModel->setHeaderData(1, Qt::Horizontal, tr("级别"));
    pItemModel->setHeaderData(2, Qt::Horizontal, tr("密码"));

    return pItemModel;
}

QStandardItemModel *Admin::fileDisplay()
{
    //1 数据库操作
    SqlTools sqlTools;
    QStandardItemModel *pItemModel = NULL;

    //1.1 建立连接
    int ret = sqlTools.connect();
    if (ret < 0)
    {
        QMessageBox::information(NULL, "错误", sqlTools.getErrors());
        return NULL;
    }
    //1.2 执行sql语句
    QString sql = "SELECT fpath, fname, fdesc, date, uploader, download_count, size FROM file;";
    ret = sqlTools.executeDql(sql, &pItemModel);
    if (ret < 0)
    {
        if (ret == -1)
        {
            QMessageBox::information(NULL, "错误", sqlTools.getErrors());
        }else if (ret == -2)
        {
            QMessageBox::information(NULL, "错误", "文件表没有符合要求的信息");
        }
        return NULL;
    }
    //1.3 释放连接
    sqlTools.disconnect();

    pItemModel->setHeaderData(0, Qt::Horizontal, tr("文件目录"));
    pItemModel->setHeaderData(1, Qt::Horizontal, tr("文件名"));
    pItemModel->setHeaderData(2, Qt::Horizontal, tr("文件描述"));
    pItemModel->setHeaderData(3, Qt::Horizontal, tr("上传时间"));
    pItemModel->setHeaderData(4, Qt::Horizontal, tr("上传人"));
    pItemModel->setHeaderData(5, Qt::Horizontal, tr("下载次数"));
    pItemModel->setHeaderData(6, Qt::Horizontal, tr("文件大小"));

    return pItemModel;
}
