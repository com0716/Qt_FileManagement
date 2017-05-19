#ifndef ADMIN_H
#define ADMIN_H

#include "global_header.h"
#include <QObject>
#include <QStandardItemModel>

class Admin : public QObject
{
    Q_OBJECT
public:
    explicit Admin(QString name, QString password);

    bool isLogin();
    QString getName();
    int getId();

private:
    int id;
    QString name;
    QString password;
};

#endif // ADMIN_H
