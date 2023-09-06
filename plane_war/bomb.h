#ifndef BOMB_H
#define BOMB_H
#include "config.h"
#include <QPixmap>
#include <QVector>

class bomb
{
public:
    bomb();
    void update_info();//更新信息（播放图片下标、播放间隔）
    QVector<QPixmap> m_pix_arr;//放爆炸图片的数组
    int m_x,m_y;//爆炸位置
    bool m_free;//爆炸状态
    int m_recorder;//距离上次切换图片的时间间隔
    int m_index;//当前加载的图片下标
};

#endif // BOMB_H
