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
    QString device_name;
    QString update_name;
    QString stdout;
    int current_taille;
    QProcess shell;
    QProcess monitor;
    bool update_finished;

signals:

    void current_progress(int);
    
public slots:
    
    void showabout(void);
    void up_upname(QString s);
    void up_dename(QString s);
    void isfinished(int exitCode, QProcess::ExitStatus exitState);
    void read_output();
    void update (void);

};

#endif // MAINWINDOW_H
