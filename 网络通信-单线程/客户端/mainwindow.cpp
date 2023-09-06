#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QHostAddress>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_tcp=new QTcpSocket(this);//创建套接字对象
    ui->port->setText("8899");//显示端口号
    ui->ip->setText("127.0.0.1");//显示ip地址
    setWindowTitle("客户端");//设置窗口栏名称
    ui->disconnect->setDisabled(true);//开始未连接至服务器是不能点击“断开连接”按钮
    connect(ui->connect,&QPushButton::clicked,[=](){//点击连接服务器按钮
        QString ip=ui->ip->text();//得到IP输入框中的输入信息
        unsigned short port=ui->port->text().toShort();//得到端口输入框中的输入信息
        m_tcp->connectToHost(QHostAddress(ip),port);//连接服务器
    });
    connect(ui->send_msg,&QPushButton::clicked,[=](){//点击发送消息按钮
        QString msg=ui->msg->toPlainText();
        m_tcp->write(msg.toUtf8());//将信息发送给服务端
        ui->record->append("客户端发送消息为："+msg);
    });
    connect(ui->disconnect,&QPushButton::clicked,[=](){//点击断开连接按钮
       m_tcp->close();//断开连接
       ui->connect->setDisabled(false);//断开连接后可以点击“连接服务器”按钮
       ui->disconnect->setEnabled(false);//断开连接后不可点击“断开连接”按钮
    });
    connect(m_tcp,&QTcpSocket::readyRead,[=](){//检测是否接收到了数据
        QByteArray data=m_tcp->readAll();//存储接收到的数据（服务器端发来的）
        ui->record->append("服务器端发送消息为："+data);//把接收到的数据显示到文本框中
    });
    connect(m_tcp,&QTcpSocket::disconnected,[=](){//服务器端断开连接
        m_tcp->close();//当套接字对象断开时tcp客户端也断开
        m_tcp->deleteLater();
        m_status->setPixmap(QPixmap(":/cuo.png").scaled(20,20));
        ui->record->append("连接已断开");
        ui->connect->setDisabled(false);//断开连接后可以点击“连接服务器”按钮
        ui->disconnect->setEnabled(false);//断开连接后不可点击“断开连接”按钮
    });
    connect(m_tcp,&QTcpSocket::connected,[=](){//当成功连接到服务器时
        m_status->setPixmap(QPixmap(":/dui.png").scaled(20,20));
        ui->record->append("成功连接到服务器");//显示成功连接
        ui->connect->setDisabled(true);//连接成功后不能点击“连接服务器”按钮
        ui->disconnect->setEnabled(true);//连接成功后可以点击“断开连接”按钮
    });
    m_status=new QLabel;
    m_status->setPixmap(QPixmap(":/cuo.png").scaled(20,20));
    ui->statusbar->addWidget(new QLabel("连接状态："));
    ui->statusbar->addWidget(m_status);
}

MainWindow::~MainWindow()
{
    delete ui;
}

