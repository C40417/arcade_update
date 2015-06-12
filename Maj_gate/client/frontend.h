#ifndef FRONTEND_H
#define FRONTEND_H

#include <QWidget>
#include <QDesktopServices>
#include <QUrl>
#include <QLabel>
#include <QProcess>
#include <QProgressBar>
#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QBoxLayout>
#include <QComboBox>
#include <QTabWidget>
#include <QSignalMapper>

#include "client.h"

class Frontend : public QWidget
{
    Q_OBJECT

public:
    Frontend();

private slots:
    void contactus();
    void updevinfo();
    void update();
    void displaydevinfo(int state);

private:
    Client *client;

    //The Tab Widget
    QTabWidget *tab;
    //Tab 1 : update choice (list of updates, decription and button to go on a web site or on a documentation)
    QGroupBox *groupvbox;
    QGroupBox *grouphbox;

    QComboBox *list_upd;

    //Separator
    QFrame* separatorv;
    QLabel *description;

    //"More" Button
    QPushButton *more_desc;

    //Boxes
    QBoxLayout *hbox;
    QBoxLayout *vbox;


    //Tab2 : device choice (list of device, decripition of the current update)
    QGroupBox *boxtab2;

    //labels, device list, and box to store
    QLabel *lab_current;
    QLabel *current;

    QComboBox *list_dev;


    QGroupBox *current_box;
    QBoxLayout *current_layout;


    //Separator
    QFrame* separatorh;

    //update info button
    QPushButton *infobutton;

    //Description
    QLabel *current_descr;

    QBoxLayout *boxtab2_layout;

    //Tab3 : Progress of the update (download and install label, progress bar, cancel and update button)
    QGroupBox *boxtab3;

    //progressbar
    QProgressBar *progress;

    //label
    QLabel *action;


    //update/cancel button
    QPushButton *updatebutton;

    //Box
    QBoxLayout *tab3layout;

    //Contat us button and quit button (not in tabs)
    QPushButton *contact;

    QPushButton *close;

    //Boxes to store tab and close, contact buttons
    QGroupBox *contactbox;
    QBoxLayout *contactbox_layout;

    QGroupBox *globalbox;
    QBoxLayout *globalbox_layout;
};

#endif //FRONTEND_H
