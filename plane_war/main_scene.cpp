#include "main_scene.h"
#include "ui_main_scene.h"
#include "config.h"
#include "map.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <ctime>
#include <QSound>
main_scene::main_scene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::main_scene)
{
    ui->setupUi(this);
    init_scene();//调用初始化场景函数
    play_game();//启动游戏
}

main_scene::~main_scene()
{
    delete ui;
}

void main_scene::init_scene()
{
    //设置窗口固定尺寸
    setFixedSize(game_width,game_height);
    //设置标题
    setWindowTitle(game_title);
    //加载图标
    setWindowIcon(QIcon(":res/app.ico"));
    m_recorder=0;//初始化敌机出场的间隔时间
    srand((unsigned int)time(NULL));//设置随机数种子
}
void main_scene::play_game()
{
    QSound::play(sound_backgroud_path);
    m_timer.start(game_rate);//启动定时器
    connect(&m_timer,&QTimer::timeout,[=](){//监听定时器发送的信号
        update_position();//更新元素坐标
        update();//调用paintevent来更新图片
        enemy_to_scene();//敌机出场
        collision_detection();//碰撞检测
    });
}
void main_scene::update_position()
{
    m_map.map_position();//更新地图坐标
    m_hero.shoot();//发射子弹
    for(int i=0;i<bullet_num;i++)//更新所有非空闲子弹的坐标，从而使子弹移动
    {
        if(m_hero.m_bullets[i].m_free==false)
        {
            m_hero.m_bullets[i].update_position();
        }
    }
    for(int i=0;i<enemy_num;i++)
    {
        if(m_enemys[i].m_free==false)
        {
            m_enemys[i].update_position();
        }
    }
    for(int i=0;i<bomb_num;i++)
    {
        if(m_bombs[i].m_free==false)
        {
            m_bombs[i].update_info();
        }
    }
    //temp_bullet.m_free=false;//改变子弹空闲状态
    //temp_bullet.update_position();//更新子弹坐标
}
void main_scene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,m_map.m_map1_pos_y,m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_pos_y,m_map.m_map2);
    painter.drawPixmap(m_hero.m_x,m_hero.m_y,m_hero.m_plane);
    for(int i=0;i<bullet_num;i++)//画出所有非空闲子弹
    {
        if(m_hero.m_bullets[i].m_free==false)
        {
            painter.drawPixmap(m_hero.m_bullets[i].m_x,m_hero.m_bullets[i].m_y,m_hero.m_bullets[i].m_bullet);
        }
    }
    for(int i=0;i<enemy_num;i++)
    {
        if(m_enemys[i].m_free==false)
        {
            painter.drawPixmap(m_enemys[i].m_x,m_enemys[i].m_y,m_enemys[i].m_enemy);
        }
    }
    //painter.drawPixmap(temp_bullet.m_x,temp_bullet.m_y,temp_bullet.m_bullet);
    for(int i=0;i<bomb_num;i++)
    {
        if(m_bombs[i].m_free==false)
        {
            painter.drawPixmap(m_bombs[i].m_x,m_bombs[i].m_y,
                               m_bombs[i].m_pix_arr[m_bombs[i].m_index]);
        }
    }
}
void main_scene::mouseMoveEvent(QMouseEvent *event)
{
    //int x=event->x();
    //int y=event->y();//这样写会让飞机在鼠标的右下角
    int x=event->x()-m_hero.m_rect.width()/2;
    int y=event->y()-m_hero.m_rect.height()/2;
    //边界检测：防止飞机出界面
    if(x<=0)
        x=0;
    if(x>=game_width-m_hero.m_rect.width())
        x=game_width-m_hero.m_rect.width();
    if(y<=0)
        y=0;
    if(y>=game_height-m_hero.m_rect.height())
        y=game_height-m_hero.m_rect.height();
    m_hero.set_position(x,y);
}
void main_scene::enemy_to_scene()
{
    m_recorder++;
    if(m_recorder<enemy_interval)
        return;//没达到出场间隔就不出场
    m_recorder=0;//重置为0
    for(int i=0;i<enemy_num;i++)
    {
        if(m_enemys[i].m_free==true)//如果空闲就出场
        {
            m_enemys[i].m_free=false;
            m_enemys[i].m_x=rand()%(game_width-m_enemys[i].m_rect.width());
            m_enemys[i].m_y=-m_enemys[i].m_rect.height();
            break;
        }
    }
}
void main_scene::collision_detection()
{
    //先做敌机和子弹的碰撞检测
    for(int i=0;i<enemy_num;i++)//遍历所有非空闲的敌机
    {
        if(m_enemys[i].m_free==true)//如果空闲就找下一架飞机
            continue;
        for(int j=0;j<bullet_num;j++)//遍历所有非空闲的子弹
        {
            if(m_hero.m_bullets[j].m_free==true)//如果空闲就找下一个子弹
                continue;
            //如果程序到这就说明第i架飞机和第j个子弹都非空闲，进行检测
            if(m_enemys[i].m_rect.intersects(m_hero.m_bullets[j].m_rect))//intersects函数两边的矩形框碰撞就返回true
            {
                m_enemys[i].m_free=true;
                m_hero.m_bullets[j].m_free=true;//碰撞后都消失，即变为空闲状态
                for(int k=0;k<bomb_num;k++)//播放爆炸效果
                {
                    if(m_bombs[k].m_free==true)//找一个空闲的爆炸
                    {
                        QSound::play(sound_bomb_path);//播放爆炸音效
                        m_bombs[k].m_free=false;//更新爆炸状态
                        m_bombs[k].m_x=m_enemys[i].m_x;
                        m_bombs[k].m_y=m_enemys[i].m_y;//更新爆炸坐标
                        break;//不break：会在该位置上把爆炸数组中所有bomb都设为非空闲
                    }
                }
            }
        }
    }
}

