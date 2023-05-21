#pragma once

#include <DFScene.hpp>
#include <DFEntity.hpp>
#include <DFComponent.hpp>
#include <algorithm>
#include <map>

class DFCameraComponent : public DFComponent
{
public:
    DFCameraComponent(DFRenderSystem &render_system)
        :m_render_system(render_system), target_position(nullptr)
    {
    }

    void SetTarget(DFEntity &gameObject)
    {
        target_position = &gameObject.transform.position;
    }

    void Update()
    {
        if (!target_position)
        {
            return;
        }

        Vector2<float> topleft = *target_position;

        topleft.x = std::max(0., topleft.x - 1280 / 2.);
        topleft.y = std::max(0., topleft.y - 720 / 2.);

        topleft.x = std::min((float)2280, (float)topleft.x + 1280);
        topleft.y = std::min((float)1080, (float)topleft.y + 720);

        topleft.x = std::max(0.f, topleft.x - 1280);
        topleft.y = std::max(0.f, topleft.y - 720);

        topleft -= topleft * 2;
        m_render_system.SetOrigin(topleft);
    }

private:
    DFRenderSystem &m_render_system;
    Vector2<float> *target_position;
};

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

    void onRenderTextures(DFRenderSystem &render_system)
    {
        auto &obj = addNewObject("Camera");
        obj.addComponent(new DFCameraComponent(render_system));
        for (auto &gameObject : m_gameObjects)
        {
            gameObject.onRenderTextures(render_system);
        }
    }

    void onSceneStart(DFRenderSystem &render_system)
    {
        for (auto &gameObject : m_gameObjects)
        {
            gameObject.Start();
        }
    }

    void onHandleFrame(DFRenderSystem &render_system)
    {
        for (auto &gameObject : m_gameObjects)
        {
            gameObject.Update();
        }

        for (auto &gameObject : m_gameObjects)
        {
            gameObject.Draw(render_system);
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
        if (std::count_if(m_gameObjAliaces.begin(), m_gameObjAliaces.end(), [ & ](auto &x) {return x.first == name;}) == 0)
        {
            return nullptr;
        }
        return &m_gameObjects[m_gameObjAliaces[name]];
    }

};
