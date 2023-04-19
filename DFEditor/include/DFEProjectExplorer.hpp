#pragma once

#include <QtWidgets>
#include <QFileSystemModel>

class DFEProjectExplorer : public QTreeView
{
    Q_OBJECT
public:
    explicit DFEProjectExplorer(QWidget *parent = nullptr);
    DFEProjectExplorer(const DFEProjectExplorer &other) = delete;
    DFEProjectExplorer(DFEProjectExplorer &&other) = delete;
    DFEProjectExplorer &operator=(const DFEProjectExplorer &other) = delete;
    DFEProjectExplorer &operator=(DFEProjectExplorer &&other) = delete;

public:
    void UpdateView(const QString &dir);

private:
    QFileSystemModel *mp_model;
};
