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

#include "textviewer.h"

TextViewer::TextViewer(QWidget *parent, QString default_text, QString filename) :
    QWidget(parent)
{
    this->setMinimumSize(300,300);
    this->setWindowTitle("Informations");
    default_content = default_text;
    content.setFileName(filename);
    text = new QTextEdit;
    closebutton = new QPushButton("Close", this);
    refreshbutton = new QPushButton("Refresh", this);
    groupvbox = new QGroupBox("About device :", this);
    grouphbox = new QGroupBox;
    vbox = new QBoxLayout(QBoxLayout::TopToBottom);
    hbox = new QBoxLayout(QBoxLayout::LeftToRight);

    text->setReadOnly(true);

    refresh();

    hbox->addWidget(refreshbutton);
    hbox->addWidget(closebutton);
    grouphbox->setLayout(hbox);

    vbox->addWidget(text);
    vbox->addWidget(grouphbox);
    groupvbox->setLayout(vbox);

    QObject::connect(closebutton, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(refreshbutton, SIGNAL(clicked()), this, SLOT(refresh()));
}

void TextViewer::refresh() {
    if (content.exists()) {
        content.open(QIODevice::ReadOnly);
        QString textvalue = QString(content.readAll().constData());
        content.close();
        text->setText(textvalue);
    } else {
        text->setText(default_content);
    }
}

void TextViewer::setfile(int devnb) {
    content.setFileName(QString("/home/alexis/dev%1/info.cfg").arg(devnb));
    refresh();
}

void TextViewer::setfile(QString filename) {
    content.setFileName(filename);
    refresh();
}
