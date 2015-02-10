#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{

}

void MainWindow::showabout() {
    QDesktopServices::openUrl(QUrl("https://www.google.fr"));
}

void MainWindow::up_upname(QString s) {
    update_name=s;
}

void MainWindow::up_dename(QString s) {
    device_name=s;
}

void MainWindow::update() {
    QString cmd="cp";
    QString cmd2="du";
    QString str=" ../updates/v";
    QString str2=" ../";
    QString str3="/";
    QString tmp=cmd+str+update_name+str2+device_name+str3+update_name;
    QByteArray byte_up=tmp.toUtf8();
    char* final = byte_up.data();
    tmp = cmd2+str+update_name;
    byte_up = tmp.toUtf8();
    char* tm = byte_up.data();
    system(tm);
    std::cout << tm << final << std::endl;
    //system(final);

}
