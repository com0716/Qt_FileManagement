#ifndef FILE_H
#define FILE_H

#include <QObject>
#include "global_header.h"
#include <QStandardItemModel>
#include <QByteArray>

class File : public QObject
{
    Q_OBJECT
public:
    explicit File(QObject *parent = 0);
    explicit File(QString fid, QString fname, QString fdesc, int fsize, QString fdate, QString uploader, int downloadCount);
    bool insertToDatabase();

    static bool deleteById(QString fid);
    static QStandardItemModel* displayAll();
    static QByteArray getFileSrcById(QString fid);

private:
    QString fid;
    QString fname;
    QString ftype;
    QString fdesc;
    int fsize;
    QString fdate;
    QString uploader;
    int downloadCount;
};

#endif // FILE_H
