#include "DFEMainWindow.hpp"
#include "ui_DFEMainWindow.h"

#include "DFEViewport.hpp"

#include <QtWidgets>

DFEMainWindow::DFEMainWindow(QWidget *parent) 
    : QMainWindow(parent),
      ui(new Ui::DFEMainWindow),
      // mp_viewport(new DFEViewport()),
      mp_contentManager(new DFEContentManager()),
      mp_sceneInspector(new DFESceneInspector()),
      mp_propertiesPanel(new DFEPropertiesPanel())

{
    ui->setupUi(this);

    addDockWidget(Qt::BottomDockWidgetArea, mp_contentManager);
    addDockWidget(Qt::RightDockWidgetArea, mp_sceneInspector);
    addDockWidget(Qt::RightDockWidgetArea, mp_propertiesPanel);

    ui->menuWindow->addAction(mp_contentManager->toggleViewAction());
    ui->menuWindow->addAction(mp_sceneInspector->toggleViewAction());
    ui->menuWindow->addAction(mp_propertiesPanel->toggleViewAction());

    connect(
        ui->actionOpen_Project,
        &QAction::triggered, 
        mp_contentManager,
        &DFEContentManager::OpenDirectory
    );

    connect(mp_sceneInspector, &DFESceneInspector::ChangedProperties, this, &DFEMainWindow::ChangePropertiesHandler);

    // Демонстрация Inspector и PropertiesPanel

    std::shared_ptr<IDFESceneObject> obj_item_1(new MocSceneObject("Item 1"));
    std::shared_ptr<IDFESceneObject> obj_item_2(new MocSceneObject("Item 2"));
    std::shared_ptr<IDFESceneObject> obj_item_3(new MocSceneObject("Item 3"));
    std::shared_ptr<IDFESceneObject> obj_item_4(new MocSceneObject("Item 4"));

    std::shared_ptr<IDFESceneObject> obj_item_2_child(new MocSceneObject("Item 2 child"));

    std::shared_ptr<IDFESceneObject> obj_item_2_child_child_1(new MocSceneObject("Item 2 child child 1"));
    std::shared_ptr<IDFESceneObject> obj_item_2_child_child_2(new MocSceneObject("Item 2 child child 2"));
    std::shared_ptr<IDFESceneObject> obj_item_2_child_child_3(new MocSceneObject("Item 2 child child 3"));

    mp_sceneInspector->AddSceneObject(obj_item_1);
    mp_sceneInspector->AddSceneObject(obj_item_2);
    mp_sceneInspector->AddSceneObject(obj_item_3);
    mp_sceneInspector->AddSceneObject(obj_item_4);

    mp_sceneInspector->AddChildSceneObject(obj_item_2, obj_item_2_child);

    mp_sceneInspector->AddChildSceneObject(obj_item_2_child, obj_item_2_child_child_1);
    mp_sceneInspector->AddChildSceneObject(obj_item_2_child, obj_item_2_child_child_2);
    mp_sceneInspector->AddChildSceneObject(obj_item_2_child, obj_item_2_child_child_3);

    // RemoveObject("Item 2 child child 3");
}

DFEMainWindow::~DFEMainWindow()
{
    delete ui;
    // delete mp_viewport;
    delete mp_contentManager;
    delete mp_sceneInspector;
    delete mp_propertiesPanel;
}

void DFEMainWindow::ChangePropertiesHandler(std::shared_ptr<IDFESceneObject> &object)
{
    mp_propertiesPanel->ChangeProperties(object);
}
