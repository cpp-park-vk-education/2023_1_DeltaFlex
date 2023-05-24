#pragma once

#include <iostream>
#include <QtWidgets>
#include <QButtonGroup>

enum class DFESV_ERR
{
    SUCCESS,
    ELEM_ALREADY_EXIST,
    PARENT_ELEM_NOT_EXIST,
    NO_MATCHING_ELEM
};

class DFESceneInspectorTree : public QTreeView
{
    Q_OBJECT
public:
    explicit DFESceneInspectorTree(QWidget *parent = nullptr);

    DFESV_ERR AddObject(const QString &object_name);
    DFESV_ERR AddChildObject(const QString &parent_object_name, const QString &child_object_name);
    DFESV_ERR RemoveObject(const QString &object_name);
    QStandardItem *SearchObject(const QString &object_name);
    QStandardItem *SearchObjectRec(const QString &object_name);

public slots:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void DeletedObject(const QString &object_name);

protected:

    QStandardItemModel *mp_model;
};
