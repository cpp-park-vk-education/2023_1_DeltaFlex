#pragma once

#include <QtWidgets>
#include <QPainter>
#include <QFont>
#include <QPen>
#include "DFEHierarchy.hpp"
#include "DFESceneObject.hpp"

class DFEViewport : public QWidget
{
    using ISOPtr = std::shared_ptr<IDFESceneObject>;

    Q_OBJECT
public:
    explicit DFEViewport(QWidget *parent = nullptr);
    
public slots:
    void dragEnterEvent(QDragEnterEvent *event) override;
    // void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    void DeleteObject(const QString &objectName);
    void ChangeRootDirectory(const QString &dir);

signals:
    void AddedObject(ISOPtr &object);

private:
    void CreateVisibleObject(const QString &filename, int x, int y);

    void DrawCanvas();
    void DrawBorder();
    void paintEvent(QPaintEvent *event) override;

    DFEHierarchy m_hierarchy;
    QString root_dir;
    QString m_scene_filename;
    size_t m_height;
    size_t m_width;

    QPainter m_painter;
    QColor m_background_color;
    QColor m_border_color;
};
