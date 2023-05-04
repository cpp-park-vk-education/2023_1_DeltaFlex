#include "DFESceneInspector.hpp"

DFESceneInspector::DFESceneInspector(QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(parent, flags),
      mp_sceneView(new DFESceneView(this))
{
    setWidget(mp_sceneView);
    setWindowTitle("Scene Inspector");

    connect(mp_sceneView, &DFESceneView::clicked, this, &DFESceneInspector::ChangePropertiesHandler);
}

DFESI_ERR DFESceneInspector::AddSceneObject(std::shared_ptr<IDFESceneObject> &new_object)
{
    if (m_objects[new_object->get_name()])
        return DFESI_ERR::REPEATED_NAME;

    m_objects[new_object->get_name()] = new_object;
    mp_sceneView->AddObject(new_object->get_name());

    return DFESI_ERR::SUCCESS;
}

DFESI_ERR DFESceneInspector::AddChildSceneObject(std::shared_ptr<IDFESceneObject> &parent_object, std::shared_ptr<IDFESceneObject> &child_object)
{
    if (m_objects[child_object->get_name()])
        return DFESI_ERR::REPEATED_NAME;

    if (!m_objects[parent_object->get_name()])
        return DFESI_ERR::PARENT_NOT_EXIST;

    m_objects[child_object->get_name()] = child_object;
    mp_sceneView->AddChildObject(parent_object->get_name(), child_object->get_name());

    return DFESI_ERR::SUCCESS;
}

void DFESceneInspector::ChangePropertiesHandler(const QModelIndex &index)
{
    emit ChangedProperties(m_objects[index.data().toString()]);
}