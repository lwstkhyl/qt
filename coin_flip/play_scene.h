#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include <QMainWindow>
#include "my_coin.h"
class play_scene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit play_scene(QWidget *parent = nullptr);
    play_scene(int level_num);
    int level_index;//内部成员属性记录所选关卡
    void paintEvent(QPaintEvent *);
    int game_array[4][4];//二维数组，维护每个关卡的具体数据
    my_coin * coin_btn[4][4];
    bool is_win;
signals:
    void play_scene_back();//名称其实可以重复
};

#endif // PLAY_SCENE_H
