#include "server.h"

Server::Server() {
    this->setMinimumSize(300,300);
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
    QByteArray blockfile;
    QDataStream out(&block, QIODevice::WriteOnly);
    file->open(QIODevice::ReadOnly);
    blockfile = file->readAll();
    QDataStream in(&blockfile, QIODevice::ReadOnly);
    out << (quint16)0;
    out << in;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    writesocket->write(block);
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
        QFile devinfo("/home/alexis/test.cfg");
        Server::sendfile(&devinfo);
        break;
    }
    case 1: {
        std::cout << "code = 1" << std::endl;
        break;
    }
    case 2: {
        std::cout << "code = QLSFLKQFLSK" << std::endl;
        break;
    }
    default: {
        std::cout << "nothing" << std::endl;
        break;
    }
    }
}
