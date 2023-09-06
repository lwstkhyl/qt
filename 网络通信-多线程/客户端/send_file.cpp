#include "send_file.h"
#include <QHostAddress>
#include <QFile>
#include <QFileInfo>

send_file::send_file(QObject *parent) : QObject(parent)
{  
}
void send_file::connect_server(unsigned short port, QString ip)
{
    m_tcp=new QTcpSocket;//实例化套接字对象
    m_tcp->connectToHost(QHostAddress(ip),port);//连接到服务器
    connect(m_tcp,&QTcpSocket::connected,this,[=](){
        emit connect_win();
    });//若套接字对象与服务器连接成功就发送成功的信号
    connect(m_tcp,&QTcpSocket::disconnected,this,[=](){
        m_tcp->close();
        m_tcp->deleteLater();
        emit connect_fail();
    });//若没连接（断开连接）就发送连接失败的信号
}
void send_file::send_file_fun(QString path)
{
    QFile file(path);//使用路径创建文件对象
    QFileInfo info(path);
    int file_size=info.size();//文件大小
    file.open(QFile::ReadOnly);//因为不需要对文件进行修改，所以用只读方式打开文件
    while(file.atEnd()==false)//当文件读完后atEnd()为true
    {
        static int num=0;//循环次数/已经发送的文件大小
        if(num==0)//如果是第一次循环，就把文件大小发送给服务器
            m_tcp->write((char*)&file_size,4);//第一个参数为发送的内容，第二个参数为内容占字节数
        QByteArray line=file.readLine();//文件一次循环读一行，line存储这行内容
        num+=line.size();//记录已经发送的文件大小，从而计算进度条
        int progress_percent=(num*100/file_size);//进度条数值
        emit current_percent(progress_percent);//将进度条数值发送给主线程
        m_tcp->write(line);//将内容传给套接字对象来进行发送
    }
}
