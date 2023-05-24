#include "DFEViewport.hpp"
#include <iostream>
#include <QImageReader>

DFEViewport::DFEViewport(QWidget *parent) : QWidget(parent)
{
    root_dir = "/";

    m_background_color = Qt::white;
    m_border_color = Qt::black;

    setAcceptDrops(true);
}

void DFEViewport::dragEnterEvent(QDragEnterEvent *event)
{
    QString path = event->mimeData()->text();
    path = path.mid(7, path.size() - 7 + 1); // Удаляем "file://" из названия

    if (QImageReader(path).canRead())
        event->acceptProposedAction();
}

// void DFEViewport::dragMoveEvent(QDragMoveEvent *event)
// {
//    // Установка курсора в зависимости от возможности бросить объект
//    event->acceptProposedAction();
// }

void DFEViewport::dropEvent(QDropEvent *event)
{
    QString path = event->mimeData()->text();
    path = path.mid(7, path.size() - 7 + 1); // Удаляем "file://" из названия

    CreateVisibleObject(path, event->pos().x(), event->pos().y());

    event->acceptProposedAction();
}

void DFEViewport::DeleteObject(const QString &objectName)
{
    m_hierarchy.Delete(objectName);
}

void DFEViewport::ChangeRootDirectory(const QString &dir)
{
    if (QFileInfo(dir).isDir())
        root_dir = dir;
}

void DFEViewport::CreateVisibleObject(const QString &filename, int x, int y)
{
    QString name = QFileInfo(filename).fileName();
    
    if (m_hierarchy.Has(name))
    {
        int index = 0;

        while (m_hierarchy.Has(name + " (" + QString::number(index) + ")"))
            ++index;

        name = name + " (" + QString::number(index) + ")";
    }

    m_hierarchy.AddRoot(new VisibleSceneObject(name, filename, x, y));

    emit AddedObject(m_hierarchy.Get(name));
}

void DFEViewport::DrawCanvas()
{
    m_painter.setPen(m_background_color);
    m_painter.setBrush(m_background_color);
    m_painter.drawRect(0, 0, width() - 1, height() - 1);
}

void DFEViewport::DrawBorder()
{
    m_painter.setPen(m_border_color);
    m_painter.setBrush(Qt::NoBrush);
    m_painter.drawRect(0, 0, width() - 1, height() - 1);
}

void DFEViewport::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    m_painter.begin(this);

    DrawCanvas();

    m_hierarchy.Draw(m_painter);

    DrawBorder();

    update();

    m_painter.end();
}