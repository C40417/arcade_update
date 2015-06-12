#include <QApplication>

#include "server.h"

int main(int argc, char *argv[])
{
    QApplication update(argc, argv);

    Server server;

    server.show();

    return update.exec();
}
