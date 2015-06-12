#include "client.h"

Client::Client() {
    this->setMinimumSize(300,300);
    devnamefile = new QFile("/home/alexis/devlist.cfg");
    addressfile = new QFile("/home/alexis/addrlist.cfg");
    devname = new QString[server_nb + 1];
    address = new QHostAddress[server_nb + 1];

    if (devnamefile->exists() && addressfile->exists()) {
        loadaddress();
    } else {
        devname[0] = QString("localloop");
        devname[1] = QString("none");
        address[0] = QHostAddress("127.0.0.1");
        address[1] = QHostAddress("0.0.0.0");
    }

    readsocket = new QTcpSocket(this);
    writesocket = new QTcpSocket(this);

    QObject::connect(readsocket, SIGNAL(connected()), this, SLOT(readconnected()));
    QObject::connect(writesocket, SIGNAL(connected()), this, SLOT(writeconnected()));
}

void Client::connect(int addrnb) {
    readsocket->abort();
    writesocket->abort();
    if (address[addrnb].toString().compare("0.0.0.0") != 0) {
        readsocket->connectToHost(address[addrnb], 4349); //connected on writesocket server
        writesocket->connectToHost(address[addrnb], 4348); //connected on readsocket server
    } else {
        emit connection(0);
    }
}

void Client::readconnected() {
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

void getconnected() {

}

/* void Client::receive(QFile file) {
    QDataStream in(readsocket);
    if (blocksize == 0) {
        if (readsocket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> blocksize;
    }
    if (readsocket->bytesAvailable() < blocksize)
        return;
    if (askedcode == 0) {
        file.open(QIODevice::WriteOnly);
        QDataStream(file);

    in >> file;
    }
    blocksize = 0;
} */

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
        file.open(QIODevice::WriteOnly);
        QByteArray block;
        QDataStream stream(&block, QIODevice::WriteOnly);
        stream << in;
        char *coucou = new char[blocksize];
        in.readRawData(coucou, blocksize);
        std::cout << coucou << std::endl;
        file.write(coucou, blocksize);
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
    int ret = 1, i = 0;
    devnamefile->open(QIODevice::ReadOnly);
    addressfile->open(QIODevice::ReadOnly);

    while (ret != -1) {
        ret = devnamefile->readLine(addr, 16);
        addressfile->readLine(name, 16);
        for (int j = 0; j < 16; ++j) {
            if (name[j] == '\n') {
                name[j] = '\0';
                continue;
            }
        }
        for (int j = 0; j < 16; ++j) {
            if (addr[j] == '\n') {
                addr[j] = '\0';
                continue;
            }
        }
        if (i < server_nb) {
        devname[i++] = QString(addr);
        address[i++] = QHostAddress(QString(addr));
        }
    }
    devname[i] = QString("none");
    address[i] = QHostAddress(QString("0.0.0.0"));
}
