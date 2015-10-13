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
#include <QTimer>
#include <QDir>

#define server_nb 20
#define requesttimeout 3000

class Client : public QWidget
{
    Q_OBJECT

public:
    Client();
    QString *devname;
    QString *romsname;
    void askreply(quint8 code);
    void adddevice(QString devicename, QString deviceaddr);
    void supprdevice(int index);

private slots:
    void loadaddress();
    void connect(int addrnb);
    void readconnected();
    void writeconnected();
    void receive();
    void hostsearch();
    void getromsinfo();
    void loadromsinfo();

signals:
    void connection(int state);

private:
    int costate;
    QFile *devnamefile;
    QFile *addressfile;
    QHostAddress *address;
    QTcpSocket *readsocket;
    QTcpSocket *writesocket;
    QTimer *timer;
    int current_connected;
    quint16 blocksize;
    quint8 askedcode;
    quint8 receivedcode;

    //client info
    QDir availableroms;
    QFile romsinfo;
};
#endif // CLIENT_H
