#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QBoxLayout>
#include <QComboBox>
#include <QTabWidget>
#include <QLabel>
#include <QProgressBar>
#include <QSignalMapper>
#include "frontend.h"

int main(int argc, char *argv[])
{
    QApplication update(argc, argv);

    Frontend window;

    window.show();

    return update.exec();
}
