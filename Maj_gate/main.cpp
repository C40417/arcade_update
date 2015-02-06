#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QBoxLayout>
#include <QComboBox>
#include <QTabWidget>
#include <QLabel>
#include <QProgressBar>

int main(int argc, char *argv[])
{
    QApplication update(argc, argv);

    //The main window
    QWidget window;
    window.setMinimumSize(320,280);

    //The Tab Widget
    QTabWidget *tab = new QTabWidget(&window);
        tab->setGeometry(40,40,400,200);

    //Tab 1 : update choice (list of updates, decription and button to go on a web site or on a documentation)
    QGroupBox *groupvbox = new QGroupBox("Choose the update to apply :");
    QGroupBox *grouphbox = new QGroupBox("Short description :");

        //Choice liste
        QComboBox *list_upd = new QComboBox(&window);
            list_upd->addItem("1.0");
            list_upd->addItem("1.1");

        //Separator
        QFrame* separatorv = new QFrame();
            separatorv->setFrameShape(QFrame::VLine);
            separatorv->setFrameShadow(QFrame::Sunken);

        //Description
        //QLabel *label = new QLabel;
        //    label->setText("Short description :");
        QLabel *description = new QLabel;
            description->setText("choose an update please");

        //"More" Button
        QPushButton *more_desc = new QPushButton();
            more_desc->setText("More about this update here");

        //Boxes
        //QBoxLayout *vbox2 = new QBoxLayout;
            //vbox2->addWidget(label);
            //vbox2->addWidget(description);

        QBoxLayout *hbox = new QBoxLayout(QBoxLayout::LeftToRight);
            hbox->addWidget(description);
            hbox->addWidget(separatorv);
            hbox->addWidget(list_upd);
            grouphbox->setLayout(hbox);

        QBoxLayout *vbox = new QBoxLayout(QBoxLayout::TopToBottom);
            vbox->addWidget(grouphbox);
            vbox->addWidget(more_desc);
            groupvbox->setLayout(vbox);

    //Tab2 : device choice (list of device, decripition of the current update)
    QGroupBox *boxtab2 = new QGroupBox("Choose the device :");

        //labels, device list, and box to store
        QLabel *lab_current = new QLabel;
            lab_current->setText("Current version :");
        QLabel *current = new QLabel;
            current->setText("1.0");

        QComboBox *list_dev = new QComboBox;
            list_dev->addItem("dev 1");
            list_dev->addItem("dev 2");

        QGroupBox *current_box = new QGroupBox;
        QBoxLayout *current_layout = new QBoxLayout(QBoxLayout::LeftToRight);
            current_layout->addWidget(list_dev);
            current_layout->addWidget(lab_current);
            current_layout->addWidget(current);
            current_box->setLayout(current_layout);

        //Separator
        QFrame* separatorh = new QFrame();
            separatorh->setFrameShape(QFrame::HLine);
            separatorh->setFrameShadow(QFrame::Sunken);

        //Description
        QLabel *current_descr = new QLabel;
        current_descr->setText("first one");

        QBoxLayout *boxtab2_layout = new QBoxLayout(QBoxLayout::TopToBottom);
            boxtab2_layout->addWidget(current_box);
            boxtab2_layout->addWidget(separatorh);
            boxtab2_layout->addWidget(current_descr);
            boxtab2->setLayout(boxtab2_layout);

    //Tab3 : Progress of the update (download and install label, progress bar, cancel and update button)
    QGroupBox *boxtab3 = new QGroupBox("Progress of the update :");

        //label
        QLabel *action = new QLabel;
            action->setText("Waiting");

        //Progress bar
        QProgressBar *progress = new QProgressBar;
            progress->setValue(0);

        //update/cancel button
        QPushButton *updatebutton = new QPushButton;
            updatebutton->setText("Update");

        //Box
        QBoxLayout *tab3layout = new QBoxLayout(QBoxLayout::TopToBottom);
            tab3layout->addWidget(action);
            tab3layout->addWidget(progress);
            tab3layout->addWidget(updatebutton);
            boxtab3->setLayout(tab3layout);

    //Adding the pages to the widget
        tab->addTab(groupvbox, "Update");
        tab->addTab(boxtab2, "Device");
        tab->addTab(boxtab3, "Progress");

    //Contat us button and quit button (not in tabs)
    QPushButton *contact = new QPushButton;
        contact->setText("Contact us");
    QPushButton *close = new QPushButton;
        close->setText("Close");

    //Boxes to store tab and close, contact buttons
        QGroupBox *contactbox = new QGroupBox;
        QBoxLayout *contactbox_layout = new QBoxLayout(QBoxLayout::LeftToRight);
            contactbox_layout->addWidget(contact);
            contactbox_layout->addWidget(close);
            contactbox->setLayout(contactbox_layout);
            QGroupBox *globalbox = new QGroupBox(&window);
        QBoxLayout *globalbox_layout = new QBoxLayout(QBoxLayout::TopToBottom);
            globalbox_layout->addWidget(tab);
            globalbox_layout->addWidget(contactbox);
            globalbox->setLayout(globalbox_layout);


    window.show();

    return update.exec();
}
