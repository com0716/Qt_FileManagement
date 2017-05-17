#include "mainwindow.h"
#include "global_header.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    moveToCenter(w);

    return a.exec();
}
