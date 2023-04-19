#include "DFESceneInspector.hpp"

DFESceneInspector::DFESceneInspector(QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(parent, flags),
      mp_sceneView(new DFESceneView())
{
    setWidget(mp_sceneView);
    setWindowTitle("Scene Inspector");
}

DFESceneInspector::~DFESceneInspector()
{
    delete mp_sceneView;
}
