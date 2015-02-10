#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QDesktopServices>
#include <QUrl>
#include <QLabel>
#include <QProcess>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    QLabel labout;

private:
    QString device_name;
    QString update_name;
    QProcess shell;

signals:
    
public slots:
    
    void showabout(void);
    void up_upname(QString s);
    void up_dename(QString s);
    void update (void);

};

#endif // MAINWINDOW_H
