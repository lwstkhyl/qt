#ifndef MY_THREAD_H
#define MY_THREAD_H

#include <QObject>
#include <QThread>
#include <QVector>
class my_thread : public QThread
{
    Q_OBJECT
public:
    explicit my_thread(QObject *parent = nullptr);
    int m_num;//主线程发送过来的随机数生成个数
    void recv_num(int num);//槽函数，接收主线程发送过来的num
protected:
    void run() override;//重写run方法，注意其中不能传入参数
signals:
    void send_array(QVector<int> num);//把生成的随机数发送给主线程
};

#endif // MY_THREAD_H
