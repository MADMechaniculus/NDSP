#include "visualuzerwindow.h"
#include "ui_visualuzerwindow.h"

VisualuzerWindow::VisualuzerWindow(dsp::Waveform && wave, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VisualuzerWindow)
{
    ui->setupUi(this);

    this->wave = std::make_shared<dsp::Waveform>(wave);
}

VisualuzerWindow::~VisualuzerWindow()
{
    delete ui;
}
