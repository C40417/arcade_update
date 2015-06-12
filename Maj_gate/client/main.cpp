#include <QApplication>

#include "frontend.h"
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication update(argc, argv);

    Frontend window;

    window.show();

    return update.exec();
}
