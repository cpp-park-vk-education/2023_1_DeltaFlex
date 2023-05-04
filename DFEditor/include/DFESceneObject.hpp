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

    QString GetName() { return m_name; }
    
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
