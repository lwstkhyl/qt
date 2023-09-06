#ifndef BULLET_H
#define BULLET_H

#include "config.h"
#include <QPixmap>
#include <QRect>
class bullet
{
public:
    bullet();
    void update_position();//更新坐标
public:
    QPixmap m_bullet;//子弹图片对象
    int m_x,m_y;//子弹坐标
    int m_speed;//子弹速度
    bool m_free;//是否闲置
    QRect m_rect;//矩形边框
};

#endif // BULLET_H
