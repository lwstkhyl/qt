#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <QObject>
#include <QRunnable>
#include <QVector>
class quick_sort : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit quick_sort(QObject *parent = nullptr);
    void recv_array(QVector<int> list);
    QVector<int> m_list;
    void quick_sort_func(QVector<int> &list,int l,int r);//快速排序函数,l和r为起始和结束位置
    void run() override;
signals:
    void finish(QVector<int> num);
};

#endif // QUICK_SORT_H
