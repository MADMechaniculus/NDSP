#include "visualuzerwindow.h"
#include "ui_visualuzerwindow.h"

VisualuzerWindow::VisualuzerWindow(dsp::Waveform && wave, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VisualuzerWindow)
{
    ui->setupUi(this);

    this->wave = std::make_shared<dsp::Waveform>(wave);

    this->wave->draw(this->ui->plotter);
}

VisualuzerWindow::~VisualuzerWindow()
{
    delete ui;
}
