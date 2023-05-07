#pragma once

#include "DFESceneInspector.hpp"
#include <QObject>
#include <QtTest>
#include <memory>

class test_DFESceneInspector : public QObject
{
    Q_OBJECT

public:
    explicit test_DFESceneInspector(QObject *parent = nullptr)
        : QObject(parent)
    {
    }

private slots:
    void testAddFirstObject()
    {
        DFESceneInspector *inspector = new DFESceneInspector();

        std::shared_ptr<IDFESceneObject>object(new MocSceneObject("Abc"));

        inspector->AddSceneObject(object);

        QCOMPARE(inspector->HasObject(object->GetName()), true);

        delete inspector;
    }
};