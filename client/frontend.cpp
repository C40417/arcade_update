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

#include "frontend.h"
#include "client.h"
#include <iostream>
#include <QFileInfo>
#include <QFile>

Frontend::Frontend() {
    this->setMinimumSize(480,320);
    this->setWindowTitle("Arcade Updater");

    //Mem alloc

    client = new Client;

    //The Tab Widget
    tab = new QTabWidget(this);
    //Tab 1 : update choice (list of updates, decription and button to go on a web site or on a documentation)
    groupvbox = new QGroupBox("Choose the new rom to add :");
    list_upd = new QComboBox(this);

    //"More" Button
    more_desc = new QPushButton();

    //Boxes
    vbox = new QBoxLayout(QBoxLayout::TopToBottom);

    //Tab2 : device choice (list of device, decripition of the current update)
    boxtab2 = new QGroupBox("Choose the device :");

    //labels, device list, and box to store
    current_text = new TextViewer;
    print_current = new QPushButton;

    list_dev = new QComboBox();


    current_box = new QGroupBox;
    current_layout = new QBoxLayout(QBoxLayout::LeftToRight);

    //Separator
    separatorh = new QFrame();

    //update info button
    infobutton = new QPushButton();

    //Description
    current_descr = new QLabel;

    boxtab2_layout = new QBoxLayout(QBoxLayout::TopToBottom);

    //Tab3 : Progress of the update (download and install label, progress bar, cancel and update button)
    boxtab3 = new QGroupBox("Progress of the update :");

    //progressbar
    progress = new QProgressBar();

    //label
    action = new QLabel;


    //update/cancel button
    addrombutton = new QPushButton;
    updatebutton = new QPushButton;

    //Tab4 : Manage device list

    boxtab4 = new QGroupBox("Manage devices");
    hbox42 = new QGroupBox("Suppress an existing device from the database");
    hbox41 = new QGroupBox("Add a device to the database");

    boxtab4_layout = new QBoxLayout(QBoxLayout::TopToBottom);
    hbox41_layout = new QBoxLayout(QBoxLayout::LeftToRight);
    hbox42_layout = new QBoxLayout(QBoxLayout::LeftToRight);

    hbox41_name = new QLineEdit;
    hbox41_addr = new QLineEdit;
    hbox41_button = new QPushButton;

    hbox42_combo = new QComboBox;
    hbox42_button = new QPushButton;

    //Box
    tab3layout = new QBoxLayout(QBoxLayout::TopToBottom);

    //Contat us button and quit button (not in tabs)
    contact = new QPushButton;

    close = new QPushButton;

    //Boxes to store tab and close, contact buttons
    contactbox = new QGroupBox;
    contactbox_layout = new QBoxLayout(QBoxLayout::LeftToRight);

    globalbox = new QGroupBox(this);
    globalbox_layout = new QBoxLayout(QBoxLayout::TopToBottom);

    //The Tab Widget
    tab->setGeometry(40,40,400,200);

    //Tab 1 : update choice (list of updates, decription and button to go on a web site or on a documentation)

    //Choice list
    //Loaded after
    loadromlist();

    //"More" Button
    more_desc->setText("More about this update here");

    //Boxes

    vbox->addWidget(list_upd);
    vbox->addWidget(more_desc);
    groupvbox->setLayout(vbox);

    //Tab2 : device choice (list of device, decripition of the current update)

    //labels, device list, and box to store
    //List loaded after

    print_current->setText("Informations");

    current_layout->addWidget(list_dev);
    current_layout->addWidget(print_current);
    current_box->setLayout(current_layout);

    //Separator
    separatorh->setFrameShape(QFrame::HLine);
    separatorh->setFrameShadow(QFrame::Sunken);

    //update info button
    infobutton->setText("Update device informations");

    //Description
    current_descr->setText("Choose a device to connect");

    boxtab2_layout->addWidget(current_box);
    boxtab2_layout->addWidget(separatorh);
    boxtab2_layout->addWidget(infobutton);
    boxtab2_layout->addWidget(current_descr);
    boxtab2->setLayout(boxtab2_layout);

    //Tab3 : Progress of the update (download and install label, progress bar, cancel and update button)

    //label
    action->setText("Choose a device and a rom to add or update the device :");

    //Progress bar
    progress->setValue(0);

    //update/cancel button
    addrombutton->setText("Add selected rom");
    updatebutton->setText("Update system");

    //Box
    tab3layout->addWidget(action);
    tab3layout->addWidget(progress);
    tab3layout->addWidget(addrombutton);
    tab3layout->addWidget(updatebutton);
    boxtab3->setLayout(tab3layout);

    //Tab4 : Manage device list

    //Setting first horizontal box
    hbox41_name->setPlaceholderText("Enter a device name");
    hbox41_addr->setPlaceholderText("Enter an IP address");
    hbox41_button->setText("Add");

    hbox41_layout->addWidget(hbox41_name);
    hbox41_layout->addWidget(hbox41_addr);
    hbox41_layout->addWidget(hbox41_button);

    hbox41->setLayout(hbox41_layout);

    //Setting second horizontal box
    loaddevlist();

    hbox42_button->setText("Suppress");

    hbox42_layout->addWidget(hbox42_combo);
    hbox42_layout->addWidget(hbox42_button);

    hbox42->setLayout(hbox42_layout);

    boxtab4_layout->addWidget(hbox41);
    boxtab4_layout->addWidget(hbox42);

    boxtab4->setLayout(boxtab4_layout);

    //Adding the pages to the widget
    tab->addTab(groupvbox, "Rom");
    tab->addTab(boxtab2, "Device");
    tab->addTab(boxtab3, "Progress");
    tab->addTab(boxtab4, "Devices list");

    //Contat us button and quit button (not in tabs)
    contact->setText("Contact us");
    close->setText("Close");

    //Boxes to store tab and close, contact buttons
    contactbox_layout->addWidget(contact);
    contactbox_layout->addWidget(close);
    contactbox->setLayout(contactbox_layout);
    globalbox_layout->addWidget(tab);
    globalbox_layout->addWidget(contactbox);
    globalbox->setLayout(globalbox_layout);

    // Connect
    connectall();
}

