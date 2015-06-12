#include "frontend.h"
#include "client.h"
#include <iostream>
#include <QFileInfo>
#include <QFile>

Frontend::Frontend() {
    this->setMinimumSize(360,320);

    //Mem alloc

    client = new Client;

    //The Tab Widget
    tab = new QTabWidget(this);
    //Tab 1 : update choice (list of updates, decription and button to go on a web site or on a documentation)
    groupvbox = new QGroupBox("Choose the update to apply :");
    grouphbox = new QGroupBox("Short description :");

    list_upd = new QComboBox(this);

    //Separator
    separatorv = new QFrame();
    description = new QLabel();

    //"More" Button
    more_desc = new QPushButton();

    //Boxes
    hbox = new QBoxLayout(QBoxLayout::LeftToRight);
    vbox = new QBoxLayout(QBoxLayout::TopToBottom);


    //Tab2 : device choice (list of device, decripition of the current update)
    boxtab2 = new QGroupBox("Choose the device :");

    //labels, device list, and box to store
    lab_current = new QLabel;
    current = new QLabel;

    list_dev = new QComboBox;


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
    updatebutton = new QPushButton;

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

    //Choice liste
    {
        int i = 0;
        while (client->devname[i].compare("none") == 0 ) {
                list_dev->addItem(client->devname[i]);
        }
        list_dev->addItem(client->devname[i]);
    }
    //Separator
    separatorv->setFrameShape(QFrame::VLine);
    separatorv->setFrameShadow(QFrame::Sunken);

    //Description
    description->setText("choose an update please");

    //"More" Button
    more_desc->setText("More about this update here");

    //Boxes
    hbox->addWidget(description);
    hbox->addWidget(separatorv);
    hbox->addWidget(list_upd);
    grouphbox->setLayout(hbox);

    vbox->addWidget(grouphbox);
    vbox->addWidget(more_desc);
    groupvbox->setLayout(vbox);

    //Tab2 : device choice (list of device, decripition of the current update)

    //labels, device list, and box to store
    lab_current->setText("Current version :");
    current->setText("unknown");

    list_dev->addItem("none");

    current_layout->addWidget(list_dev);
    current_layout->addWidget(lab_current);
    current_layout->addWidget(current);
    current_box->setLayout(current_layout);

    //Separator
    separatorh->setFrameShape(QFrame::HLine);
    separatorh->setFrameShadow(QFrame::Sunken);

    //update info button
    infobutton->setText("Update device informations");

    //Description
    current_descr->setText("No current information, please update");

    boxtab2_layout->addWidget(current_box);
    boxtab2_layout->addWidget(separatorh);
    boxtab2_layout->addWidget(infobutton);
    boxtab2_layout->addWidget(current_descr);
    boxtab2->setLayout(boxtab2_layout);

    //Tab3 : Progress of the update (download and install label, progress bar, cancel and update button)

    //label
    action->setText("Choose an update and a device");

    //Progress bar
    progress->setValue(0);

    //update/cancel button
    updatebutton->setText("Update");

    //Box
    tab3layout->addWidget(action);
    tab3layout->addWidget(this->progress);
    tab3layout->addWidget(updatebutton);
    boxtab3->setLayout(tab3layout);

    //Adding the pages to the widget
    tab->addTab(groupvbox, "Update");
    tab->addTab(boxtab2, "Device");
    tab->addTab(boxtab3, "Progress");

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


    //Signals

    //Close
    QObject::connect(close, SIGNAL(clicked()), this, SLOT(close()));

    //Contact us
    QObject::connect(contact, SIGNAL(clicked()), this, SLOT(contactus()));

    //Connect
    QObject::connect(list_dev, SIGNAL(currentIndexChanged(int)), client, SLOT(connect(int)));

    //Update device info
    QObject::connect(infobutton, SIGNAL(clicked()), this, SLOT(updevinfo()));
    QObject::connect(client, SIGNAL(connection(int)), this, SLOT(displaydevinfo(int)));
    //Update
    QObject::connect(updatebutton, SIGNAL(clicked()), this, SLOT(update()));

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
    QString statestr;
    if (state%2 == 1)
        statestr = QString("server read ok");
    else
        statestr = QString("server read not ok");
    if (state > 1)
        statestr += QString("server write ok");
    else
        statestr += QString("server write not ok");
    current_descr->setText(statestr);
}
