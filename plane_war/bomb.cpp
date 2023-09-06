#include "bomb.h"
#include <QString>
bomb::bomb()
{
    //将爆炸需要的7张图放进一个数组中
    for(int i=1;i<=bomb_max;i++)
    {
        //因为config中bombpath是有%1占位的，现需要把占位用i替代，形成一个完整有效的路径
        QString str=QString(bomb_path).arg(i);//完整路径是":/res/bomb-2.png"的形式
        m_pix_arr.push_back(QPixmap(str));
    }
    m_x=0;
    m_y=0;
    m_free=true;
    m_index=0;
    m_recorder=0;
}
void bomb::update_info()
{
    if(m_free==true)//空闲状态不进行爆炸
        return;
    m_recorder++;
    if(m_recorder<bomb_interval)//爆炸切换图片时间小于间隔，不进行切换图片
        return;
    m_recorder=0;//重置时间
    m_index++;
    if(m_index>bomb_max-1)//爆炸图片播放完毕
    {
        m_index=0;//重置下标，准备下一次爆炸
        m_free=true;//变为空闲状态
    }
}
