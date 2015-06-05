#include "mainwindow.h"
#include <iostream>
#include <QRegExp>

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

void MainWindow::isfinished(int exitCode, QProcess::ExitStatus exitState) {
    if (exitCode==0)
        update_finished=true;
    std::cout << "coucou" << std::endl;
}

void MainWindow::read_output() {
    stdout = monitor.readChannel();
    current_taille = (stdout.remove(QRegExp("\s*../.*"))).toInt();
    if (current_taille!=0)
        std::cout << update_finished << ";" << current_taille << std::endl;
}

void MainWindow::update() {
    update_finished=false;
    QString cmd="cp";
    QString cmd2="du";
    QString cmd3="watch ";
    QString str=" ../updates/v";
    QString str2=" ../";
    QString str3="/";
    QString cp=cmd+str+update_name+str2+device_name+str3+update_name;
    QString du=cmd2+str+update_name;
    QString watch=cmd2+str2+device_name+str3+update_name;
    shell.start(du);
    shell.waitForFinished(-1);
    QString stdout = shell.readAllStandardOutput();
    int total_taille = (stdout.remove(QRegExp("\s*../.*"))).toInt();
    shell.start(cp);
    monitor.setReadChannel(QProcess::StandardOutput);
    monitor.start(watch);
    labout.setText("not_started");
    labout.show();
    shell.waitForStarted();
    QObject::connect(&shell, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(isfinished(int,QProcess::ExitStatus)));
    QObject::connect(this, SIGNAL(current_progress(int)), &progress, SLOT(setValue(int)));
    QObject::connect(&monitor, SIGNAL(readyReadStandardOutput()), this, SLOT(read_output()));
    emit current_progress(current_taille/total_taille);



    //system(final);

}
