#include "my_pushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>
//my_pushbutton::my_pushbutton(QWidget *parent) : QWidget(parent)
//{

//}
my_pushbutton::my_pushbutton(QString normal_img,QString press_img)
{
    this->normal_img_path=normal_img;
    this->press_img_path=press_img;
    QPixmap pix;
    bool ret= pix.load(normal_img);//判断是否加载图片成功
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}
void my_pushbutton::zoom1()
{
    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //第一个参数为目标，第二个参数为特效名
    animation->setDuration(200);//时间间隔
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));//起始位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));//结束位置（往上移10）
    animation->setEasingCurve(QEasingCurve::OutBounce);//设置弹跳效果
    animation->start();//执行动画
}
void my_pushbutton::zoom2()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //注意这步中开始位置是y()+10，说明按钮的y值再执行完向上跳后未改变
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
//重现按钮的按下和释放事件
void my_pushbutton::mousePressEvent(QMouseEvent *e)
{
    if(this->press_img_path!="")//判断是否传入图片->是否切换图片
    {
        //用上面的方法加载
        QPixmap pix;
        bool ret= pix.load(this->press_img_path);
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}
void my_pushbutton::mouseReleaseEvent(QMouseEvent *e)
{
    //用上面的方法还原
    if(this->press_img_path!="")
    {
        QPixmap pix;
        bool ret= pix.load(this->normal_img_path);
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
void my_pushbutton::enterEvent(QEvent *event)
{
    emit enter_menu_btn();
}
void my_pushbutton::leaveEvent(QEvent *)
{
    emit leave_menu_btn();
}
