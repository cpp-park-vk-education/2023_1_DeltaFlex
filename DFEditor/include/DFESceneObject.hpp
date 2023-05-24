#pragma once

#include <iostream>
#include <QString>
#include <QPainter>

enum class IDFESO_ERR
{
    SUCCESS,
    ERR_EMPTY_NAME
};

class IDFESceneObject
{
public:
    IDFESceneObject() = default;

    QString GetName() const { return m_name; }
    std::string GetSName() const { return m_name.toStdString(); }
    
    virtual IDFESO_ERR Rename(const QString &new_name)
    {
        if (new_name.isEmpty())
            return IDFESO_ERR::ERR_EMPTY_NAME;
        
        m_name = new_name;

        return IDFESO_ERR::SUCCESS;
    }

    virtual void Draw(QPainter &painter) const
    {
    }

protected:
    QString m_name;
};

class MocSceneObject: public IDFESceneObject
{
public:
    MocSceneObject(const QString &name) { m_name = name; }
};

class VisibleSceneObject : public IDFESceneObject
{
public:
    VisibleSceneObject(const QString &name, const QString &path, int x, int y)
    {
        m_name = name;
        m_path = path;

        image.load(path);

        m_x = x;
        m_y = y;
    }

    void Draw(QPainter &painter) const override
    {
        if (!image.isNull())
        {
            painter.drawImage(m_x, m_y, image);
        }
    }
private:
    QImage image;
    QString m_path;
    int m_x;
    int m_y;
};
