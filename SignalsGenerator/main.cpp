#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(w.windowFlags() | Qt::WindowStaysOnTopHint);//设置窗口最前
    //  w.setWindowFlags(w.windowFlags() &~ Qt::WindowStaysOnTopHint);//取消窗口最前
    w.show();

    return a.exec();
}
