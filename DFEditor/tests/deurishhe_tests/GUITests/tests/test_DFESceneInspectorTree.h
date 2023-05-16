#pragma once

#include "DFESceneInspectorTree.hpp"
#include <QObject>
#include <QtTest>

class test_DFESceneInspectorTree : public QObject
{
    Q_OBJECT

public:
    explicit test_DFESceneInspectorTree(QObject *parent = nullptr)
        : QObject(parent)
    {
    }

private slots:
    void testAddFirstObject()
    {
        DFESceneInspectorTree *scene_tree = new DFESceneInspectorTree();

        scene_tree->AddObject("First");

        QCOMPARE(scene_tree->SearchObject("First")->text(), "First");
        QCOMPARE(scene_tree->SearchObject("First")->parent(), nullptr);

        delete scene_tree;
    }

    void testAddThreeObjects()
    {
        DFESceneInspectorTree *scene_tree = new DFESceneInspectorTree();

        scene_tree->AddObject("First");
        scene_tree->AddObject("Second");
        scene_tree->AddObject("Third");

        QCOMPARE(scene_tree->SearchObject("Third")->text(), "Third");
        QCOMPARE(scene_tree->SearchObject("Second")->text(), "Second");
        QCOMPARE(scene_tree->SearchObject("First")->text(), "First");

        QCOMPARE(scene_tree->SearchObject("Third")->parent(), nullptr);
        QCOMPARE(scene_tree->SearchObject("Second")->parent(), nullptr);
        QCOMPARE(scene_tree->SearchObject("First")->parent(), nullptr);

        delete scene_tree;
    }

    void testMakeHierarchyOneChild()
    {
        DFESceneInspectorTree *scene_tree = new DFESceneInspectorTree();

        scene_tree->AddObject("Item");
        scene_tree->AddChildObject("Item", "Item child");

        QCOMPARE(scene_tree->SearchObjectRec("Item")->text(), "Item");
        QCOMPARE(scene_tree->SearchObjectRec("Item child")->text(), "Item child");

        QCOMPARE(scene_tree->SearchObjectRec("Item")->parent(), nullptr);
        QCOMPARE(scene_tree->SearchObjectRec("Item child")->parent(), scene_tree->SearchObjectRec("Item"));

        delete scene_tree;
    }

    void testMakeHierarchyThreeChilds()
    {
        DFESceneInspectorTree *scene_tree = new DFESceneInspectorTree();

        scene_tree->AddObject("Item");
        scene_tree->AddChildObject("Item", "Item child 1");
        scene_tree->AddChildObject("Item", "Item child 2");
        scene_tree->AddChildObject("Item", "Item child 3");

        QCOMPARE(scene_tree->SearchObjectRec("Item")->text(), "Item");
        QCOMPARE(scene_tree->SearchObjectRec("Item child 1")->text(), "Item child 1");
        QCOMPARE(scene_tree->SearchObjectRec("Item child 2")->text(), "Item child 2");
        QCOMPARE(scene_tree->SearchObjectRec("Item child 3")->text(), "Item child 3");

        QCOMPARE(scene_tree->SearchObjectRec("Item")->parent(), nullptr);
        QCOMPARE(scene_tree->SearchObjectRec("Item child 1")->parent(), scene_tree->SearchObjectRec("Item"));
        QCOMPARE(scene_tree->SearchObjectRec("Item child 2")->parent(), scene_tree->SearchObjectRec("Item"));
        QCOMPARE(scene_tree->SearchObjectRec("Item child 3")->parent(), scene_tree->SearchObjectRec("Item"));

        delete scene_tree;
    }

    void testMakeHierarchyThreeLevels()
    {
        DFESceneInspectorTree *scene_tree = new DFESceneInspectorTree();

        scene_tree->AddObject("Item");
        scene_tree->AddChildObject("Item", "Item child");
        scene_tree->AddChildObject("Item child", "Item child child");

        QCOMPARE(scene_tree->SearchObjectRec("Item")->text(), "Item");
        QCOMPARE(scene_tree->SearchObjectRec("Item child")->text(), "Item child");
        QCOMPARE(scene_tree->SearchObjectRec("Item child child")->text(), "Item child child");

        QCOMPARE(scene_tree->SearchObjectRec("Item")->parent(), nullptr);
        QCOMPARE(scene_tree->SearchObjectRec("Item child")->parent(), scene_tree->SearchObjectRec("Item"));
        QCOMPARE(scene_tree->SearchObjectRec("Item child child")->parent(), scene_tree->SearchObjectRec("Item child"));

        delete scene_tree;
    }

    void testMakeHierarchyFourLevels()
    {
        DFESceneInspectorTree *scene_tree = new DFESceneInspectorTree();

        scene_tree->AddObject("Item");
        scene_tree->AddChildObject("Item", "Item child");
        scene_tree->AddChildObject("Item child", "Item child child 1");
        scene_tree->AddChildObject("Item child", "Item child child 2");
        scene_tree->AddChildObject("Item child child 1", "Item child child child");

        QCOMPARE(scene_tree->SearchObjectRec("Item")->text(), "Item");
        QCOMPARE(scene_tree->SearchObjectRec("Item child")->text(), "Item child");
        QCOMPARE(scene_tree->SearchObjectRec("Item child child 1")->text(), "Item child child 1");
        QCOMPARE(scene_tree->SearchObjectRec("Item child child 2")->text(), "Item child child 2");
        QCOMPARE(scene_tree->SearchObjectRec("Item child child child")->text(), "Item child child child");

        QCOMPARE(scene_tree->SearchObjectRec("Item")->parent(), nullptr);
        QCOMPARE(scene_tree->SearchObjectRec("Item child")->parent(), scene_tree->SearchObjectRec("Item"));
        QCOMPARE(scene_tree->SearchObjectRec("Item child child 1")->parent(), scene_tree->SearchObjectRec("Item child"));
        QCOMPARE(scene_tree->SearchObjectRec("Item child child 2")->parent(), scene_tree->SearchObjectRec("Item child"));
        QCOMPARE(scene_tree->SearchObjectRec("Item child child child")->parent(), scene_tree->SearchObjectRec("Item child child 1"));

        delete scene_tree;
    }
};