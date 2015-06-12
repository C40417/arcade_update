#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QWidget>
#include <QHostAddress>
#include <QLabel>
#include <iostream>
#include <QPushButton>
#include <QDataStream>
#include <QFile>
#include <QFileInfo>
#include <string>

#define server_nb 20

class Client : public QWidget
{
    Q_OBJECT

public:
    QString *devname;
    Client();
    void askreply(quint8 code);

private slots:
    void loadaddress();
    void connect(int addrnb);
    void readconnected();
    void writeconnected();
    void receive();

signals:
    void connection(int state);

private:
    int costate;
    QFile *devnamefile;
    QFile *addressfile;
    QHostAddress *address;
    QTcpSocket *readsocket;
    QTcpSocket *writesocket;
    int current_connected;
    quint16 blocksize;
    quint8 askedcode;
    quint8 receivedcode;
};
#endif // CLIENT_H
