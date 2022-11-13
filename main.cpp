#include "waveletmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WaveletMainWindow w;
    w.show();
    return a.exec();
}
