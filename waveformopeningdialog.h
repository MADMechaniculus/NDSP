#ifndef WAVEFORMOPENINGDIALOG_H
#define WAVEFORMOPENINGDIALOG_H

#include <QDialog>

namespace Ui {
class WaveFormOpeningDialog;
}

class WaveFormOpeningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WaveFormOpeningDialog(QWidget *parent = nullptr);
    ~WaveFormOpeningDialog();

private:
    Ui::WaveFormOpeningDialog *ui;
};

#endif // WAVEFORMOPENINGDIALOG_H
