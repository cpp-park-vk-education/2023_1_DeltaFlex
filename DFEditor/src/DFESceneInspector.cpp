#include "DFESceneInspector.hpp"

DFESceneInspector::DFESceneInspector(QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(parent, flags),
      m_sceneView(new DFESceneView(this))
{
    setWidget(m_sceneView);
    setWindowTitle("Scene Inspector");
}

DFESceneInspector::~DFESceneInspector()
{
    delete m_sceneView;
}
