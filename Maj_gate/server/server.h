#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>
#include <QLabel>
#include <QFile>

#include <iostream>

class Server : public QWidget
{
    Q_OBJECT

public:
    Server();

private slots:
    void sendreadyread();
    void sendreadywrite();
    void waitfordemands();
    void sendreply(quint8 code);
    void sendfile(QFile *file);

private:
    QTcpServer *readserver;
    QTcpServer *writeserver;
    QLabel *address;
    QTcpSocket *readsocket;
    QTcpSocket *writesocket;
    quint16 blocksize;
};

#endif // SERVER_H
