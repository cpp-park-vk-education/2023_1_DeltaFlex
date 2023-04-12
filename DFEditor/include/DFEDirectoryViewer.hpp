#pragma once

#include <QtWidgets>

class DFEDirectoryViewer : public QWidget
{
    Q_OBJECT
public:
    explicit DFEDirectoryViewer(QWidget *parent);
    ~DFEDirectoryViewer();

private:
    QLineEdit *m_pathEdit;
    QTreeView *m_explorer;

    QVBoxLayout *m_verticalLayout;

    QString m_path;
};
