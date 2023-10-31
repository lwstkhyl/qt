#ifndef MY_WORK_H
#define MY_WORK_H

#include <QObject>
#include <QVector>
class generate_new : public QObject //生成随机数类
{
    Q_OBJECT
public:
    explicit generate_new(QObject *parent = nullptr);
    void working(int num);//相当于run()方法中传入参数，因此就不需要recv_num函数以及类中的变量m_num进行接收，下面两个类同理
signals:
    void send_array(QVector<int> num);
};

class bubble_sort_new : public QObject//冒泡排序类
{
    Q_OBJECT
public:
    explicit bubble_sort_new(QObject *parent = nullptr);
    void working(QVector<int> list);
signals:
    void finish(QVector<int> num);
};

class quick_sort_new : public QObject//快速排序类
{
    Q_OBJECT
public:
    explicit quick_sort_new(QObject *parent = nullptr);
    void quick_sort_func(QVector<int> &list,int l,int r);
    void working(QVector<int> list);
signals:
    void finish(QVector<int> num);
};
#endif // MY_WORK_H
