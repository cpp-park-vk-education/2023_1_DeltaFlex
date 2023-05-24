#pragma once

#include "DFEProjectExplorer.hpp"
#include <QtTest>
#include <QObject>
#include <QtWidgets>

class DFEProjectExplorerWrapper : public DFEProjectExplorer
{
public:
    DFEProjectExplorerWrapper(QWidget *parent = nullptr)
        : DFEProjectExplorer(parent)
    {
    }

    QFileSystemModel *GetModel()
    {
        return mp_model;
    }
};


class test_DFEProjectExplorer : public QObject
{
    Q_OBJECT

public:
    test_DFEProjectExplorer(QObject *parent = nullptr)
        : QObject(parent)
    {
    }

private slots:
    void testConsructor()
    {
        DFEProjectExplorerWrapper *obj = new DFEProjectExplorerWrapper();

        QVERIFY2(obj->GetModel() != nullptr, "Model was not initialized properly");
        QCOMPARE(obj->GetModel()->rootPath(), "");

        delete obj;
    }

    void testUpdateView()
    {
        const QString TEST_DIR{"."};
        DFEProjectExplorerWrapper *obj = new DFEProjectExplorerWrapper();

        obj->UpdateView(TEST_DIR);
        auto index = obj->rootIndex();
        
        QFileSystemModel *model = new QFileSystemModel();
        model->setRootPath("");

        QCOMPARE(obj->GetDirByIndex(index), model->filePath(model->index(TEST_DIR)));

        delete obj;
        delete model;
    }

    void testExpandDirectory()
    {
        const QString TEST_DIR{"."};

        DFEProjectExplorerWrapper *obj = new DFEProjectExplorerWrapper();

        obj->ExpandDirectory(TEST_DIR);
        auto index = obj->GetModel()->index(TEST_DIR);
        QVERIFY2(obj->isExpanded(index), "Test folder was not expanded");

        delete obj;
    }    
};