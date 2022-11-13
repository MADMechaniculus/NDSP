#ifndef VISUALUZERWINDOW_H
#define VISUALUZERWINDOW_H

#include <QMainWindow>

namespace Ui {
class VisualuzerWindow;
}

class VisualuzerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VisualuzerWindow(QWidget *parent = nullptr);
    ~VisualuzerWindow();

    void

private:
    Ui::VisualuzerWindow *ui;
};

#endif // VISUALUZERWINDOW_H
