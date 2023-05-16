#pragma once

#include <QtWidgets>
#include "DFEHierarchy.hpp"
#include "DFESceneObject.hpp"

class DFEViewport : public QGraphicsView
{
    Q_OBJECT

public:
    explicit DFEViewport(QWidget *parent = nullptr);
private:
    DFEHierarchy<IDFESceneObject> m_hierarchy;
};
