#ifndef FILE_MD5_H
#define FILE_MD5_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QCryptographicHash>
#include <QApplication>
#include <QDir>
#include <QFileInfoList>
#include <QFileDialog>
#include <QMap>
#include <QHash>
#include <QStringList>
class file_md5 : public QObject
{
    Q_OBJECT
public:
    explicit file_md5(QObject *parent = nullptr);
    void check_dumplate(const QString &path);//计算目录下所有文件及其md5
    QStringList getfiles(const QString &path);//获取path下所有文件的路径
    QByteArray get_file_md5(const QString& path);//获取path路径文件的MD5
    QHash<QByteArray,QStringList> ret;
    int i;
signals:
    void get_dumplate(const QHash<QByteArray,QStringList> &dumps);//返回目录下所有文件及其md5的信号
    void progress(int current,int total);//传给主线程的进度信号
};

#endif // FILE_MD5_H
