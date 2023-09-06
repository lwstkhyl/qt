#include "map.h"
#include "config.h"
map::map()
{
    m_map1.load(map_path);
    m_map2.load(map_path);//加载地图对象
    m_map1_pos_y=-game_height;
    m_map2_pos_y=0;//初始化y轴坐标
    m_scroll_speed=map_scroll_speed;//设置地图滚动速度
}

void map::map_position()
{
    m_map1_pos_y += m_scroll_speed;//第一张地图滚动位置
    if(m_map1_pos_y>=0)//如果图片滚动到了边界
    {
        m_map1_pos_y=-game_height;//就重置
    }
    m_map2_pos_y += m_scroll_speed;//第一张地图滚动位置
    if(m_map2_pos_y>=game_height)
    {
        m_map2_pos_y=0;
    }
}
