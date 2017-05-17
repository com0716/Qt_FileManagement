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
    //查询相关的guest信息
    QStandardItemModel *guestDisplay();
    QStandardItemModel *fileDisplay();
    void deleteFileByName(QString name);
    void deleteGuestByName(QString name);

private:
    int id;
    QString name;
    QString password;
};

#endif // ADMIN_H
