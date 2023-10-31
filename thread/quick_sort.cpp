#include "quick_sort.h"
#include <QElapsedTimer>
#include <QDebug>
quick_sort::quick_sort(QObject *parent) : QThread(parent)
{

}
void quick_sort::recv_array(QVector<int> list)
{
    m_list=list;
}
void quick_sort::quick_sort_func(QVector<int> &s, int l, int r)
{
    if(l<r)
    {
        int i=l,j=r;
        int x=s[l];
        while (i<j)
        {
            while (i<j&&s[j]>=x)
            {
                j--;
            }
            if(i<j)
            {
                s[i]=s[j];
                i++;
            }
            while (i<j&&s[i]<x)
            {
                i++;
            }
            if(i<j)
            {
                s[j]=s[i];
                j--;
            }
        }
        s[i]=x;
        quick_sort_func(s,l,i-1);
        quick_sort_func(s,i+1,r);
    }
}
void quick_sort::run()
{
    qDebug()<<"快速排序线程的线程地址："<<QThread::currentThread();
    QElapsedTimer time;
    time.start();
    quick_sort_func(m_list,0,m_list.size()-1);
    int milsec=time.elapsed();
    qDebug()<<"快速排序用时"<<milsec<<"ms";
    emit finish(m_list);
}
