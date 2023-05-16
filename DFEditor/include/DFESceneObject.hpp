#pragma once

#include <QString>

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
    
    virtual IDFESO_ERR Rename(QString new_name)
    {
        if (new_name.isEmpty())
            return IDFESO_ERR::ERR_EMPTY_NAME;
        
        m_name = new_name;

        return IDFESO_ERR::SUCCESS;
    }
protected:
    QString m_name;
};

class MocSceneObject: public IDFESceneObject
{
public:
    MocSceneObject(QString name) { m_name = name; }
};

template<>
struct std::hash<IDFESceneObject>
{
    std::size_t operator()(const IDFESceneObject *&object)
    {
        return std::hash<std::string>{}(object->GetName().toStdString());
    }
};
