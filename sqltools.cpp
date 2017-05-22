#include "sqltools.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlResult>

SqlTools::SqlTools(QObject *parent) : QObject(parent)
{

}

int SqlTools::connect()
{
    //判断是否已经存在默认连接
    if (mysqlDB.contains("qt_sql_default_connection"))
    {
        mysqlDB = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        mysqlDB = QSqlDatabase::addDatabase("QMYSQL");
    }

    mysqlDB.setHostName("localhost");
    //mysqlDB.setHostName("123.207.164.120");
    mysqlDB.setUserName("root");
    mysqlDB.setPassword("com0716");
    mysqlDB.setDatabaseName("file_management");

    if (!mysqlDB.open())
    {
        errors = mysqlDB.lastError().text();
        return -1;
    }

    executeDml("SET NAMES utf8;");

    return 0;
}

int SqlTools::executeDql(const QString sql, QStandardItemModel **pItemModel)
{
    if (pItemModel == NULL)
    {
        errors = "function executeDql error:null pointer.";
        return -1;
    }

    //SELECT
    QSqlQuery query(mysqlDB);
    if (!query.exec(sql))
    {
        errors = query.lastError().text();
        return -1;
    }

    QSqlRecord rec = query.record();
    int rowCount = query.size();    //行数
    int colCount = rec.count();     //列数

    //查询没有结果
    if (rowCount <= 0)
    {
        return -2;
    }

    *pItemModel = new QStandardItemModel(rowCount, colCount);

    //添加头信息
    /*for (int x = 0; x < colCount; x ++)
    {
        (*pItemModel)->setHeaderData(x, Qt::Horizontal, rec.field(x).name());
    }*/

    //添加具体信息
    for (int i = 0; i < rowCount; i ++)
    {
        query.next();
        for (int j = 0; j < colCount; j ++)
        {
            (*pItemModel)->setData((*pItemModel)->index(i, j, QModelIndex()), query.value(j));
        }
    }

    return 0;
}

QSqlQuery SqlTools::executeDql(const QString sql)
{
    QSqlQuery query(mysqlDB);
    if (!query.exec(sql))
    {
        errors = query.lastError().text();
        return QSqlQuery();
    }

    return query;
}

int SqlTools::executeDml(const QString sql)
{
    //INSERT UPDATE DELETE
    QSqlQuery query(mysqlDB);
    if (!query.exec(sql))
    {
        errors = query.lastError().text();
        return -1;
    }

    return 0;
}

int SqlTools::executeDml(QSqlQuery &query)
{
    if (!query.exec())
    {
        errors = query.lastError().text();
        return -1;
    }

    return 0;
}

void SqlTools::disconnect()
{
    errors = "";
    mysqlDB.close();
}

QString SqlTools::getErrors()
{
    return errors;
}
