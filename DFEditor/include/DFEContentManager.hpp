#pragma once

#include <QtWidgets>
#include <QDockWidget>

#include "DFEProjectExplorer.hpp"
#include "DFEAssetViewer.hpp"

class DFEContentManager : public QDockWidget
{
    Q_OBJECT
public:
    explicit DFEContentManager(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    DFEContentManager(const DFEContentManager &other) = delete;
    DFEContentManager(DFEContentManager &&other) = delete;
    DFEContentManager &operator=(const DFEContentManager &other) = delete;
    DFEContentManager &operator=(const DFEContentManager &&other) = delete;
    ~DFEContentManager();

private:
    DFEProjectExplorer *m_projectExplorer;
    DFEAssetViewer *m_assetViewer;
};
