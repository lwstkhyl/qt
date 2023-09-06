#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "choose_level_scene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class mainScene; }
QT_END_NAMESPACE

class mainScene : public QMainWindow
{
    Q_OBJECT

public:
    mainScene(QWidget *parent = nullptr);
    ~mainScene();
    void paintEvent(QPaintEvent *);
    choose_level_scene * choose_scene= NULL;
private:
    Ui::mainScene *ui;
};
#endif // MAINSCENE_H
