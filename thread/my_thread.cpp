#include "my_thread.h"
#include <QElapsedTimer>
#include <QDebug>
my_thread::my_thread(QObject *parent) : QThread(parent)
{

}

void my_thread::recv_num(int num)
{
    m_num=num;
}
void my_thread::run()
{
    qDebug()<<"生成随机数线程的线程地址："<<QThread::currentThread();
    QVector<int> list;//将生成的随机数存入该vector中
    QElapsedTimer time;//计算该流程使用的时间
    time.start();
    for(int i=0;i<m_num;i++)
    {
        list.push_back(qrand()%100000);
    }
    int milsec=time.elapsed();//返回执行该流程返回的时间，单位为ms
    qDebug()<<"生成"<<m_num<<"个随机数所需时间："<<milsec<<"ms";
    emit send_array(list);
}
