#include "waveformopeningdialog.h"
#include "ui_waveformopeningdialog.h"

WaveFormOpeningDialog::WaveFormOpeningDialog(QString &path, uint16_t &dataType, QWidget *parent) :
    path(path),
    dataType(dataType),
    QDialog(parent),
    ui(new Ui::WaveFormOpeningDialog)
{
    ui->setupUi(this);

    this->ui->comboBox->clear();

    for (size_t i = 0; i < 8 /* count of items in emun */; i++) {
        this->ui->comboBox->addItem(QString(niistt::dsp::Waveform::Waveform_DataType_ItemName(i)));
    }

}

WaveFormOpeningDialog::~WaveFormOpeningDialog()
{
    delete ui;
}

void WaveFormOpeningDialog::on_buttonBox_accepted()
{
    this->dataType = this->ui->comboBox->currentIndex();
}

void WaveFormOpeningDialog::on_toolButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Waveform"), "/home", \
                                                    tr("IQ16 (*.iq16);;IQ32 (*.iq32);;"
                                                       "IQ Float (*.iqFloat);;"
                                                       "IQ Double (*.iqDouble);;"
                                                       "Plain (*.float *.double *.int16 *.int32);;"
                                                       "Binary (*.bin *.dat);;"
                                                       "All (*.*)"));
    if (!fileName.isEmpty()) {
        this->path = fileName;
        this->ui->lineEdit->setText(this->path);
    } else {
        this->path.clear();
    }
}


void WaveFormOpeningDialog::on_buttonBox_rejected()
{
    this->path.clear();
}

