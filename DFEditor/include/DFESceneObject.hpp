#pragma once

#include <string>

enum class IDFESO_ERR
{
    SUCCESS,
    ERR_EMPTY_NAME
};

class IDFESceneObject
{
public:
    IDFESceneObject() = default;

    QString get_name() { return m_name; }
    
    virtual IDFESO_ERR rename(QString new_name)
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
