#include "file.h"
#include "sqltools.h"

File::File(QObject *parent)
{

}

File::File(QString fpath, QString fname, QString fdesc, QString date, QString uploader, int downloadCount, int size)
{
    this->fpath = fpath;
    this->fname = fname;
    this->fdesc = fdesc;
    this->date = date;
    this->uploader = uploader;
    this->downloadCount = downloadCount;
    this->size = size;
}

bool File::insertToDatabase()
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
    QString sql = QString("INSERT INTO file "
                          "(fpath, fname, fdesc, date, uploader, download_count, size) "
                          "VALUES ('%1', '%2', '%3', NOW(), '%4', %5, %6);")
            .arg(fpath)
            .arg(fname)
            .arg(fdesc)
            .arg(uploader)
            .arg(downloadCount)
            .arg(size);
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

bool File::deleteByName(QString name)
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
    QString sql = "DELETE FROM file WHERE name='"+name+"';";
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

QStandardItemModel *File::displayAll()
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
