#pragma once

#include <QMainWindow>

#include "DFEContentManager.hpp"

namespace Ui
{
    class DFEMainWindow;
}

class DFEMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DFEMainWindow(QWidget *parent = nullptr);
    DFEMainWindow(const DFEMainWindow &other) = delete;
    ~DFEMainWindow() override;

private:
    Ui::DFEMainWindow *ui;
    DFEContentManager *m_contentManager;
};
