#include "bullet.h"
bullet::bullet()
{
    m_bullet.load(bullet_path);//加载子弹资源
    m_x=game_width/2-m_bullet.width()/2;
    m_y=game_height;//初始位置可以设置成界面中间，但无所谓
    m_free=true;//开始为空闲状态
    m_speed=bullet_speed;
    m_rect.setWidth(m_bullet.width());
    m_rect.setHeight(m_bullet.height());
    m_rect.moveTo(m_x,m_y);
}
void bullet::update_position()
{
    if(m_free==true)//空闲状态下不需要计算坐标
        return;
    m_y-=m_speed;
    m_rect.moveTo(m_x,m_y);//非空闲就向上移动
    if(m_y<=-m_rect.height())//如果向上移动出界面
        m_free=true;//就改为空闲状态
}
