#include "DFESceneInspector.hpp"

DFESceneInspector::DFESceneInspector(QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(parent, flags),
      mp_sceneTree(new DFESceneInspectorTree(this))
{
    setWidget(mp_sceneTree);
    setWindowTitle("Scene Inspector");

    connect(mp_sceneTree, &DFESceneInspectorTree::clicked, this, &DFESceneInspector::ChangePropertiesHandler);
}

DFESI_ERR DFESceneInspector::AddSceneObject(std::shared_ptr<IDFESceneObject> &new_object)
{
    if (m_objects[new_object->GetName()])
        return DFESI_ERR::REPEATED_NAME;

    m_objects[new_object->GetName()] = new_object;
    mp_sceneTree->AddObject(new_object->GetName());

    return DFESI_ERR::SUCCESS;
}

DFESI_ERR DFESceneInspector::AddChildSceneObject(std::shared_ptr<IDFESceneObject> &parent_object, std::shared_ptr<IDFESceneObject> &child_object)
{
    if (m_objects[child_object->GetName()])
        return DFESI_ERR::REPEATED_NAME;

    if (!m_objects[parent_object->GetName()])
        return DFESI_ERR::PARENT_NOT_EXIST;

    m_objects[child_object->GetName()] = child_object;
    mp_sceneTree->AddChildObject(parent_object->GetName(), child_object->GetName());

    return DFESI_ERR::SUCCESS;
}

bool DFESceneInspector::HasObject(const QString &object_name) const
{
    return static_cast<bool>(m_objects.count(object_name));
}

void DFESceneInspector::ChangePropertiesHandler(const QModelIndex &index)
{
    emit ChangedProperties(m_objects[index.data().toString()]);
}
