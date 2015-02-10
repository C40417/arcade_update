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
    QString cmd="/bin/bash -c cp";
    QString cmd2="du";
    QString str=" ../updates/v";
    QString str2=" ../";
    QString str3="/";
    QString tmp=cmd+str+update_name+str2+device_name+str3+update_name;
    QString tm = cmd2+str+update_name;
    shell.start(tm);
    shell.waitForFinished(-1);
    QString stdout = shell.readAllStandardOutput();
    labout.setMinimumSize(400,400);
    labout.setText(stdout);
    labout.show();
    //system(final);

}
