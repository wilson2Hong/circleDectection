#include "circledectection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    circleDectection w;
    w.show();
    w.circleDected();

    return a.exec();
}
