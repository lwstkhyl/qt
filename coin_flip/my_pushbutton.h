#ifndef MY_PUSHBUTTON_H
#define MY_PUSHBUTTON_H

#include <QPushButton>

class my_pushbutton : public QPushButton
{
    Q_OBJECT
public:
//    explicit my_pushbutton(QWidget *parent = nullptr);
    my_pushbutton(QString normal_img,QString press_img="");
    //参数1：正常显示的图片路径，参数2：按下后显示的图片路径
    QString normal_img_path;
    QString press_img_path;
    //成员属性：保存用户传入的默认显示路径和按下后的路径
    void zoom1();//向上跳
    void zoom2();//向下跳
    //重现按钮的按下和释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *);
    int pos;
signals:
    void enter_menu_btn();
    void leave_menu_btn();
    void kuozhan();

};

#endif // MY_PUSHBUTTON_H
