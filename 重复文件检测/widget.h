#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>
#include <QHash>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    QString file_path;
    QStringList getfiles(const QString& path);//获取path下所有文件的路径
    QByteArray get_file_md5(const QString& path);//获取path路径文件的MD5
    QHash<QByteArray,QStringList> md5_filelist;//把所有MD5值相同的文件存入一个qstringlist里面，有多少个MD5就有多少个pair
    QHash<qint64,QStringList> size_filelist;
    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
