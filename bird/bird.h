#ifndef BIRD_H
#define BIRD_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QPoint>
#include <QMouseEvent>
#include <QMenu>
class bird : public QWidget
{
    Q_OBJECT
public:
    explicit bird(QWidget *parent = nullptr);
    QPixmap m_bird_pix;//鸟显示的图片资源
    int min=1,max=8;//图片最小值和最大值下标
    QTimer *timer;//定时器
    void running();//执行动画
    QPoint m_Pos,m_oaPos,m_obPos;//3个坐标
    void mouseMoveEvent(QMouseEvent *event);//重写鼠标移动事件
    void mousePressEvent(QMouseEvent *event);//重写鼠标按下事件
    bool mouse_press=false;//鼠标按下状态，默认没按
    void mouseReleaseEvent(QMouseEvent *event);//重写鼠标释放事件
    QMenu * m_menu;//创建菜单指针
signals:
    void change_pix();//正在切换图片的信号
    void moving(QPoint point);//移动窗口的信号
};

#endif // BIRD_H
