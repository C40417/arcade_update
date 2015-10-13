/* The MIT License (MIT)

Copyright (c) [2015] [Alexis Lescouet]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#include "client.h"

Client::Client() {
    this->setMinimumSize(300,300);
    costate=0;
    devnamefile = new QFile("/home/alexis/devlist.cfg");  // /dir/to/cfg
    addressfile = new QFile("/home/alexis/addrlist.cfg"); // /dir/to/cfg
    availableroms = QDir("/home/alexis/dev0/availableroms/"); // /dir/to/roms
    romsinfo.setFileName("/home/alexis/dev0/romsinfo.cfg"); // /dir/to/roms/../romsinfo.cfg
    devname = new QString[server_nb + 1];
    address = new QHostAddress[server_nb + 1];
    romsname = new QString[50];

    if (devnamefile->exists() && addressfile->exists()) {
        loadaddress();
    } else {
        devname[0] = QString("localloop");
        devname[1] = QString("none");
        address[0] = QHostAddress("127.0.0.1");
        address[1] = QHostAddress::Null;
    }

    loadromsinfo();

    readsocket = new QTcpSocket(this);
    writesocket = new QTcpSocket(this);
    timer= new QTimer(this);
    timer->setSingleShot(true);


    QObject::connect(readsocket, SIGNAL(connected()), this, SLOT(readconnected()));
    QObject::connect(writesocket, SIGNAL(connected()), this, SLOT(writeconnected()));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(hostsearch()));
}

void Client::connect(int addrnb) {
    readsocket->abort();
    writesocket->abort();
    if (!address[addrnb].isNull()) {
        readsocket->connectToHost(address[addrnb], 4349); //connect on writesocket server
        writesocket->connectToHost(address[addrnb], 4348); //connect on readsocket server
        emit connection(-1);
        timer->start(requesttimeout);
    } else {
        emit connection(0);
    }
}

void Client::hostsearch() {
    if (timer->isActive())
        timer->stop();
    else
        emit connection(0);
}

void Client::readconnected() {
    hostsearch();
    if (costate%2 == 0)
        costate += 1;
    QObject::connect(readsocket, SIGNAL(readyRead()), this, SLOT(receive()));
    blocksize = 0;
    emit connection(costate);
}

void Client::writeconnected() {
    if (costate < 2)
        costate += 2;
    emit connection(costate);
}

void Client::receive() {
    QDataStream in(readsocket);
    if (blocksize == 0) {
        if (readsocket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> blocksize;
    }
    if (readsocket->bytesAvailable() < blocksize)
        return;
    if (askedcode == 0) {
        QFile file(QString("/home/alexis/dev%1/info.cfg").arg(current_connected));
        if (file.exists()) {
            QString name = file.fileName();
            file.rename(name+"~");
            file.setFileName(name);
        }
        char *data = new char[blocksize];
        QDataStream out(&file);
        file.open(QIODevice::WriteOnly);
        in.readRawData(data, blocksize);
        out.writeRawData(data, blocksize);
        file.close();
    }
    blocksize = 0;
}

void Client::askreply(quint8 code) {
    askedcode = code;
    QByteArray block;
    QDataStream out(&block, QIODevice::ReadWrite);
    out << (quint16)0;
    out << (quint8)code;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    writesocket->write(block);
}

void Client::loadaddress() {
    char name[16];
    char addr[16];
    int ret = 1, i = -1;
    devnamefile->open(QIODevice::ReadOnly);
    addressfile->open(QIODevice::ReadOnly);

    while (ret != -1) {
        ret = devnamefile->readLine(name, 16);
        addressfile->readLine(addr, 16);
        for (int j = 0; j <= 16; ++j) {
            if (name[j] == '\n') {
                name[j] = '\0';
            }
            if (addr[j] == '\n') {
                addr[j] = '\0';
            }
        }
        if (i < server_nb) {
            i++;
            devname[i] = QString(name);
            address[i] = QHostAddress(QString(addr));
        }
    }
    devname[i] = QString("none");
    address[i] = QHostAddress::Null;

    devnamefile->close();
    addressfile->close();
}

void Client::adddevice(QString devicename, QString deviceaddr) {
    devnamefile->open(QIODevice::Append);
    addressfile->open(QIODevice::Append);
    devnamefile->write((devicename+"\n").toUtf8().constData());
    addressfile->write((deviceaddr+"\n").toUtf8().constData());
    devnamefile->close();
    addressfile->close();
    loadaddress();
}

void Client::supprdevice(int index) {
    QFile *tmpname;
    QFile *tmpaddr;
    tmpname = new QFile("/home/alexis/ab492d3491df4832deab9c394ca83");
    tmpaddr = new QFile("/home/alexis/45b23a4d4f53d214acd482d34a31b");
    tmpname->open(QIODevice::WriteOnly);
    tmpaddr->open(QIODevice::WriteOnly);
    devnamefile->open(QIODevice::ReadWrite);
    addressfile->open(QIODevice::ReadWrite);
    int i = 0;
    int ret = 10;
    while (i < index) {
        tmpname->write(devnamefile->readLine(16).constData());
        tmpaddr->write(addressfile->readLine(16).constData());
        i++;
    }
    i++;
    devnamefile->readLine();
    addressfile->readLine();
    char data[16];
    while (ret != -1) {
        ret = devnamefile->readLine(data, 16);
        tmpname->write(data);
        tmpaddr->write(addressfile->readLine(16).constData());
        i++;
    }
    tmpname->close();
    tmpaddr->close();
    devnamefile->close();
    addressfile->close();
    devnamefile->remove();
    addressfile->remove();
    tmpname->rename(devnamefile->fileName());
    tmpaddr->rename(addressfile->fileName());
    delete tmpname;
    delete tmpaddr;
    loadaddress();
}

void Client::getromsinfo() {
    QStringList ls = availableroms.entryList();
    QString info = ls.filter(".zip").join("\n");
    if (romsinfo.exists())
        romsinfo.copy(romsinfo.fileName()+"~");
    romsinfo.open(QIODevice::WriteOnly);
    romsinfo.write((info+"\n").toUtf8().constData());
    romsinfo.close();
}

void Client::loadromsinfo() {
    getromsinfo();
    char name[20];
    romsinfo.open(QIODevice::ReadOnly);
    int ret = 1, i = -1;

    while (ret != -1) {
        ret = romsinfo.readLine(name, 20);
        for (int j = 0; j <= 20; ++j) {
            if (name[j] == '\n') {
                name[j] = '\0';
            }
        }
        romsname[++i] = QString(name);
    }
    romsname[i] = QString("none");
    romsinfo.close();
}
