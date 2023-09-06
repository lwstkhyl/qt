#include "main_scene.h"
#include "ui_main_scene.h"
#include <QIcon>
#include <QPainter>
#include <QDesktopWidget>
main_scene::main_scene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::main_scene)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/birdIcon.ico"));
    this->m_bird=new bird;//创建鸟对象
    this->m_bird->setParent(this);//将鸟对象显示到窗口中
    this->setFixedSize(this->m_bird->width(),this->m_bird->height());//设置主窗口大小（不必要，因为后面还要进行隐藏）
    this->m_bird->running();//启动定时器
    connect(this->m_bird,&bird::change_pix,[=](){
        update();//调用画图事件来进行更新
    });
    connect(this->m_bird,&bird::moving,[=](QPoint point){
        this->move(point);
        m_auto_pos=point;//鼠标拖拽时更新当前窗口的位置
    });//(QPoint point)用于接收moving信号中的qpoint
    this->timer=new QTimer(this);//创建定时器对象
    this->timer->start(30);//启动定时器，间隔为30ms
    QDesktopWidget* desk=QApplication::desktop();//获取屏幕的相关信息
    this->m_auto_pos.setY(desk->height()/2-this->m_bird->height());//设置起始y坐标
    connect(timer,&QTimer::timeout,[=](){
        if(this->m_bird->mouse_press==false)//当鼠标没有按下时
        {
            this->m_auto_pos.setX(this->m_auto_pos.x()+5);
            if(this->m_auto_pos.x()>desk->width())//如果x坐标超出了屏幕宽度
            {
                this->m_auto_pos.setX(-this->m_bird->width());//将窗口位置设为屏幕左侧
            }//将坐标向右移动5单位
            this->move(this->m_auto_pos);//窗口也要移动
        }
    });
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setAttribute(Qt::WA_TranslucentBackground);//设置透明窗体
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint);//设置窗口顶层（不会被其它界面遮挡）
}
main_scene::~main_scene()
{
    delete ui;
}
void main_scene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->m_bird->m_bird_pix);
}

