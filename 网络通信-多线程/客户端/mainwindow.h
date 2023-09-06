#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
signals:
    void start_connect(unsigned short port,QString ip);//开始连接的信号，负责连接按钮和任务类
    void send_file_signal(QString path);//发送文件的信号，由主线程传给任务类
};
#endif // MAINWINDOW_H
