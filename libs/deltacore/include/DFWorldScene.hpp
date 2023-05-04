#pragma once

#include <DFScene.hpp>
#include <DFEntity.hpp>
#include <algorithm>
#include <map>
class DFWorldScene : public DFScene
{
private:
    friend DFEntity;
    std::vector<DFEntity> m_gameObjects;
    std::map<std::string, size_t> m_gameObjAliaces;
public:
    DFWorldScene()
    {
        m_gameObjects.reserve(300);
    }

    void onRenderTextures(DFScUpdParams_t &render_data)
    {
        for (auto &gameObject : m_gameObjects)
        {
            gameObject.onRenderTextures(render_data);
        }
    }

    void onSceneStart(DFScUpdParams_t &render_data)
    {
        for (auto &gameObject : m_gameObjects)
        {
            gameObject.Start();
        }
    }

    void onHandleFrame(DFScUpdParams_t &render_data)
    {
        for (auto &gameObject : m_gameObjects)
        {
            gameObject.Update();
        }

        for (auto &gameObject : m_gameObjects)
        {
            gameObject.Draw(render_data);
        }
    }

    DFEntity &addNewObject(std::string name)
    {
        m_gameObjects.emplace_back();
        DFEntity &to_ret = m_gameObjects.back();
        m_gameObjAliaces[name] = m_gameObjects.size() - 1;
        return to_ret;
    }

    DFEntity *findEntity(std::string &&name)
    {
        return findEntity(name);
    }

    DFEntity *findEntity(std::string &name)
    {
        if(std::count_if(m_gameObjAliaces.begin(), m_gameObjAliaces.end(), [&](auto &x){return x.first == name;}) == 0)
        {
            return nullptr;
        }
        return &m_gameObjects[m_gameObjAliaces[name]];
    }

};
