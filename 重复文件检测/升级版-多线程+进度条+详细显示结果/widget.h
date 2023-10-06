#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>
#include <QHash>
#include <QStringList>
#include <QThread>
#include <QFile>
#include <QDebug>
#include <QCryptographicHash>
#include <QApplication>
#include <QDir>
#include <QFileInfoList>
#include <QFileDialog>
#include <QMessageBox>
#include "file_md5.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    QString file_path;
    QHash<QByteArray,QStringList> dumplate;//用于存储重复文件信息
    file_md5 *md5=new file_md5;//任务类
    QThread *thread=new QThread;//线程类
    ~Widget();
public slots:
    void show_dumplate(const QHash<QByteArray,QStringList> &dumps);//接收get_dumplate的信号
    void show_progress(int current,int total);//接收进度信号
signals:
    void start_check_dumplate(const QString &path);//启动计算目录下所有文件及其md5的信号
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
