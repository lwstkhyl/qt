#ifndef ENEMY_PLANE_H
#define ENEMY_PLANE_H
#include<QRect>
#include<QPixmap>
class enemy_plane
{
public:
    enemy_plane();
    void update_position();//更新坐标
public:
    QPixmap m_enemy;
    int m_x,m_y;
    QRect m_rect;
    bool m_free;
    int m_speed;
};

#endif // ENEMY_PLANE_H
