#pragma once

#include <QMainWindow>

#include "DFEContentManager.hpp"
#include "DFESceneInspector.hpp"
#include "DFEPropertiesPanel.hpp"

namespace Ui
{
    class DFEMainWindow;
}

class DFEMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DFEMainWindow(QWidget *parent = nullptr);
    DFEMainWindow(const DFEMainWindow &other) = delete;
    DFEMainWindow(DFEMainWindow &&other) = delete;
    DFEMainWindow &operator=(const DFEMainWindow &other) = delete;
    DFEMainWindow &operator=(DFEMainWindow &&other) = delete;
    ~DFEMainWindow() override;

private:
    Ui::DFEMainWindow  *ui;
    DFEContentManager  *m_contentManager;
    DFESceneInspector  *m_sceneInspector;
    DFEPropertiesPanel *m_propertiesPanel;
};
