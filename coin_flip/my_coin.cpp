#include "my_coin.h"
#include <QString>
#include <QDebug>
//my_coin::my_coin(QWidget *parent) : QWidget(parent)
//{

//}
my_coin::my_coin(QString btn_img)
{
    this->setFocusPolicy(Qt::NoFocus);
    QPixmap pix;
    bool ret=pix.load(btn_img);
    if(!ret)
    {
        QString str= QString("图片%1加载失败").arg(btn_img);
        qDebug()<<str;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    //监听正面翻反面的信号，并且翻转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/Coin000%1.png").arg(this->min++);//从min=1开始，每次都+1
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断是否翻完了，若翻完，把min重置
        if(this->min>this->max)
        {
            this->min=1;
            is_animation=false;
            timer1->stop();
        }
    });
    //监听反面翻正面的信号，并且翻转金币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/Coin000%1.png").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->max<this->min)
        {
            this->max=8;
            is_animation=false;
            timer2->stop();
        }
    });

}
void my_coin::mousePressEvent(QMouseEvent *e)
{
    if(this->is_animation || this->is_win)//如果在做动画或者按钮的iswin值为true，就想拦截点击的信号
    {
        return;
    }
    else //如果没在做动画，就不拦截
    {
        QPushButton::mousePressEvent(e);
    }
}
void my_coin::change_flag()
{
    //如果是正面 翻成反面
    if(this->flag)
    {
        //开始正面翻反面的定时器
        timer1->start(30);//此步相当于发送了定时器开始的信号，被上面&QTimer::timeout接收
        this->flag=false;//开始做动画
        is_animation=true;

    }
    else//反面翻正面
    {
        timer2->start(30);
        this->flag=true;
        is_animation=true;
    }
}
