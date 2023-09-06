#include "receive_file.h"
#include <QFile>

receive_file::receive_file(QTcpSocket* tcp,QObject *parent) : QThread(parent)
{
    m_tcp=tcp;
}
void receive_file::run()
{
    QFile* file=new QFile("receive.txt");//这个路径是想把接收到的文件存储在哪，具体路径在build-send_file_server下
    file->open(QFile::WriteOnly);//以只写方式打开文件
    connect(m_tcp,&QTcpSocket::readyRead,[=](){
        static int count=0;//因为每接收到一次文件就会有一个readyread信号并执行一次connect，所以可以用static变量来记录是第几次接收信息/已经接收到文件的大小
        static int total=0;//存储文件总大小
        if(count==0)//如果是第一次接收到信号，那就是客户端发来的文件总大小信息
            m_tcp->read((char*)&total,4);//读取4个字节的文件总大小信息，存在total中
        QByteArray all=m_tcp->readAll();//读取剩下的数据
        file->write(all);
        count+=all.size();//递增已经接收到的大小
        if(count==total)//当数据全部读完时
        {
            m_tcp->close();//关闭套接字对象
            m_tcp->deleteLater();//释放资源↓
            file->close();
            file->deleteLater();
            emit over();
        }
    });
    //因为正常的run方法只在start时执行一次，而在这里我们不能确定什么时候会接收到数据执行connect操作，所以要让run方法在start后一直执行
    exec();//进入事件循环
}
