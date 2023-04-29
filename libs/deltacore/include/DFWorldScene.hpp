#pragma once

#include <DFScene.hpp>
#include <DFEntity.hpp>

class DFWorldScene: public DFScene
{
private:
    std::vector<DFEntity> m_gameobjects;
public:
    DFWorldScene()
    {
        m_gameobjects.reserve(300);
    }
    void onRenderTextures(DFScUpdParams_t &render_data)
    {
        for (auto &gameObject: m_gameobjects)
        {
            gameObject.onRenderTextures(render_data);
        }
    }

    void onSceneStart(DFScUpdParams_t &render_data)
    {
    }

    void onHandleFrame(DFScUpdParams_t &render_data)
    {
        for (auto &gameObject: m_gameobjects)
        {
            gameObject.Update();
        }

        for (auto &gameObject: m_gameobjects)
        {
            gameObject.Draw(render_data);
        }
    }

    DFEntity& addNewObject()
    {
        m_gameobjects.emplace_back();
        return m_gameobjects.back();
    }
};
