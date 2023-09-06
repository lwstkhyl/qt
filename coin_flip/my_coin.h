#ifndef MY_COIN_H
#define MY_COIN_H

#include <QPushButton>
#include <QString>
#include <QTimer>
class my_coin : public QPushButton
{
    Q_OBJECT
public:
    //explicit my_coin(QWidget *parent = nullptr);
    my_coin(QString btn_img);//参数代表传入的是金币路径还是银币路径
    //金币属性
    int pos_x;//x坐标位置
    int pox_y;//y坐标位置
    bool flag;//正反标示
    void change_flag();//改变标志的方法
    QTimer *timer1;//正面翻反面的定时器
    QTimer *timer2;//反面翻正面的定时器
    int min=1;
    int max=8;
    //执行动画的标志
    bool is_animation=false;
    void mousePressEvent(QMouseEvent *e);
    bool is_win=false;
signals:

};

#endif // MY_COIN_H
