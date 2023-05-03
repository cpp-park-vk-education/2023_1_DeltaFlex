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

    std::string get_name() { return m_name; }
    
    virtual IDFESO_ERR rename(std::string new_name)
    {
        if (new_name.empty())
            return IDFESO_ERR::ERR_EMPTY_NAME;
        
        m_name = new_name;

        return IDFESO_ERR::SUCCESS;
    }
protected:
    std::string m_name;
};

class MocSceneObject: public IDFESceneObject
{
public:
    MocSceneObject(std::string name) { m_name = name; }
};
