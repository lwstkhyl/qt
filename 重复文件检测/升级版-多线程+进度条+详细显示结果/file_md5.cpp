#include "file_md5.h"

file_md5::file_md5(QObject *parent) : QObject(parent)
{

}
void file_md5::check_dumplate(const QString &path)
{
    QStringList file_list=getfiles(path);
    ret.clear();
    i=0;
    qDebug()<<file_list.count();
    for(;i<file_list.count();i++)
    {
        QString file_name=file_list[i];
        QByteArray md5=get_file_md5(file_name);
        ret[md5].append(file_name);
        emit progress(i+1,file_list.count());//参数为当前是第几个文件i和文件总数量
    }
    emit get_dumplate(ret);
}
QStringList file_md5::getfiles(const QString &path)
{
    QStringList result;
    QDir dir(path);
    QFileInfoList info_list=dir.entryInfoList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);
    for(int i=0;i<info_list.count();i++)
    {
        QFileInfo info=info_list.at(i);
        if(info.isDir())
        {
            QString sub_dir=info.absoluteFilePath();
            QStringList files=getfiles(sub_dir);
            result.append(files);
        }
        else
        {
            QString file_name=info.absoluteFilePath();
            result.append(file_name);
        }
    }
    return result;
}
QByteArray file_md5::get_file_md5(const QString &path)
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        QCryptographicHash hash(QCryptographicHash::Md5);
        while(!file.atEnd())
        {
            QByteArray content=file.read(100*1024*1024);
            hash.addData(content);
        }
        QByteArray md5=hash.result().toHex();
        file.close();
        return md5;
    }
    return QByteArray();
}
