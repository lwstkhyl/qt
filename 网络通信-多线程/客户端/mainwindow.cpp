#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "send_file.h"
#include <QThread>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ip->setText("127.0.0.1");
    ui->port->setText("8989");
    ui->progressBar->setRange(0,100);//设置进度条的显示值范围
    ui->progressBar->setValue(0);//设置进度条的当前值

    QThread* t=new QThread;//创建线程对象
    send_file* worker=new send_file;//创建任务类对象
    worker->moveToThread(t);//将任务类移动到线程对象中

    connect(ui->connect_server,&QPushButton::clicked,[=](){//点击连接服务器按钮
        QString ip=ui->ip->text();
        unsigned short port=ui->port->text().toShort();
        emit start_connect(port,ip);//发送开始连接的信号
    });
    connect(this,&MainWindow::start_connect,worker,&send_file::connect_server);//连接开始连接信号和任务类

    connect(ui->sel_file,&QPushButton::clicked,[=](){//点击选择文件按钮
        QString path=QFileDialog::getOpenFileName();//弹出选择文件窗口并保存路径
        if(path.isEmpty()==true)
        {
            QMessageBox::warning(this,"打开文件","选择的文件路径不能为空");
            return;//如果选择路径为空就不往下执行
        }
        ui->file_path->setText(path);
    });

    connect(ui->send_file,&QPushButton::clicked,[=](){//点击发送文件按钮
        emit send_file_signal(ui->file_path->text());
    });
    connect(this,&MainWindow::send_file_signal,worker,&send_file::send_file_fun);//连接发送文件信号和任务类

    //处理任务类给主线程发送的信号↓
    connect(worker,&send_file::connect_win,this,[=](){
        QMessageBox::information(this,"连接服务器","已经成功连接到了服务器");//弹出提示框
    });
    connect(worker,&send_file::connect_fail,[=](){
        //进行资源释放↓
        t->quit();
        t->wait();
        worker->deleteLater();
        t->deleteLater();
    });
    connect(worker,&send_file::current_percent,ui->progressBar,&QProgressBar::setValue);//设置进度条值

    t->start();//启动子线程
}
MainWindow::~MainWindow()
{
    delete ui;
}

