#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QDesktopServices>
#include <QUrl>
#include <QLabel>
#include <QProcess>
#include <QProgressBar>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    QLabel labout;
    QProgressBar progress;

private:
    QString src_dir;
    QString dst_dir;
    QString device_name;
    QString update_name;
    QString device_address;
    bool update_finished;

signals:

    void current_progress(int);
    
public slots:
    
    void showabout(void);
    void up_upname(QString s);
    void up_dename(QString s);
    void set_dest(QString s);
    void set_src(QString s);
    void set_address(QString s);
    void isfinished(int exitCode, QProcess::ExitStatus exitState);
    void update (void);

};

#endif // MAINWINDOW_H
