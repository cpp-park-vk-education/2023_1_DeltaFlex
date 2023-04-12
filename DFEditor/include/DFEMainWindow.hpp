#pragma once

#include <QMainWindow>

namespace Ui
{
    class DFEMainWindow;
}

class DFEMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DFEMainWindow(QWidget *parent = nullptr);
    ~DFEMainWindow() override;

private:
    Ui::DFEMainWindow *ui;
};
