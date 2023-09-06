#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPaintEvent>
#include <QPainter>
#include <my_pushbutton.h>
#include <QDebug>
#include <QTimer>
#include <QSound>
mainScene::mainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainScene)
{
    ui->setupUi(this);
    //配置主场景
    //设置固定大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币主场景");
    //退出按钮的实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //准备开始按钮的音效
    QSound * start_sound = new QSound(":/CoinFlip_res_TapButtonSound.wav",this);
    //写开始按钮
    my_pushbutton *start_btn = new my_pushbutton(":/MenuSceneStartButton.png");
    start_btn->setParent(this);
    start_btn->move(this->width()*0.5-start_btn->width()*0.5,this->height()*0.7);//注意这块不是正中间
    //实例化选择关卡场景
    choose_scene=new choose_level_scene;
    connect(start_btn,&my_pushbutton::clicked,[=](){
        //播放开始音效
        start_sound->play();
        //做一个弹起的特效
        start_btn->zoom1();
        start_btn->zoom2();
        //进入到选择关卡场景中
        QTimer::singleShot(500,this,[=](){//在0.5后让this执行下面的函数
            //设置选择关卡场景的位置
            choose_scene->setGeometry(this->geometry());
            this->hide();//自身隐藏
            choose_scene->show();//显示选择关卡场景
        });//此时按钮跳完之后才进入下个场景   
    });
    //监听选择关卡的返回按钮的信号
    connect(choose_scene,&choose_level_scene::choose_scene_back,this,[=](){
        this->setGeometry(choose_scene->geometry());
        choose_scene->hide();//将选择关卡场景隐藏掉
        this->show();//重新显示主场景
    });

}
void mainScene::paintEvent(QPaintEvent *)
{
    //画背景图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //前两个参数为起始位置，第3，4个参数为把图片拉伸成窗口大小

    //画背景上的图标
    pix.load(":/Title.png");
    //缩放图片
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);//都缩小成0.5倍
    painter.drawPixmap(10,30,pix);

}
mainScene::~mainScene()
{
    delete ui;
}

