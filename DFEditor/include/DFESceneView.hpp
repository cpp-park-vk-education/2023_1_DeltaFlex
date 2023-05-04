#pragma once

#include <QtWidgets>
#include <QButtonGroup>

enum class DFESV_ERR
{
    SUCCESS,
    ELEM_ALREADY_EXIST,
    PARENT_ELEM_NOT_EXIST,
    NO_MATCHING_ELEM
};

class DFESceneView : public QTreeView
{
    Q_OBJECT
public:
    explicit DFESceneView(QWidget *parent = nullptr);

    DFESV_ERR AddObject(QString object_name);
    DFESV_ERR AddChildObject(QString parent_object_name, QString child_object_name);
    DFESV_ERR RemoveObject(QString object_name);
protected:
    QStandardItem *SearchObject(QString object_name);
    QStandardItem *SearchObjectRec(QString object_name);

    QStandardItemModel *mp_model;
};
