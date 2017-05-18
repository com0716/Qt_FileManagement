#ifndef FILE_H
#define FILE_H

#include <QObject>
#include "global_header.h"
#include <QStandardItemModel>

class File : public QObject
{
    Q_OBJECT
public:
    explicit File(QObject *parent = 0);
    explicit File(QString fpath, QString fname, QString fdesc, QString date, QString uploader, int downloadCount, int size);
    bool insertToDatabase();

    static bool deleteByName(QString name);
    static QStandardItemModel* displayAll();

private:
    QString fpath;
    QString fname;
    QString fdesc;
    QString date;
    QString uploader;
    int downloadCount;
    int size;
};
/*
CREATE TABLE file(
fpath VARCHAR(256) NOT NULL,
fname VARCHAR(256) NOT NULL,
fdesc VARCHAR(256),
date DATETIME PRIMARY KEY,
uploader VARCHAR(64) NOT NULL,
download_count INT NOT NULL,
size INT NOT NULL
);
*/
#endif // FILE_H
