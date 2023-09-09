#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QDebug>
#include <QCryptographicHash>
#include <QApplication>
#include <QDir>
#include <QFileInfoList>
#include <QFileDialog>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->open_file_button,&QPushButton::clicked,this,[=](){
        QString file_path_choose=QFileDialog::getExistingDirectory(this,"打开文件","C:\\Users\\17185\\Desktop\\c++\\qt");
        if(file_path_choose.isEmpty()==true)
        {
            QMessageBox::warning(this,"打开文件","选择的文件路径不能为空");
            return;
        }
        ui->file_path_edit->setText(file_path_choose);
    });
    connect(ui->get_files,&QPushButton::clicked,this,[=](){
        file_path=ui->file_path_edit->text();
        QStringList file_list=getfiles(file_path);
        if(file_path.isEmpty()==true)
        {
            QMessageBox::warning(this,"选择文件","请选择文件路径");
            return;
        }
        //用文件大小检索文件↓
        size_filelist.clear();//如果不clear，当重复检测两次时，上一次的文件就会当成这次的文件一起检测，导致假的重复
        for(int i=0;i<file_list.count();i++)
        {
            QFile file(file_list.at(i));
            qint64 file_size;
            if (file.open(QIODevice::ReadOnly))
                file_size=file.size();
            size_filelist[file_size].append(file_list.at(i));
        }
        file_list.clear();//清空file_list
        for(auto beg=size_filelist.begin();beg!=size_filelist.end();beg++)
            if(beg.value().count()>1)//如果该大小有多个文件，就把它加入file_list中
                for(int i=0;i<beg.value().count();i++)
                    file_list.append(beg.value().at(i));
        //用MD5检索文件↓
        md5_filelist.clear();
        for(int i=0;i<file_list.count();i++)
        {
            QString file_name=file_list[i];
            QByteArray md5=get_file_md5(file_name);
            //qDebug()<<"filename:"<<QString(file_name)<<"md5:"<<QString(md5);
            md5_filelist[md5].append(file_name);//md5_filelist[md5]通过key来访问value，得到该MD5对应的qstringlist，如果没有这个MD5就创建一个pair（key为这个MD5）
        }
        //显示结果↓
        ui->file_name->setText("查找范围："+file_path);
        int flag=0;
        for(auto beg=md5_filelist.begin();beg!=md5_filelist.end();beg++)//遍历qhash
        {
            //qDebug()<<"md5:"<<beg.key()<<"value count"<<beg.value().count();
            if(beg.value().count()>1)//如果qstringlist里面的元素数量>1，说明有重复文件
            {
                flag=1;
                ui->file_name->append("重复文件：");
                for(int i=0;i<beg.value().count();i++)
                    ui->file_name->append(beg.value().at(i));
                ui->file_name->append("\n");
            }
        }
        if(flag==0)
            ui->file_name->append("无重复文件");
    });
}
QStringList Widget::getfiles(const QString &path)
{
    QStringList result;
    QDir dir(path);//dir存储path目录下的所有文件和文件夹路径
    QFileInfoList info_list=dir.entryInfoList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);//..表示上一级目录，不需要上一级的路径，这样info_list就只包含path里面的文件路径
    for(int i=0;i<info_list.count();i++)//循环次数为info_list的元素数
    {
        QFileInfo info=info_list.at(i);
        if(info.isDir())//如果这个路径是一个文件夹，就递归调用getfiles函数来获取里面的文件，再放到结果里面
        {
            QString sub_dir=info.absoluteFilePath();//获取文件夹的绝对路径
            QStringList files=getfiles(sub_dir);
            result.append(files);
        }
        else//如果是一个文件就直接放到结果里面
        {
            QString file_name=info.absoluteFilePath();
            result.append(file_name);
        }
    }
    return result;
}
QByteArray Widget::get_file_md5(const QString &path)
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly))//如果文件打开成功
    {
        QCryptographicHash hash(QCryptographicHash::Md5);
        while(!file.atEnd())//因为有的文件可能很大，所有要分段读取文件来计算MD5
        {
            QByteArray content=file.read(100*1024*1024);//一次读取100M字节的信息
            hash.addData(content);//把这段文件添加到MD5的计算中
        }
        QByteArray md5=hash.result().toHex();//最终计算结果，转成16进制输出
        file.close();
        return md5;
    }
    return QByteArray();//如果不成功就返回空值
}
Widget::~Widget()
{
    delete ui;
}

