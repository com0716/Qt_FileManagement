#include "file.h"
#include "sqltools.h"
#include <QSqlQuery>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QVariant>

Page File::fpage;

File::File(QObject *parent) : QObject(parent)
{

}

File::File(QString fid, QString fname, QString fdesc, int fsize, QString fdate, QString uploader, int downloadCount)
{
    this->fid = fid;
    this->fname = fname;
    this->fdesc = fdesc;
    this->fsize = fsize;
    this->fdate = fdate;
    this->uploader = uploader;
    this->downloadCount = downloadCount;
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

    //文件读取
    QByteArray data;
    QFile* file = new QFile(this->fname); //fileName为二进制数据文件名
    file->open(QIODevice::ReadOnly);
    data = file->readAll();
    file->close();
    QVariant var(data);
    fsize = file->size();
    fname = QFileInfo(this->fname).fileName();
    ftype = QFileInfo(this->fname).suffix();


    //2 执行sql语句
    QString sql = QString("INSERT INTO file_blob "
                          "(fid, fname, ftype, fdesc, fsize, fdate, uploader, download_count, fsrc) "
                          "VALUES "
                          "(:fid, :fname, :ftype, :fdesc, :fsize, NOW(), :uploader, :download_count, :fsrc);");
    QSqlQuery query;
    query.exec("SET NAMES utf8;");

    query.prepare(sql);
    query.bindValue(":fid", this->fid);
    query.bindValue(":fname", this->fname);
    query.bindValue(":ftype", this->ftype);
    query.bindValue(":fdesc", this->fdesc);
    query.bindValue(":fsize", this->fsize);
    query.bindValue(":uploader", this->uploader);
    query.bindValue(":download_count", 0);
    query.bindValue(":fsrc", var);


    ret = sqlTools.executeDml(query);
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

bool File::deleteById(QString fid)
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
    QString sql = "DELETE FROM file_blob WHERE fid='"+fid+"';";
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
    QString sql = QString ("SELECT fid, fname, ftype, fdesc, fsize, fdate, "
                           "uploader, download_count FROM file_blob "
                           "ORDER BY fdate DESC LIMIT %1, %2;")
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
            QMessageBox::information(NULL, tr("错误"), tr("文件表没有符合要求的信息"));
        }
        return NULL;
    }
    //1.3 释放连接
    sqlTools.disconnect();

    pItemModel->setHeaderData(0, Qt::Horizontal, tr("文件编号"));
    pItemModel->setHeaderData(1, Qt::Horizontal, tr("文件名"));
    pItemModel->setHeaderData(2, Qt::Horizontal, tr("文件类型"));
    pItemModel->setHeaderData(3, Qt::Horizontal, tr("文件描述"));
    pItemModel->setHeaderData(4, Qt::Horizontal, tr("文件大小"));
    pItemModel->setHeaderData(5, Qt::Horizontal, tr("上传时间"));
    pItemModel->setHeaderData(6, Qt::Horizontal, tr("上传人"));
    pItemModel->setHeaderData(7, Qt::Horizontal, tr("下载次数"));

    return pItemModel;
}

QByteArray File::getFileSrcById(QString fid)
{
    //1 数据库操作
    SqlTools sqlTools;

    //1.1 建立连接
    int ret = sqlTools.connect();
    if (ret < 0)
    {
        QMessageBox::information(NULL, "错误", sqlTools.getErrors());
        return NULL;
    }
    //1.2 执行sql语句
    QString sql = QString("SELECT fsrc FROM file_blob WHERE fid='%1';").arg(fid);
    QSqlQuery query = sqlTools.executeDql(sql);

    //1.3 释放连接
    sqlTools.disconnect();

    if (query.next())
    {
        return query.value(0).toByteArray();
    }

    return NULL;
}

void File::getPageInfo()
{
    SqlTools sqlTools;
    int ret = sqlTools.connect();
    if (ret < 0)
    {
        QMessageBox::information(NULL, "错误", sqlTools.getErrors());
        return ;
    }
    QString sql = QString("SELECT COUNT(fid) FROM file_blob;");
    QSqlQuery query = sqlTools.executeDql(sql);

    sqlTools.disconnect();

    if (query.next())
    {
        int totalCount = query.value(0).toInt();
        fpage.setTotalCount(totalCount);
    }
}

void File::setCurrentPage(unsigned int page)
{
    fpage.setCurrentPage(page);
}

unsigned int File::getCurrentPage()
{
    return fpage.getCurrentPage();
}

unsigned int File::getMaxPage()
{
    return fpage.getMaxPage();
}
