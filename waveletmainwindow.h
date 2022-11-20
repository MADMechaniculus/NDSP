#ifndef WAVELETMAINWINDOW_H
#define WAVELETMAINWINDOW_H

#include <QMainWindow>

#include "visualuzerwindow.h"
#include "waveformopeningdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WaveletMainWindow; }
QT_END_NAMESPACE

class WaveletMainWindow : public QMainWindow
{
    Q_OBJECT

    VisualuzerWindow * viz;

public:
    WaveletMainWindow(QWidget *parent = nullptr);
    ~WaveletMainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WaveletMainWindow *ui;
};
#endif // WAVELETMAINWINDOW_H
