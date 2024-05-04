#include "MeshProcessor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MeshProcessor w;
    w.show();
    return a.exec();
}
