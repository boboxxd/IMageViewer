#include "mainwindow.h"
#include <QApplication>
#include <QObject>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QObject::tr("图片浏览器-江苏濠汉信息技术有限公司"));
    w.show();
    return a.exec();
}
