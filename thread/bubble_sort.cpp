#include "bubble_sort.h"
#include <QElapsedTimer>
#include <QDebug>
bubble_sort::bubble_sort(QObject *parent) : QThread(parent)
{

}
void bubble_sort::recv_array(QVector<int> list)
{
    m_list=list;
}
void bubble_sort::run()
{
    qDebug()<<"冒泡排序线程的线程地址："<<QThread::currentThread();
    QElapsedTimer time;
    time.start();
    for(int i=0;i<m_list.size();i++)
        for(int j=0;j<m_list.size()-i-1;j++)
            if(m_list[j]>m_list[j+1])
            {
                int temp=m_list[j];
                m_list[j]=m_list[j+1];
                m_list[j+1]=temp;
            }
    int milsec=time.elapsed();
    qDebug()<<"冒泡排序用时"<<milsec<<"ms";
    emit finish(m_list);
}
