#include "bird.h"

bird::bird(QWidget *parent) : QWidget(parent)
{
    for(int i=0;i<this->max;i++)
    {
        QString str=QString(":/bird%1.png").arg(i+1);
        this->m_bird_pix.load(str);
    }
    this->setFixedSize(this->m_bird_pix.width(),this->m_bird_pix.height());//设置鸟的尺寸
    //默认情况下鸟的尺寸和屏幕一样大，会导致拖拽时出现误差
    this->timer=new QTimer(this);//创建定时器对象
    connect(timer,&QTimer::timeout,[=](){
        QString str=QString(":/bird%1.png").arg(this->min++);//从bird1.png开始
        this->m_bird_pix.load(str);
        if(this->min>this->max)
            this->min=1;//如果加到了最大值就要进行重置
        emit change_pix();//发出切换了图片的信号，让主场景知道图片发生了改变
    });
    this->m_menu=new QMenu();//创建菜单对象
    connect(this->m_menu->addAction("退出"),&QAction::triggered,[=](){
        //this->m_menu->addAction("退出")会创建一个“退出”的选项，同时返回该选项，将创建和使用该选项和为一体
        exit(0);//关闭窗口并退出程序
    });
}
void bird::running()
{
    this->timer->start(50);//启动定时器，每隔50ms切张图
}
void bird::mousePressEvent(QMouseEvent *event)
{
    this->m_oaPos=event->globalPos();
    this->m_obPos=((QWidget*)this->parent())->frameGeometry().topLeft();//this->parent()指bird所在的窗口，调用返回值不确定，需要强制转换成QWidget*类型
    //frameGeometry().topLeft()是窗口左上角的点
    this->m_Pos=this->m_oaPos-this->m_obPos;
    this->mouse_press=true;//鼠标按下时状态为true
    if(event->button()==Qt::RightButton)//判断按下的是不是右键
    {
        this->m_menu->popup(QCursor::pos());//弹出菜单，参数为弹出的位置，QCursor::pos()表示当前鼠标的位置
    }
    //如果菜单消失（不是点击退出），鸟应该继续向前飞
    connect(this->m_menu,&QMenu::aboutToHide,[=](){//&QMenu::aboutToHide是菜单消失的信号
        this->mouse_press=false;//将鼠标设为松开的状态
    });
}
void bird::mouseReleaseEvent(QMouseEvent *event)
{
    this->mouse_press=false;//鼠标释放时状态为false
}
void bird::mouseMoveEvent(QMouseEvent *event)
{
    this->m_oaPos=event->globalPos();//改变向量OA的值,注意QMouseEvent和QMouseEvent中globalPos不同
    this->m_obPos=this->m_oaPos-this->m_Pos;//改变向量OB的值
    //在移动过程中得到窗口最终移动到的位置OB，用信号发送给窗口
    emit this->moving(this->m_obPos);
}
