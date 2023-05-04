#pragma once

#include <QWidget>
#include <QDockWidget>
#include <QStandardItemModel>
#include <memory>
#include <unordered_map>
#include "DFESceneView.hpp"
#include "DFESceneObject.hpp"

enum class DFESI_ERR
{
    SUCCESS,
    REPEATED_NAME,
    PARENT_NOT_EXIST
};

class DFESceneInspector : public QDockWidget
{
    Q_OBJECT

public:
    explicit DFESceneInspector(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

    DFESI_ERR AddSceneObject(std::shared_ptr<IDFESceneObject> &new_object);
    DFESI_ERR AddChildSceneObject(std::shared_ptr<IDFESceneObject> &parent_object, std::shared_ptr<IDFESceneObject> &child_object);
public slots:
    void ChangePropertiesHandler(const QModelIndex &index);
signals:
    void ChangedProperties(std::shared_ptr<IDFESceneObject> &object);
protected:
    DFESceneView *mp_sceneView;
    std::unordered_map<QString, std::shared_ptr<IDFESceneObject>> m_objects;
};
