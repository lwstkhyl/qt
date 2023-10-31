#include "my_work.h"
#include <QElapsedTimer>
#include <QDebug>
#include <QThread>
generate_new::generate_new(QObject *parent):QObject(parent)
{

}
void generate_new::working(int num)
{
    qDebug()<<"生成随机数线程的线程地址："<<QThread::currentThread();
    QVector<int> list;
    QElapsedTimer time;
    time.start();
    for(int i=0;i<num;i++)
    {
        list.push_back(qrand()%100000);
    }
    int milsec=time.elapsed();
    qDebug()<<"生成"<<num<<"个随机数所需时间："<<milsec<<"ms";
    emit send_array(list);
}

bubble_sort_new::bubble_sort_new(QObject *parent):QObject(parent)
{

}
void bubble_sort_new::working(QVector<int> list)
{
    qDebug()<<"冒泡排序线程的线程地址："<<QThread::currentThread();
    QElapsedTimer time;
    time.start();
    for(int i=0;i<list.size();i++)
        for(int j=0;j<list.size()-i-1;j++)
            if(list[j]>list[j+1])
            {
                int temp=list[j];
                list[j]=list[j+1];
                list[j+1]=temp;
            }
    int milsec=time.elapsed();
    qDebug()<<"冒泡排序用时"<<milsec<<"ms";
    emit finish(list);
}

quick_sort_new::quick_sort_new(QObject *parent):QObject(parent)
{

}
void quick_sort_new::quick_sort_func(QVector<int> &s, int l, int r)
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
void quick_sort_new::working(QVector<int> list)
{
    qDebug()<<"快速排序线程的线程地址："<<QThread::currentThread();
    QElapsedTimer time;
    time.start();
    quick_sort_func(list,0,list.size()-1);
    int milsec=time.elapsed();
    qDebug()<<"快速排序用时"<<milsec<<"ms";
    emit finish(list);
}
