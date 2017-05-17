#ifndef SQLTOOLS_H
#define SQLTOOLS_H

#include "global_header.h"
#include <QObject>
#include <QSqlDatabase>
#include <QSqlResult>
#include <QStandardItemModel>

class SqlTools : public QObject
{
    Q_OBJECT
public:
    explicit SqlTools(QObject *parent = 0);
    //连接数据库
    int connect();

    //数据查询语言DQL SELECT
    int executeDql(const QString sql, QStandardItemModel **pItemModel);

    //数据操作语言DML INSERT UPDATE DELETE
    int executeDml(const QString sql);

    //数据定义语言DDL -- 不做实现
    //数据控制语言DCL -- 不做实现

    //关闭数据库连接
    void disconnect();

    //获得错误信息
    QString getErrors();

private:
    QSqlDatabase mysqlDB;

    QString errors;
};

#endif // SQLTOOLS_H
