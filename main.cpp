#include "mainwindow.h"
#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.hide();
    Dialog login;
    login.setWindowTitle("登录");
    // 登录通过后切换至主页面
    if(login.exec() == QDialog::Accepted){
        w.setWindowTitle("学籍管理系统");
        w.show();
        return a.exec();
    }
    else return 0;
}
