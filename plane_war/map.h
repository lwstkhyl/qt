#ifndef MAP_H
#define MAP_H
#include <QPixmap>

class map
{
public:
    map();//构造函数
    void map_position();//地图滚动坐标计算
    QPixmap m_map1;
    QPixmap m_map2;//创建两个图片对象
    int m_map1_pos_y,m_map2_pos_y;//地图y轴坐标
    int m_scroll_speed;//地图滚动速度
};

#endif // MAP_H
