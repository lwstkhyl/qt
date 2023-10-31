#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <QObject>
#include <QThread>
#include <QVector>
class bubble_sort : public QThread
{
    Q_OBJECT
public:
    explicit bubble_sort(QObject *parent = nullptr);
    void recv_array(QVector<int> list);//接收生成的随机数列表
    QVector<int> m_list;//要进行排序的随机数
protected:
    void run() override;//重写run方法
signals:
    void finish(QVector<int> num);//排序结束的信号，传给主线程排序后结果列表
};

#endif // BUBBLE_SORT_H
