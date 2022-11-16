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
    this->viz->show();
}

