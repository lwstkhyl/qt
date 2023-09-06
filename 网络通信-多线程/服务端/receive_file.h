#ifndef RECEIVE_FILE_H
#define RECEIVE_FILE_H

#include <QThread>
#include <QTcpSocket>

class receive_file : public QThread
{
    Q_OBJECT
public:
    explicit receive_file(QTcpSocket* tcp,QObject *parent = nullptr);//直接用构造函数进行传参，这样就不用再单独写一个函数了
    QTcpSocket* m_tcp;//套接字对象
protected:
    void run() override;
signals:
    void over();//文件读取完全
};

#endif // RECEIVE_FILE_H
