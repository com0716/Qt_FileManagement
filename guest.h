#ifndef GUEST_H
#define GUEST_H

#include <QObject>
#include "global_header.h"
#include <QStandardItemModel>

class Guest : public QObject
{
    Q_OBJECT
public:
    explicit Guest(QObject *parent = 0);
    explicit Guest(QString name, int grade, QString password);

    bool insertToDatabase();

    static bool deleteByName(QString name);
    static QStandardItemModel* displayAll();
private:
    QString name;
    int grade;
    QString password;
};
/*
CREATE TABLE guest(
name VARCHAR(64) PRIMARY KEY,
grade TINYINT NOT NULL,
password VARCHAR(200) NOT NULL
);
*/
#endif // GUEST_H
