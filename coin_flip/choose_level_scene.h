#ifndef CHOOSE_LEVEL_SCENE_H
#define CHOOSE_LEVEL_SCENE_H

#include <QMainWindow>
#include "play_scene.h"
class choose_level_scene : public QMainWindow
{
    Q_OBJECT
public:
    explicit choose_level_scene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    play_scene * play = NULL;
    signals:
    //写一个自定义信号，告诉主场景点击了返回
    void choose_scene_back();


};

#endif // CHOOSE_LEVEL_SCENE_H
