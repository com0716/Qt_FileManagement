#ifndef GLOBAL_HEADER_H
#define GLOBAL_HEADER_H

/*#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
*/
#include <QDebug>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QCryptographicHash>
#include <QMainWindow>
#include <QApplication>

inline QString md5(QString input)
{
    QByteArray bb;
    bb = QCryptographicHash::hash(input.toLatin1(), QCryptographicHash::Md5);
    return bb.toHex();
}

inline void moveToCenter(QMainWindow &w)
{

    QDesktopWidget *pDesktop = QApplication::desktop();
    w.move((pDesktop->width()-w.width())/2,
           (pDesktop->height()-w.height())/2);
}

#endif // GLOBAL_HEADER_H
