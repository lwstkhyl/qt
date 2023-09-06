#ifndef HERO_PLANE_H
#define HERO_PLANE_H
#include<QPixmap>
#include<QRect>
#include "bullet.h"
class hero_plane
{
public:
    hero_plane();
    void shoot();//子弹发射
    void set_position(int x,int y);//设置飞机位置
public:
    QPixmap m_plane;//飞机图片对象
    int m_x,m_y;//飞机坐标
    QRect m_rect;//飞机矩形边框
    bullet m_bullets[bullet_num];//弹匣
    int m_recorder=0;//发射间隔记录
};

#endif // HERO_PLANE_H
