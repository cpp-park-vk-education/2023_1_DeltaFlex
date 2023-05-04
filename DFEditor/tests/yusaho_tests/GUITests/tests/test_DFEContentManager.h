#pragma once

#include "DFEContentManager.hpp"

#include <QtWidgets>
#include <QtTest>
#include <QObject>

class DFEContentManagerWrapper : public DFEContentManager
{
public:
    DFEContentManagerWrapper(QWidget *parent = nullptr)
        : DFEContentManager(parent)
    {
    }

    DFEAssetViewer *GetAssetViewer()
    {
        return mp_assetViewer;
    }

    DFEProjectExplorer *GetProjectExplorer()
    {
        return mp_projectExplorer;
    }
};

class test_DFEContentManager : public QObject
{
    Q_OBJECT
public:
    explicit test_DFEContentManager(QObject *parent = nullptr)
        : QObject(parent)
    {
    }

private slots:
    void testConstructor()
    {
        DFEContentManagerWrapper *obj = new DFEContentManagerWrapper();

        QCOMPARE(obj->windowTitle(), "Content Manager");
        QVERIFY2(obj->widget() != 0, "Internal widget was not initialized properly");
        delete obj;
    }
};
