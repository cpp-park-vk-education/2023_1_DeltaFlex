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

    void SetTarget(Vector2<float> &pos)
    {
        std::cout << "set_target" << (void *)&pos << "\n";
        target_position = &pos;
    }

    void Update()
    {
        if (!target_position)
        {
            return;
        }

        // std::cout << *target_position << "\n";

        Vector2<float> topleft = *target_position;

        topleft.x = std::max(0.f, topleft.x - 1280.f / 2.f);
        topleft.y = std::max(0.f, topleft.y - 720.f / 2.f);

        topleft.x = std::min(2280.f, topleft.x + 1280.f);
        topleft.y = std::min(720.f, topleft.y + 720.f);

        topleft.x = std::max(0.f, topleft.x - 1280);
        topleft.y = std::max(0.f, topleft.y - 720);

        topleft.x = -topleft.x;
        topleft.y = -topleft.y;
        // topleft -= topleft * 2;;
        m_render_system.SetOrigin(topleft);
    }

    void Draw(DFRenderSystem &render_system)
    {
        if (!target_position)
            return;
        render_system.SetColor(255, 255, 255);
        render_system.RenderCircle(target_position->x, target_position->y, 10);
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
        for (auto &gameObject : m_gameObjects)
        {
            gameObject.onRenderTextures(render_system);
        }
        auto &obj = addNewObject("Camera");
        obj.addComponent(new DFCameraComponent(render_system));
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
        if (std::count_if(m_gameObjAliaces.begin(), m_gameObjAliaces.end(), [&](auto &x) {return x.first == name; }) == 0)
        {
            return nullptr;
        }
        return &m_gameObjects[m_gameObjAliaces[name]];
    }

};
