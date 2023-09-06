#include "main_scene.h"
#include <QResource>
#include <QApplication>
#include "config.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QResource::registerResource(game_res_path);
    main_scene w;
    w.show();
    return a.exec();
}
