#ifndef WAVEFORMOPENINGDIALOG_H
#define WAVEFORMOPENINGDIALOG_H

#include <QDialog>
#include <QString>
#include <QFileDialog>

#include "dsp.hpp"

namespace Ui {
class WaveFormOpeningDialog;
}

class WaveFormOpeningDialog : public QDialog
{
    Q_OBJECT

    QString & path;
    uint16_t & dataType;

public:
    explicit WaveFormOpeningDialog(QString &path, uint16_t &dataType, QWidget *parent = nullptr);
    ~WaveFormOpeningDialog();

private slots:
    void on_buttonBox_accepted();
    void on_toolButton_clicked();

    void on_buttonBox_rejected();

private:
    Ui::WaveFormOpeningDialog *ui;
};

#endif // WAVEFORMOPENINGDIALOG_H
