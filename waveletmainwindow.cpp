#include "waveletmainwindow.h"
#include "./ui_waveletmainwindow.h"

WaveletMainWindow::WaveletMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WaveletMainWindow)
{
    ui->setupUi(this);

//    viz = new VisualuzerWindow(this);
}

WaveletMainWindow::~WaveletMainWindow()
{
    delete ui;
}


void WaveletMainWindow::on_pushButton_clicked()
{
    QString path = "";
    uint16_t dataType = 0;

    WaveFormOpeningDialog dialog(path, dataType, this);

    int ret = dialog.exec();
    if (ret == 0) {
        // Success
    }
    // Fail
}

