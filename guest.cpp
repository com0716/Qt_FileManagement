#include "guest.h"
#include "sqltools.h"
#include <QSqlQuery>

Page Guest::fpage;

Guest::Guest(QObject *parent) : QObject(parent)
{

}

Guest::Guest(QString name, int grade, QString password)
{
    this->name = name;
    this->grade = grade;
    this->password = md5(password);
}

bool Guest::insertToDatabase()
{
    SqlTools sqlTools;

    //1 建立连接
    int ret = sqlTools.connect();
    if (ret < 0)
    {
        QMessageBox::information(NULL, "错误", sqlTools.getErrors());
        return false;
    }
    //2 执行sql语句
    QString sql = QString("INSERT INTO guest (name, grade, password) VALUES ('%1', %2, '%3');")
            .arg(name)
            .arg(grade)
            .arg(password);
    ret = sqlTools.executeDml(sql);
    if (ret < 0)
    {
        if (ret == -1)
        {
            QMessageBox::information(NULL, "错误", sqlTools.getErrors());
        }
        return false;
    }

    //3 释放连接
    sqlTools.disconnect();

    return true;
}

bool Guest::deleteByName(QString name)
{
    SqlTools sqlTools;

    //1 建立连接
    int ret = sqlTools.connect();
    if (ret < 0)
    {
        QMessageBox::information(NULL, "错误", sqlTools.getErrors());
        return false;
    }
    //2 执行sql语句
    QString sql = "DELETE FROM guest WHERE name='"+name+"';";
    ret = sqlTools.executeDml(sql);
    if (ret < 0)
    {
        if (ret == -1)
        {
            QMessageBox::information(NULL, "错误", sqlTools.getErrors());
        }
        return false;
    }
    //3 释放连接
    sqlTools.disconnect();

    return true;
}

QStandardItemModel *Guest::displayAll()
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
    QString sql = QString("SELECT name, grade, password FROM guest limit %1, %2;")
                        .arg((fpage.getCurrentPage()-1)*fpage.getPageSize())
                        .arg(fpage.getPageSize());
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

void Guest::getPageInfo()
{
    SqlTools sqlTools;
    int ret = sqlTools.connect();
    if (ret < 0)
    {
        QMessageBox::information(NULL, "错误", sqlTools.getErrors());
        return ;
    }
    QString sql = QString("SELECT COUNT(name) FROM guest;");
    QSqlQuery query = sqlTools.executeDql(sql);

    sqlTools.disconnect();

    if (query.next())
    {
        int totalCount = query.value(0).toInt();
        fpage.setTotalCount(totalCount);
    }
}

void Guest::setCurrentPage(unsigned int page)
{
    fpage.setCurrentPage(page);
}

unsigned int Guest::getCurrentPage()
{
    return fpage.getCurrentPage();
}

unsigned int Guest::getMaxPage()
{
    return fpage.getMaxPage();
}
