#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_s=new QTcpServer(this);//创建监听的服务器对象
    m_tcp=new QTcpSocket(this);//创建套接字对象
    ui->port->setText("8899");//显示端口号
    setWindowTitle("服务器");//设置窗口栏名称
    connect(ui->set_listen,&QPushButton::clicked,[=](){//点击启动按钮启动监听
        unsigned short port=ui->port->text().toUShort();//port是端口号
        m_s->listen(QHostAddress::Any,port);//设置监听
        ui->set_listen->setDisabled(true);//将按钮设为不可用
    });//对于按钮的connect操作，也可以在ui中右键按钮点击“转到槽”，直接在新建的函数中写上面lambda中的内容
    connect(m_s,&QTcpServer::newConnection,[=](){//检测有无新连接
        m_tcp=m_s->nextPendingConnection();//当有新连接时将套接字对象实例化
        connect(m_tcp,&QTcpSocket::readyRead,[=](){//检测是否接收到了数据，必须写在QTcpSocket* m_tcp=m_s->nextPendingConnection()下，因为此时m_tcp才被实例化
            QByteArray data=m_tcp->readAll();//存储接收到的数据（客户端发来的）
            ui->record->append("客户端发送消息为："+data);//把接收到的数据显示到文本框中
        });
        m_status->setPixmap(QPixmap(":/dui.png").scaled(20,20));//有新连接时就换成连接状态的图片
        connect(m_tcp,&QTcpSocket::disconnected,[=](){
            m_tcp->close();//当套接字对象断开时tcp服务端也断开
            m_tcp->deleteLater();//释放内存，也可以不写这行
            m_status->setPixmap(QPixmap(":/cuo.png").scaled(20,20));//设为未连接状态
        });
    });
    connect(ui->send_msg,&QPushButton::clicked,[=](){//点击发送消息的按钮就发送消息
        QString msg=ui->msg->toPlainText();//将输入框中的内容以纯文本的方式取出来存入msg中
        m_tcp->write(msg.toUtf8());//将msg转为utf-8(qbytearray)类型进行发送
        ui->record->append("服务器端发送消息为："+msg);//将服务器端发送的消息显示到文本框中
    });
    m_status=new QLabel;//因为还要把它设置到状态栏内，所以指不指定父对象无所谓
    m_status->setPixmap(QPixmap(":/cuo.png").scaled(20,20));//默认为未连接状态，并把图片尺寸设为20*20
    //直接在左侧右键图片文件，点击copy path就可以快速复制路径
    ui->statusbar->addWidget(new QLabel("连接状态："));//添加一个显示文字的qlabel
    ui->statusbar->addWidget(m_status);
}

MainWindow::~MainWindow()
{
    delete ui;
}

