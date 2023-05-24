#include "DFESceneInspectorTree.hpp"

DFESceneInspectorTree::DFESceneInspectorTree(QWidget *parent) : 
    QTreeView(parent),
    mp_model(new QStandardItemModel(this))
{
    setFrameShape(QFrame::NoFrame);
    setModel(mp_model);
    setDragEnabled(true);
    
    QStandardItem *empty_label_item = new QStandardItem("");
    empty_label_item->setSizeHint(QSize(0, 0));
    mp_model->setHorizontalHeaderItem(0, empty_label_item);
}

DFESV_ERR DFESceneInspectorTree::AddObject(const QString &object_name)
{
    if (SearchObjectRec(object_name))
        return DFESV_ERR::ELEM_ALREADY_EXIST;

    QStandardItem *item = new QStandardItem(object_name);

    mp_model->appendRow(item);

    return DFESV_ERR::SUCCESS;
}

DFESV_ERR DFESceneInspectorTree::AddChildObject(const QString &parent_object_name, const QString &child_object_name)
{
    if (SearchObjectRec(child_object_name))
        return DFESV_ERR::ELEM_ALREADY_EXIST;

    QStandardItem *parent_item = SearchObjectRec(parent_object_name);

    if (!parent_item)
        return DFESV_ERR::PARENT_ELEM_NOT_EXIST;

    QStandardItem *child_item = new QStandardItem(child_object_name);

    parent_item->appendRow(child_item);

    return DFESV_ERR::SUCCESS;
}

DFESV_ERR DFESceneInspectorTree::RemoveObject(const QString &object_name)
{
    QStandardItem *search_item = SearchObject(object_name);

    if (!search_item)
    {
        search_item = SearchObjectRec(object_name);

        if (!search_item)
            return DFESV_ERR::NO_MATCHING_ELEM;

        search_item->parent()->removeRow(search_item->row());

        return DFESV_ERR::SUCCESS;
    }

    mp_model->takeRow(mp_model->indexFromItem(search_item).row());

    return DFESV_ERR::SUCCESS;
}

QStandardItem *DFESceneInspectorTree::SearchObject(const QString &object_name)
{
    QList<QStandardItem *>items = mp_model->findItems(object_name);

    if (items.count())
        return items[0];
    
    return nullptr;
}

QStandardItem *DFESceneInspectorTree::SearchObjectRec(const QString &object_name)
{
    QList<QStandardItem *>items = mp_model->findItems(object_name, Qt::MatchRecursive);

    if (items.count())
        return items[0];
    
    return nullptr;
}

void DFESceneInspectorTree::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_X || event->key() == Qt::Key_Backspace)
    {
        QModelIndexList indices = selectedIndexes();

        for (int index = indices.count() - 1; index >= 0; index--)
        {
            QString object_name = indices.at(index).data().toString();

            RemoveObject(object_name);
            emit DeletedObject(object_name);
        }
    }
}
