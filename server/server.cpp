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

#include "server.h"

Server::Server() {
    this->setMinimumSize(300,300);
    roms = QDir("/home/alexis/dev0/roms/"); // /home/pi/mame4all-pi/roms (raspicade documentation p17)
    devinfo.setFileName("/home/alexis/test.cfg"); // /home/pi/mame4all-pi/serverinfo.cfg (or another)

    readserver = new QTcpServer(this);
    writeserver = new QTcpServer(this);
    readserver->listen(QHostAddress::LocalHost, 4348);
    writeserver->listen(QHostAddress::LocalHost, 4349);

    address = new QLabel(this);
    address->setText("read = "+readserver->serverAddress().toString()+" port = 4348\n"+"write = port 4349");
    address->show();
    QObject::connect(readserver, SIGNAL(newConnection()), this, SLOT(sendreadyread()));
    QObject::connect(writeserver, SIGNAL(newConnection()), this, SLOT(sendreadywrite()));
}

void Server::sendreadyread() {
    readsocket = readserver->nextPendingConnection();
    QObject::connect(readsocket, SIGNAL(readyRead()), this, SLOT(waitfordemands()));
}

void Server::sendreadywrite() {
    writesocket = writeserver->nextPendingConnection();
    blocksize = 0;
}

void Server::sendfile(QFile *file) {
    QByteArray block;
    char *data = new char[file->size()];
    QDataStream in(file);
    QDataStream out(&block, QIODevice::WriteOnly);
    file->open(QIODevice::ReadOnly);
    in.readRawData(data, file->size());
    out << (quint16)0;
    out.writeRawData(data, file->size());
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    writesocket->write(block);
    file->close();
}

void Server::waitfordemands() {
    QDataStream in(readsocket);
    if (blocksize == 0) {
        if (readsocket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> blocksize;
    }
    if (readsocket->bytesAvailable() < blocksize)
        return;
    quint8 code;
    in >> code;
    blocksize = 0;
    sendreply(code);
}

void Server::sendreply(quint8 code) {
    switch (code) {
    case 0: {
        //Send data about device (version number)
        std::cout << "code = 0" << std::endl;
        makedevinfo();
        Server::sendfile(&devinfo);
        break;
    }
    case 1: {
        std::cout << "code = 1" << std::endl;
        break;
    }
    case 2: {
        std::cout << "code = 2" << std::endl;
        break;
    }
    default: {
        std::cout << "nothing" << std::endl;
        break;
    }
    }
}

void Server::makedevinfo() {
    QStringList ls = roms.entryList();
    QString info = ls.filter(".zip").join("\n");
    if (devinfo.exists())
        devinfo.copy(devinfo.fileName()+"~");
    devinfo.open(QIODevice::WriteOnly);
    devinfo.write((info+"\n").toUtf8().constData());
    devinfo.close();
}
