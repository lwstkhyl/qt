#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stop_check->setDisabled(true);
    md5->moveToThread(thread);
    connect(ui->open_file_button,&QPushButton::clicked,this,[=](){
        QString file_path_choose=QFileDialog::getExistingDirectory(this,"打开文件","C:\\Users\\17185\\Desktop\\c++\\qt");//默认打开界面是项目所在文件夹
        if(file_path_choose.isEmpty()==true)
        {
            QMessageBox::warning(this,"打开文件","选择的文件路径不能为空");
            return;
        }
        ui->file_path_edit->setText(file_path_choose);
    });
    connect(ui->get_files,&QPushButton::clicked,this,[=](){
        thread->start();//点击按钮后开始执行线程
        file_path=ui->file_path_edit->text();
        if(file_path.isEmpty()==true)
        {
            QMessageBox::warning(this,"选择文件","请选择文件路径");
            return;
        }
        //如果直接写md5->check_dumplate(file_path)，则该函数仍在主线程里执行（尽管函数是在任务类中声明），但调用是在主线程中
        emit start_check_dumplate(file_path);
        ui->get_files->setDisabled(true);
        ui->stop_check->setDisabled(false);
        ui->progress_bar->setValue(0);//进度条清零
        ui->file_listWidget->clear();
        ui->md5_listWidget->clear();//文本框清空
    });
    connect(ui->stop_check,&QPushButton::clicked,this,[=](){
        thread->terminate();//唯一能使线程能真正停下来，并且下次start是重新开始的方法，缺点是不稳定，当开始/停止反复切换次数很多时会崩
        ui->get_files->setDisabled(false);
        ui->stop_check->setDisabled(true);
        ui->progress_bar->setValue(0);
    });
    qRegisterMetaType<QHash<QByteArray,QStringList>>("QHash<QByteArray,QStringList>");//出现Make sure 'QHash<QByteArray,QStringList>' is registered using qRegisterMetaType().时添加
    connect(this,&Widget::start_check_dumplate,md5,&file_md5::check_dumplate);
    connect(md5,&file_md5::progress,this,&Widget::show_progress);//注意connect接收的两个对象md5和this都是指针
    connect(md5,SIGNAL(get_dumplate(QHash<QByteArray,QStringList>)),this,SLOT(show_dumplate(QHash<QByteArray,QStringList>)));//将file_md5线程返回的文件和MD5给主线程
    //等效于connect(md5,&file_md5::get_dumplate,this,&Widget::on_get_dumplate)，旧版本写法可以更方便的应对信号/槽有重载时的情况，需要将on_get_dumplate在.h中用public/private slots声明
    connect(ui->md5_listWidget,&QListWidget::currentTextChanged,[=](const QString &current_text){//该信号在改变选择的项时触发，以qstring类型传出选择的内容（即MD5）
        ui->file_listWidget->clear();//清空之前MD5的文件路径，以便显示这次的内容
        QStringList files=this->dumplate[current_text.toLocal8Bit()];//将qstring转成qbytearray类型，要不然不能通过键找值
        ui->file_listWidget->addItems(files);//additems函数可以接收list类型，而additem只能接收一个值
    });
}
void Widget::show_dumplate(const QHash<QByteArray, QStringList> &dumps)
{
    int flag=0;
    for(auto beg=dumps.begin();beg!=dumps.end();beg++)
    {
        if(beg.value().count()>1)
        {
            flag=1;
            ui->md5_listWidget->addItem(beg.key());//将重复文件的MD5显示到md5_listWidget中
            this->dumplate.insert(beg.key(),beg.value());//将重复的文件及其MD5存入dumplate中
        }
    }
    if(flag==0)
        ui->md5_listWidget->addItem("无重复文件");
}
void Widget::show_progress(int current, int total)
{
    ui->progress_bar->setMaximum(total);
    ui->progress_bar->setValue(current);//这样设置最大值和当前值就不用自己用除法计算进度百分数了
    if(ui->progress_bar->value()==total)//检测完成后退出线程
    {
        thread->exit();
        thread->wait();
        ui->get_files->setDisabled(false);
        ui->stop_check->setDisabled(true);
    }
}
Widget::~Widget()
{
    //如果线程类在widget.h中声明，可能需要在widget析构里加上
    //thread->exit();
    //thread->wait(10*1000);等待10s退出
    delete ui;
}

