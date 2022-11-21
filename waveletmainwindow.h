#ifndef WAVELETMAINWINDOW_H
#define WAVELETMAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "visualuzerwindow.h"
#include "waveformopeningdialog.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
#include <sys/stat.h>

QT_BEGIN_NAMESPACE
namespace Ui { class WaveletMainWindow; }
QT_END_NAMESPACE

static int64_t getSize(std::string path) {
    struct stat stBuffer;
    if (stat(path.c_str(), &stBuffer) == 0) {
        return stBuffer.st_size;
    }
    return -1;
}

class WaveletMainWindow : public QMainWindow
{
    Q_OBJECT

    VisualuzerWindow * viz;
    std::queue<VisualuzerWindow *> visuzlizers;

public:
    WaveletMainWindow(QWidget *parent = nullptr);
    ~WaveletMainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WaveletMainWindow *ui;
};
#endif // WAVELETMAINWINDOW_H
