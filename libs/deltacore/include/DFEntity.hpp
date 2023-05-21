#pragma once

#include <DFComponent.hpp>
#include <DFScUpdParams.hpp>
#include <DFTransform.hpp>
#include <DFSceneManager.hpp>

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
        m_components = std::exchange(other.m_components, { 0 });
    };

    void onRenderTextures(DFRenderSystem &render_system)
    {
        // std::cout << "initing nigga" << m_components.size() << "\n";
        for (auto component : m_components)
        {
            // std::cout << (void *)component << " " << "\n";
            // MainMenuBack *test = (MainMenuBack*)component;
            // std::cout << test->img_path << "\n";
            // std::cout << typeid(*component).name() << "\n";
            component->onRenderTextures(render_system);
        }
    };

    void Update()
    {
        for (auto component : m_components)
        {
            component->Update();
        }
    };

    void Start()
    {
        for (auto component : m_components)
        {
            component->Start();
        }
    }

    void Draw(DFRenderSystem &render_system)
    {
        for (auto component : m_components)
        {
            component->Draw(render_system);
        }
    };

    void onInit()
    {
        for (auto component : m_components)
        {
            component->onInit(*this);
        }
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

    static DFEntity *Find(std::string name)
    {
        return DFSceneManager::Instance->activeScene.get()->findEntity(name);
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