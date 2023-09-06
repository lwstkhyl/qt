#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include <QWidget>
#include <QTimer>
#include "map.h"
#include "hero_plane.h"
#include "bullet.h"
#include "enemy_plane.h"
#include "bomb.h"
QT_BEGIN_NAMESPACE
namespace Ui { class main_scene; }
QT_END_NAMESPACE

class main_scene : public QWidget
{
    Q_OBJECT

public:
    main_scene(QWidget *parent = nullptr);
    ~main_scene();
    void init_scene(); //初始化场景
    QTimer m_timer;//设置图片滚动的定时器
    map m_map;//地图对象
    void play_game();//启动游戏
    void update_position();//更新游戏中所有元素的坐标
    void paintEvent(QPaintEvent *);
    hero_plane m_hero;//飞机对象
    void mouseMoveEvent(QMouseEvent *event);
    void enemy_to_scene();//敌机出场的函数
    enemy_plane m_enemys[enemy_num];//敌机的数组
    int m_recorder;//敌机出场间隔
    void collision_detection();//碰撞检测函数
    //bullet temp_bullet;
    bomb m_bombs[bomb_num];//爆炸的数组
private:
    Ui::main_scene *ui;
};
#endif // MAIN_SCENE_H
