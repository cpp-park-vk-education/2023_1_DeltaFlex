#pragma once

#include <QtWidgets>

class DFEViewport : public QGraphicsView
{
    Q_OBJECT

public:
    explicit DFEViewport(QWidget *parent);
};