void Frontend::connectall() {
    //Close
    QObject::connect(close, SIGNAL(clicked()), current_text, SLOT(close()));
    QObject::connect(close, SIGNAL(clicked()), this, SLOT(close()));

    //Contact us
    QObject::connect(contact, SIGNAL(clicked()), this, SLOT(contactus()));

    //Connect
    QObject::connect(list_dev, SIGNAL(currentIndexChanged(int)), client, SLOT(connect(int)));

    //Update device info
    QObject::connect(infobutton, SIGNAL(clicked()), this, SLOT(updevinfo()));
    QObject::connect(client, SIGNAL(connection(int)), this, SLOT(displaydevinfo(int)));
    QObject::connect(list_dev, SIGNAL(currentIndexChanged(int)), current_text, SLOT(setfile(int)));
    QObject::connect(print_current, SIGNAL(clicked()), current_text, SLOT(show()));
    //Update
    QObject::connect(updatebutton, SIGNAL(clicked()), this, SLOT(update()));

    //Add suppress
    QObject::connect(hbox41_button, SIGNAL(clicked()), this, SLOT(confirmadd()));
    QObject::connect(hbox42_button, SIGNAL(clicked()), this, SLOT(confirmsuppress()));
}

void Frontend::contactus() {
    QDesktopServices::openUrl(QUrl("https://www.google.fr"));
}

void Frontend::updevinfo() {
    client->askreply(0);
}

void Frontend::update() {
    client->askreply(1);
}

void Frontend::displaydevinfo(int state) {
    if (state == -1) {
        current_descr->setText("Connecting");
    } else if (state == 3) {
        current_descr->setText("Connected to "+list_dev->currentText());
    } else {
        current_descr->setText("No connection");
    }
}

void Frontend::loaddevlist() {
    list_dev->disconnect();
    hbox41_name->disconnect();

    list_dev->clear();
    hbox42_combo->clear();

    int i = 0;
    while (client->devname[i].compare("none") != 0) {
        hbox42_combo->addItem(client->devname[i]);
        list_dev->addItem(client->devname[i++]);
    }
    list_dev->addItem(client->devname[i]);
}

void Frontend::loadromlist() {
    list_upd->disconnect();
    list_upd->clear();

    int i = 0;
    while (i < client->romsname->size()) {
        list_upd->addItem(client->romsname[i++]);
    }
}

void Frontend::confirmadd() {
    hbox41_button->setText("Sure ?");
    QObject::disconnect(hbox41_button, 0, this, SLOT(confirmadd()));
    QObject::connect(hbox41_button, SIGNAL(clicked()), this, SLOT(adddevice()));
    QTimer::singleShot(5000, this, SLOT(addtimeout()));
}

void Frontend::confirmsuppress() {
    hbox42_button->setText("Sure ?");
    QObject::disconnect(hbox42_button, 0, this, SLOT(confirmsuppress()));
    QObject::connect(hbox42_button, SIGNAL(clicked()), this, SLOT(suppressdevice()));
    QTimer::singleShot(5000, this, SLOT(supprtimeout()));
}

void Frontend::addtimeout() {
        hbox41_button->setText("Add");
        QObject::disconnect(hbox41_button, 0, this, SLOT(adddevice()));
        QObject::connect(hbox41_button, SIGNAL(clicked()), this, SLOT(confirmadd()));
}

void Frontend::supprtimeout() {
    hbox42_button->setText("Suppress");
    QObject::disconnect(hbox42_button, 0, this, SLOT(suppressdevice()));
    QObject::connect(hbox42_button, SIGNAL(clicked()), this, SLOT(confirmsuppress()));
}

void Frontend::adddevice() {
    hbox41_button->setText("Add");
    QObject::disconnect(hbox41_button, 0, this, SLOT(adddevice()));
    QObject::connect(hbox41_button, SIGNAL(clicked()), this, SLOT(confirmadd()));
    client->adddevice(hbox41_name->text(), hbox41_addr->text());

    loaddevlist();
    connectall();
}

void Frontend::suppressdevice() {
    hbox42_button->setText("Suppress");
    QObject::disconnect(hbox42_button, 0, this, SLOT(suppressdevice()));
    QObject::connect(hbox42_button, SIGNAL(clicked()), this, SLOT(confirmsuppress()));
    client->supprdevice(hbox42_combo->currentIndex());

    loaddevlist();
    connectall();
}
