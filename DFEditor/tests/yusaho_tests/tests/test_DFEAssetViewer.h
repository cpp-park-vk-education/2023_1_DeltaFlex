#pragma once

#include "DFEAssetViewer.hpp"
#include <QObject>
#include <QtTest>

class test_DFEAssetViewer : public QObject
{
    Q_OBJECT

public:
    explicit test_DFEAssetViewer(QObject *parent = nullptr)
        : QObject(parent)
    {
    }

private slots:
    void testUpdateView()
    {
        DFEAssetViewer *viewer = new DFEAssetViewer();
        QListView *tstView = new QListView();
        QFileSystemModel *tstModel = new QFileSystemModel();

        tstModel->setRootPath("");
        tstView->setModel(tstModel);
        tstView->setRootIndex(tstModel->index("/home"));

        viewer->UpdateView("/home");

        QVERIFY2(viewer->rootIndex().isValid(), "Viewer root index is not valid");
        QCOMPARE(viewer->GetDirByIndex(viewer->rootIndex()), tstModel->filePath(tstView->rootIndex()));

        delete viewer;
        delete tstView;
        delete tstModel;
    }
};