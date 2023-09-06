#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "receive_file.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_s=new QTcpServer(this);//实例化服务器对象
    ui->port->setText("8989");//设置端口号
    connect(ui->set_listen,&QPushButton::clicked,[=](){//点击启动服务器按钮
        unsigned short port=ui->port->text().toUShort();
        m_s->listen(QHostAddress::Any,port);//启动监听
    });
    connect(m_s,&QTcpServer::newConnection,[=](){//有新连接时
        QTcpSocket* tcp=m_s->nextPendingConnection();//得到套接字对象
        receive_file* sub_thread=new receive_file(tcp);//创建子线程，同时把tcp传给子线程
        sub_thread->start();//启动子线程
        connect(sub_thread,&receive_file::over,[=](){//文件传输结束时
            sub_thread->exit();//释放资源↓
            sub_thread->wait();
            sub_thread->deleteLater();
            QMessageBox::information(this,"文件接收","文件接收完毕");
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

