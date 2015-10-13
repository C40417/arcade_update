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
#include <QLineEdit>

#include "client.h"
#include "textviewer.h"

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
    void loaddevlist();
    void loadromlist();
    void connectall();

    void confirmadd();
    void confirmsuppress();
    void adddevice();
    void suppressdevice();
    void addtimeout();
    void supprtimeout();

private:
    Client *client;

    //The Tab Widget
    QTabWidget *tab;
    //Tab 1 : update choice (list of updates, decription and button to go on a web site or on a documentation)
    QGroupBox *groupvbox;
    QGroupBox *grouphbox;

    QComboBox *list_upd;

    //"More" Button
    QPushButton *more_desc;

    //Boxes
    QBoxLayout *hbox;
    QBoxLayout *vbox;


    //Tab2 : device choice (list of device, decripition of the current update)
    QGroupBox *boxtab2;

    //labels, device list, and box to store
    TextViewer *current_text;
    QPushButton *print_current;


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
    QPushButton *addrombutton;
    QPushButton *updatebutton;

    //Box
    QBoxLayout *tab3layout;

    //Tab4 : Manage device list

    QGroupBox *boxtab4;
    QGroupBox *hbox42;
    QGroupBox *hbox41;

    QBoxLayout *boxtab4_layout;
    QBoxLayout *hbox41_layout;
    QBoxLayout *hbox42_layout;

    QLineEdit *hbox41_name;
    QLineEdit *hbox41_addr;
    QPushButton *hbox41_button;

    QComboBox *hbox42_combo;
    QPushButton *hbox42_button;

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
