#pragma once

#include <DFComponent.hpp>
#include <DFScUpdParams.hpp>
#include <DFTransform.hpp>

#include <vector>
#include <typeinfo>

#include <iostream>
#include <utility>

class DFEntity
{
private:
    std::vector<DFComponent *> m_components;

public:
    DFTransform transform;

    DFEntity() = default;
    DFEntity(const DFEntity &other) = delete;

    DFEntity(DFEntity &&other)
    {
        m_components = std::exchange(other.m_components, {0});
    };

    void onRenderTextures(DFScUpdParams_t &render_data) {};

    void Update()
    {
        for (auto component : m_components)
        {
            component->Update();
        }
    };

    void Draw(DFScUpdParams_t &render_data)
    {
        for (auto component : m_components)
        {
            component->Draw(render_data);
        }
    };

    void onInit()
    {
        for (auto component : m_components)
            component->onInit(*this);
    }

    template<typename T> T *getComponent()
    {
        for (auto component : m_components)
        {
            if (typeid(*component) == typeid(T))
            {
                return dynamic_cast<T *>(component);
            }
        }
        return nullptr;
    }

    void addComponent(DFComponent *component)
    {
        m_components.push_back(component);
    }

    ~DFEntity()
    {
        for (size_t i = 0; i < m_components.size(); ++i)
        {
            delete m_components[i];
        }
    }
};