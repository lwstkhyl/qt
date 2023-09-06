#include "play_scene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include "my_pushbutton.h"
#include <QTimer>
#include <QLabel>
#include "my_coin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSound>
//play_scene::play_scene(QWidget *parent) : QMainWindow(parent)
//{

//}
play_scene::play_scene(int level_num)
{
    QString str = QString("进入了第%1关").arg(level_num);
    qDebug()<<str;
    this->level_index=level_num;
    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");
    //直接用关卡选择界面中的
    QMenuBar * bar=menuBar();
    setMenuBar(bar);
    QMenu * start_menu=bar->addMenu("开始");
    QAction * quit_action=start_menu->addAction("退出");
    connect(quit_action,&QAction::triggered,[=](){
        this->close();
    });
    //返回按钮音效
    QSound * back_sound= new QSound(":/CoinFlip_res_BackButtonSound.wav",this);
    //翻金币音效
    QSound * flip_sound = new QSound(":/CoinFlip_res_ConFlipSound.wav",this);
    //胜利按钮音效
    QSound * win_sound = new QSound(":/CoinFlip_res_LevelWinSound.wav",this);
    //返回按钮--直接从chooselevelscene中拿
    my_pushbutton * back_btn =new my_pushbutton(":/BackButton.png",":/BackButtonSelected.png");
    back_btn->setParent(this);
    back_btn->move(this->width()-back_btn->width(),this->height()-back_btn->height());
    connect(back_btn,&my_pushbutton::clicked,[=](){
        //播放返回按钮音效
        back_sound->play();
        QTimer ::singleShot(500,this,[=](){
            emit this->play_scene_back();
        });
    });
    QLabel *label = new QLabel;
    label->setParent(this);
    QFont font;//字体
    font.setFamily("华文新魏");
    font.setPointSize(15);
    QString str1= QString("Level:%1").arg(this->level_index);
    label->setFont(font);//将字体设置到标签控件中
    label->setText(str1);
    label->setGeometry(30,this->height()-50,120,80);//相当于同时设定
//    label->setFixedSize(120,50);
//    label->move(30,this->height()-50);

    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->game_array[i][j] = config.mData[this->level_index][i][j];
            //QMap<int, QVector< QVector<int> > >mData;
            //mData的第[this->level_index]个参数对应第几关
            //mData[this->level_index]是一个二维容器，赋值操作把存储值取到game_array中
        }
    }
    //胜利图片显示
    QLabel * win_label = new QLabel;
    QPixmap tmp_pix;
    tmp_pix.load(":/LevelCompletedDialogBg.png");
    win_label->setGeometry(0,0,tmp_pix.width(),tmp_pix.height());
    win_label->setPixmap(tmp_pix);
    win_label->setParent(this);
    win_label->move((this->width()-tmp_pix.width())*0.5,-tmp_pix.height());//负号就是显示在界面上面，看不到
    //只有胜利时图片才从上面下来

    //显示金币背景图片
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            //绘制背景图片
            QLabel * label = new QLabel;
            label->setParent(this);
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/BoardNode.png"));
            label->move(57+i*50,200+j*50);
            //创建金币
            QString str;
            if(this->game_array[i][j]==1)
            {
                //显示金币
                str=":/Coin0001.png";
            }
            else
            {
                str=":/Coin0008.png";
            }
            my_coin * coin = new my_coin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            //给金币的属性赋值
            coin->pos_x=i;
            coin->pox_y=j;
            coin->flag=this->game_array[i][j];//1正面（金币）  0反面（银币）
            coin_btn[i][j]=coin;//将金币放入到金币的二维数组里，便于后期的维护
            //点击金币，进行翻转
            connect(coin,&my_coin::clicked,[=](){
                //播放翻金币音效
                flip_sound->play();
                //点击按钮，将所有的按钮都禁用
                for(int i=0;i<4;i++)
                    for(int j=0;j<4;j++)
                    {
                        this->coin_btn[i][j]->is_win=true;
                    }//因为出现胜利图片之前还会有一次判断胜利，不用担心被误判胜利
                //if(coin->is_animation==false)
                //{
                coin->change_flag();
                this->game_array[i][j]=this->game_array[i][j]==0?1:0;
                //}
                //翻转周围金币(延时翻转）
                QTimer::singleShot(300,this,[=](){
                    if(coin->pos_x+1<=3)//右侧金币翻转条件（注意posx是从0开始的，所以等号右侧为3）
                    {
                        coin_btn[coin->pos_x+1][coin->pox_y]->change_flag();
                        this->game_array[coin->pos_x+1][coin->pox_y]=this->game_array[coin->pos_x+1][coin->pox_y]==0?1:0;
                    }
                    if(coin->pos_x-1>=0)//左侧金币翻转条件
                    {
                        coin_btn[coin->pos_x-1][coin->pox_y]->change_flag();
                        this->game_array[coin->pos_x-1][coin->pox_y]=this->game_array[coin->pos_x-1][coin->pox_y]==0?1:0;
                    }
                    if(coin->pox_y+1<=3)//下侧金币翻转条件
                    {
                        coin_btn[coin->pos_x][coin->pox_y+1]->change_flag();
                        this->game_array[coin->pos_x][coin->pox_y+1]=this->game_array[coin->pos_x][coin->pox_y+1]==0?1:0;
                    }
                    if(coin->pox_y-1>=0)//上侧金币翻转条件
                    {
                        coin_btn[coin->pos_x][coin->pox_y-1]->change_flag();
                        this->game_array[coin->pos_x][coin->pox_y-1]=this->game_array[coin->pos_x][coin->pox_y-1]==0?1:0;
                    }
                    //翻完周围金币后，将所有金币解开禁用
                    for(int i=0;i<4;i++)
                        for(int j=0;j<4;j++)
                        {
                            this->coin_btn[i][j]->is_win=false;
                        }
                    //注意区分this(play_scene)和coin_btn[i][j]里的is_win不一样，这里都是改变coin_btn的iswin，目的是对应mycoin里的事件拦截器
                    //等到所有金币都翻完后判断是否胜利
                    this->is_win=true;
                    for(int i=0;i<4;i++)
                        for(int j=0;j<4;j++)
                        {
                            if(coin_btn[i][j]->flag==false)
                            {
                                this->is_win=false;
                                i=5;//退出两层循环
                                break;
                            }
                        }
                    if(this->is_win==true)
                    {
                        //添加胜利音效
                        win_sound->play();
                        qDebug()<<"胜利";
                        //将所有按钮的胜利标志改为true
                        for(int i=0;i<4;i++)
                            for(int j=0;j<4;j++)
                            {
                                coin_btn[i][j]->is_win=true;
                            }
                        //将胜利图片砸下来
                        QPropertyAnimation * animation = new QPropertyAnimation(win_label,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(win_label->x(),win_label->y(),win_label->width(),win_label->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(win_label->x(),win_label->y()+180,win_label->width(),win_label->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();
                    }
                });
            });
        }
    }
}
//先在头文件中重写绘图事件
void play_scene::paintEvent(QPaintEvent *)
{//直接用关卡选择界面中的
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
