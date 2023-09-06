#ifndef SEND_FILE_H
#define SEND_FILE_H

#include <QObject>
#include <QTcpSocket>

class send_file : public QObject
{
    Q_OBJECT
public:
    explicit send_file(QObject *parent = nullptr);
    void connect_server(unsigned short port,QString ip);//连接服务器，参数为端口和IP
    void send_file_fun(QString path);//发送文件，参数为路径
    QTcpSocket* m_tcp;//套接字对象
signals:
    void connect_win();//连接成功的信号
    void connect_fail();//连接失败的信号
    void current_percent(int num);//进度条显示数值
};

#endif // SEND_FILE_H
