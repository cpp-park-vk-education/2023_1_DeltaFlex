#pragma once

#include <QWidget>
#include <QDockWidget>
#include "DFESceneView.hpp"

class DFESceneInspector : public QDockWidget
{
public:
    explicit DFESceneInspector(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    DFESceneInspector(const DFESceneInspector &other)               = delete;
    DFESceneInspector(DFESceneInspector &&other)                    = delete;
    DFESceneInspector &operator=(const DFESceneInspector &other)    = delete;
    DFESceneInspector &operator=(DFESceneInspector &&other)         = delete;
    ~DFESceneInspector();

protected:
    DFESceneView *mp_sceneView;
};
