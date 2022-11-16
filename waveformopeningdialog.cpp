#include "waveformopeningdialog.h"
#include "ui_waveformopeningdialog.h"

WaveFormOpeningDialog::WaveFormOpeningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaveFormOpeningDialog)
{
    ui->setupUi(this);
}

WaveFormOpeningDialog::~WaveFormOpeningDialog()
{
    delete ui;
}
