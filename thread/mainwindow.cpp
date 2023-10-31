#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "my_thread.h"
#include "bubble_sort.h"
#include "quick_sort.h"
#include "my_work.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QThread *t1=new QThread(this);
    QThread *t2=new QThread;
    QThread *t3=new QThread;//创建子线程对象
    generate_new *gen=new generate_new;
    bubble_sort_new *bubble=new bubble_sort_new;
    quick_sort_new *quick=new quick_sort_new;//创建任务类对象
    gen->moveToThread(t1);
    bubble->moveToThread(t2);
    quick->moveToThread(t3);//将任务对象移动到某个子线程中
    connect(this,&MainWindow::starting,gen,&generate_new::working);//starting和working接收相同参数，进行传参
    connect(ui->start,&QPushButton::clicked,this,[=](){
        emit starting(10000);
        t1->start();//t1是随机数线程，用t1代替generate进行启动
    });//以下都与前面方法相同，只需把recv_num改成working，bubble和quick的start用t1t2代替
    connect(gen,&generate_new::send_array,bubble,&bubble_sort_new::working);
    connect(gen,&generate_new::send_array,quick,&quick_sort_new::working);
    connect(gen,&generate_new::send_array,this,[=](QVector<int> list){
        t2->start();
        t3->start();
        for(int i=0;i<list.size();i++)
        {
            ui->rand_list->addItem(QString::number(list[i]));
        }
    });
    connect(bubble,&bubble_sort_new::finish,this,[=](QVector<int> list){
        for(int i=0;i<list.size();i++)
        {
            ui->bubble_list->addItem(QString::number(list[i]));
        }
    });
    connect(quick,&quick_sort_new::finish,this,[=](QVector<int> list){
        for(int i=0;i<list.size();i++)
        {
            ui->quick_list->addItem(QString::number(list[i]));
        }
    });
//    my_thread * generate=new my_thread;//创建子线程对象
//    bubble_sort * bubble=new bubble_sort;//创建冒泡排序进程对象
//    quick_sort * quick=new quick_sort;//创建快速排序进程对象
//    connect(this,&MainWindow::starting,generate,&my_thread::recv_num);
//    //starting信号和recv_num信号槽接收同类型的参数，将staring信号的参数直接传给信号槽
//    connect(ui->start,&QPushButton::clicked,this,[=](){
//        emit starting(10000);//主线程传给子线程m_num参数
//        generate->start();//按钮被按下时启动子线程
//    });
//    connect(generate,&my_thread::send_array,bubble,&bubble_sort::recv_array);
//    connect(generate,&my_thread::send_array,quick,&quick_sort::recv_array);//接收随机数列表
//    connect(generate,&my_thread::send_array,this,[=](QVector<int> list){
//        bubble->start();
//        quick->start();//当随机数生成完后启动两个排序线程
//        for(int i=0;i<list.size();i++)
//        {
//            ui->rand_list->addItem(QString::number(list[i]));//把传过来的list中的数转成qstring类型显示到listwidget中
//        }
//    });
//    connect(bubble,&bubble_sort::finish,this,[=](QVector<int> list){
//        for(int i=0;i<list.size();i++)
//        {
//            ui->bubble_list->addItem(QString::number(list[i]));
//        }
//    });
//    connect(quick,&quick_sort::finish,this,[=](QVector<int> list){
//        for(int i=0;i<list.size();i++)
//        {
//            ui->quick_list->addItem(QString::number(list[i]));
//        }
//    });//排序结束后将两个排序结果输出到listwidget中
    connect(this,&MainWindow::destroyed,this,[=](){
        t1->quit();
        t1->wait();
        t1->deleteLater();
        gen->deleteLater();
    });
//    connect(this,&MainWindow::destroyed,this,[=](){
//        generate->quit();
//        generate->wait();
//        generate->deleteLater():
//    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

