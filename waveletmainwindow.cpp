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

    if (ret == 1) {
        int64_t fileSize = getSize(path.toStdString());

        switch (dataType) {
        case niistt::dsp::Waveform::Waveform_DataType_int16_iq:
        {
            if (fileSize % sizeof (niistt::dsp::datatypes::int16_iq_t) != 0) {
                QMessageBox::warning(this, tr("Waveform opening"),
                                     tr("Target file size not a multiple of int16_iq"),
                                     QMessageBox::Ok);
                return;
            }

            uint32_t samplesCount = fileSize / sizeof (niistt::dsp::datatypes::int16_iq_t);
            std::vector<double> timeline(samplesCount);
            std::vector<niistt::dsp::datatypes::int16_iq_t> samples(samplesCount);

            std::ifstream input(path.toStdString(), std::ios::binary);
            if (input.is_open()) {
                input.read((char*)samples.data(), fileSize);
                input.close();

                double counter = 0;
                std::for_each(std::begin(timeline), std::end(timeline), [&counter](double & item) { item = counter++; });

                niistt::dsp::Waveform wave(timeline, samples);



                this->visuzlizers.emplace(new VisualuzerWindow(std::move(wave), this));

            } else {
                QMessageBox::warning(this, tr("Waveform opening"),
                                     tr("Can`t open reading stream"),
                                     QMessageBox::Ok);
                return;
            }

            break;
        }
        case niistt::dsp::Waveform::Waveform_DataType_int32_iq:
        {
            break;
        }
        case niistt::dsp::Waveform::Waveform_DataType_float_iq:
        {
            break;
        }
        case niistt::dsp::Waveform::Waveform_DataType_double_iq:
        {
            break;
        }
        case niistt::dsp::Waveform::Waveform_DataType_int16_plain:
        {
            break;
        }
        case niistt::dsp::Waveform::Waveform_DataType_int32_plain:
        {
            break;
        }
        case niistt::dsp::Waveform::Waveform_DataType_float_plain:
        {
            break;
        }
        case niistt::dsp::Waveform::Waveform_DataType_double_plain:
        {
            break;
        }
        }
    }
    // Fail
}

