#ifndef VISUALUZERWINDOW_H
#define VISUALUZERWINDOW_H

#include <QMainWindow>

#include "dsp.hpp"

namespace dsp = niistt::dsp;

namespace Ui {
class VisualuzerWindow;
}

class VisualuzerWindow : public QMainWindow
{
    Q_OBJECT
    std::shared_ptr<dsp::Waveform> wave;

public:
    explicit VisualuzerWindow(dsp::Waveform && wave, QWidget *parent = nullptr);
    ~VisualuzerWindow();

private:
    Ui::VisualuzerWindow *ui;
};

#endif // VISUALUZERWINDOW_H
