#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include <QWidget>
#include "bird.h"
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class main_scene; }
QT_END_NAMESPACE

class main_scene : public QWidget
{
    Q_OBJECT

public:
    main_scene(QWidget *parent = nullptr);
    ~main_scene();
    bird *m_bird;//创建鸟对象的指针
    void paintEvent(QPaintEvent *event);//重写绘图事件
    QTimer *timer;//自动移动的定时器
    QPoint m_auto_pos;//记录自动移动的位置
private:
    Ui::main_scene *ui;
};
#endif // MAIN_SCENE_H
