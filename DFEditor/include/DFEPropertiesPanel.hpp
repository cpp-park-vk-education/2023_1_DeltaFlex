#pragma once

#include <QtWidgets>
#include "DFEExpandingWidget.hpp"

class DFEPropertiesPanel : public QDockWidget
{
    Q_OBJECT;
public:
    explicit DFEPropertiesPanel(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~DFEPropertiesPanel();
private:
    DFEExpandingWidget *m_test;
};
