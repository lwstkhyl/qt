#include "choose_level_scene.h"
#include <QMenuBar>
#include <QPainter>
#include "my_pushbutton.h"
#include <QTimer>
#include <QVector>
#include <QLabel>
#include <QDebug>
#include <QSound>
choose_level_scene::choose_level_scene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(320,588);//设置大小
    this->setWindowIcon(QIcon(":/Coin0001.png"));//设置图标
    this->setWindowTitle("选择关卡场景");//设置标题

    QMenuBar * bar=menuBar();//创建菜单栏
    setMenuBar(bar);
    QMenu * start_menu=bar->addMenu("开始");//创建开始菜单
    QAction * quit_action=start_menu->addAction("退出");//创建退出菜单项
    connect(quit_action,&QAction::triggered,[=](){
        this->close();
    });
    //选择关卡按钮音效
    QSound * choose_sound = new QSound(":/CoinFlip_res_TapButtonSound.wav",this);
    //返回按钮音效
    QSound * back_sound= new QSound(":/CoinFlip_res_BackButtonSound.wav",this);
    //返回按钮
    my_pushbutton * back_btn =new my_pushbutton(":/BackButton.png",":/BackButtonSelected.png");
    back_btn->setParent(this);
    back_btn->move(this->width()-back_btn->width(),this->height()-back_btn->height());//把按钮放到右下角
    //点击后返回
    connect(back_btn,&my_pushbutton::clicked,[=](){
        //播放返回按钮音效
        back_sound->play();

        QTimer ::singleShot(500,this,[=](){//设置延迟返回，若不想延时就直接写发送信号
            emit this->choose_scene_back();
        });
    });
    //创建选择关卡的按钮
    //可以用二重循环，也可以只用一个循环
    for(int i=0;i<20;i++)
    {
        my_pushbutton * menu_btn= new my_pushbutton(":/LevelIcon.png");
        menu_btn->setParent(this);
        //用%和/控制move距离
        menu_btn->move(25+i%4*70,130+i/4*70);//加号前的是起始距离
        QLabel * label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menu_btn->width(),menu_btn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);
        //这样是把label和按钮重合，但数字是从左往右写的
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置label上文字对齐方式：水平居中和垂直居中
        //设置让鼠标能穿透label
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
        connect(menu_btn,&my_pushbutton::clicked,[=](){
            //播放选择关卡音效
            choose_sound->play();
            QString str=QString::number(i+1);
            QTimer ::singleShot(500,this,[=](){
                //进入到游戏场景
                this->hide();//将选关场景隐藏掉
                play = new play_scene(i+1);//创建游戏场景,并捕获选关信息
                //设置游戏场景的初始位置
                play->setGeometry(this->geometry());
                play->show();//显示游戏场景
                connect(play,&play_scene::play_scene_back,[=](){
                    this->setGeometry(play->geometry());
                    this->show();
                    delete play;
                    play=NULL;
                //因为是在lambda里面创建的play窗口，所以要在同一个lambda里监听
                });
            });
        });
        connect(menu_btn,&my_pushbutton::enter_menu_btn,[=](){
            QPixmap pix;
            bool ret= pix.load(":/Coin0001.png");
            if(!ret)
            {
                qDebug()<<"图片加载失败";
                return;
            }
            menu_btn->setIcon(pix);
        });
        connect(menu_btn,&my_pushbutton::leave_menu_btn,[=](){
            QPixmap pix;
            bool ret= pix.load(":/LevelIcon.png");
            if(!ret)
            {
                qDebug()<<"图片加载失败";
                return;
            }
            menu_btn->setIcon(pix);
        });
    }
}
void choose_level_scene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
