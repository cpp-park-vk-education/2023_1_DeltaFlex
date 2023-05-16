#pragma once

#include <QtWidgets>
#include <vector>
#include "DFEExpandingWidget.hpp"
#include "DFESceneObject.hpp"

class DFEPropertiesPanel : public QDockWidget
{
    Q_OBJECT;
public:
    explicit DFEPropertiesPanel(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

    void ChangeProperties(std::shared_ptr<IDFESceneObject> &object);
protected:
    std::shared_ptr<IDFESceneObject> mp_object;
    std::vector<DFEExpandingWidget *>m_properties;
};
