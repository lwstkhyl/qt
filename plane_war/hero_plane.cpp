#include "hero_plane.h"
#include "config.h"
hero_plane::hero_plane()
{
    m_plane.load(hero_plane_path);//初始化加载飞机图片资源
    m_x=(game_width-m_plane.width())/2;
    m_y=game_height-m_plane.height();//初始化坐标
    m_rect.setWidth(m_plane.width());
    m_rect.setHeight(m_plane.height());//设置矩形边框宽高
    m_rect.moveTo(m_x,m_y);//设置矩形边框位置
}
void hero_plane::shoot()
{    
    m_recorder++;//累加时间间隔记录变量
    if(m_recorder<bullet_interval)
        return;//如果没达到时间间隔，就不发射子弹
    m_recorder=0;//如果达到就重置记录变量并发射
    for(int i=0;i<bullet_num;i++)//遍历弹匣数组来找一颗空闲的子弹进行发射
    {
        if(m_bullets[i].m_free==true)//如果空闲就发射子弹
        {
            m_bullets[i].m_free=false;//把它变成不空闲
/*            m_bullets[i].m_x=m_x;
            m_bullets[i].m_y=m_y;*///设置子弹坐标同飞机坐标，因为是从飞机开始发射
            m_bullets[i].m_x=m_x+m_rect.width()/2-10;
            m_bullets[i].m_y=m_y-25;
            break;//发射完就退出循环
        }
    }
}
void hero_plane::set_position(int x, int y)
{
    m_x=x;
    m_y=y;
    m_rect.moveTo(x,y);
}
