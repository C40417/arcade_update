#include "mainwindow.h"
#include <iostream>
#include <QFileInfo>
#include <QFile>

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

void MainWindow::set_dest(QString s) {
    dst_dir=s;
}

void MainWindow::set_src(QString s) {
    src_dir=s;
}

void MainWindow::set_address(QString s) {
    device_address=s;
}

void MainWindow::isfinished(int exitCode, QProcess::ExitStatus exitState) {
    if (exitCode==0)
        update_finished=true;
    std::cout << "coucou" << std::endl;
}

void MainWindow::update() {
    QProcess* sshfs= new QProcess;
    QString coucou = "sshfs "+device_address+" "+dst_dir;
    std::cout << coucou.toUtf8().constData() << std::endl;
    sshfs->start("sshfs "+device_address+" "+dst_dir);
    std::cout << sshfs->pid() << std::endl;
    if (sshfs->state() == QProcess::NotRunning) {
        update_finished=false;
        QFileInfo src_info(src_dir+"updates/v"+update_name);
        QFileInfo dst_info(dst_dir+"/v"+update_name);
        QFile src_file(src_dir+"updates/v"+update_name);
        QFile dst_file(dst_dir+device_name+"/v"+update_name);

        QDataStream src_stream(&src_file);
        QDataStream dst_stream(&dst_file);

        char* data =new char[2048];

        qint64 src_size=src_info.size();
        qint64 data_readed;
        qint64 currently_readed = 0;

        QObject::connect(this, SIGNAL(current_progress(int)), &progress, SLOT(setValue(int)));
        std::string tmp1 = (src_dir+"updates/v"+update_name).toUtf8().constData();
        std::string tmp2 = (dst_dir+"/v"+update_name).toUtf8().constData();
        std::cout << tmp1 << std::endl << tmp2 <<std::endl;

        if (src_file.open(QIODevice::ReadOnly)) {
            if (dst_file.open(QIODevice::WriteOnly)) {
                while (!src_stream.atEnd()) {
                    data_readed = src_stream.readRawData(data, 2048);
                    currently_readed += data_readed;
                    emit current_progress((100*currently_readed)/src_size);
                    dst_stream.writeRawData(data, 2048);
                    dst_file.flush();
                }

            } else {
                std::cout << "can't open destination file for write" << std::endl;
            }
        } else {
            std::cout << "can't open source file for read" << std::endl;
        }
        delete[] data;
    } else {
        std::cout << "can't mount destination" << std::endl;
    }
        sshfs->terminate();
        std::cout << "flag 1" << std::endl;
        //sshfs->start("fusermount -u "+dst_dir);
        std::cout << "flag 2" << std::endl;
        sshfs->waitForFinished(-1);
        delete sshfs;
}
