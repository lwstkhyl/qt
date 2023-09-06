#include "enemy_plane.h"
#include "config.h"
enemy_plane::enemy_plane()
{
    m_enemy.load(enemy_path);//敌机资源加载
    m_x=0;
    m_y=0;//因为之后还要随机赋值，所以位置初始值无所谓
    m_free=true;
    m_speed=enemy_speed;
    m_rect.setWidth(m_enemy.width());
    m_rect.setHeight(m_enemy.height());
    m_rect.moveTo(m_x,m_y);
}
void enemy_plane::update_position()
{
    if(m_free==true)
        return;//空闲状态不计算坐标
    m_y+=m_speed;//从上往下飞
    m_rect.moveTo(m_x,m_y);
    if(m_y>=game_height)//如果出界
        m_free=true;//就设为空闲
}
