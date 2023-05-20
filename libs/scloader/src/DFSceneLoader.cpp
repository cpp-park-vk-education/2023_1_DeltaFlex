#include <DFSceneLoader.hpp>
#include <DFWorldScene.hpp>

#include <spdlog/spdlog.h>

DFSceneLoader::DFSceneLoader(const std::string &path) : m_deserializer(path), m_dynlib()
{
}


/*
size_t n_objects: 3
std::string "name", size_t components
std::string "component_name", ...data...
*/

DFScene *DFSceneLoader::Load()
{
    spdlog::set_pattern("[%H:%M:%S %z] [%^%L%$] [thread %t] %v");
    spdlog::info("Loading scene ...");
    DFWorldScene *loaded_scene = new DFWorldScene();

    size_t n_objects;
    m_deserializer >> n_objects;
    spdlog::info("objects on scene: {}", n_objects);
    for (size_t object_index = 0; object_index < n_objects; ++object_index)
    {
        std::string cur_obj_name;
        size_t cur_obj_components;

        m_deserializer >> cur_obj_name;
        DFEntity &gameObj = loaded_scene->addNewObject(cur_obj_name);
        m_deserializer >> gameObj.transform.position >> cur_obj_components;
        spdlog::info("[{}] obj: {} pos: ({}, {}), components: {}",
            object_index,
            cur_obj_name,
            gameObj.transform.position.x, gameObj.transform.position.y,
            cur_obj_components);

        for (size_t component_index = 0; component_index < cur_obj_components; ++component_index)
        {
            try
            {
                gameObj.addComponent(LoadComponent());
            }
            catch (const spdlog::spdlog_ex &e)
            {
                spdlog::error("Loading scene FAILED");
                spdlog::set_pattern("%+");
                throw e;
            }

        }
        gameObj.onInit();
    }
    spdlog::info("Loading scene OK");
    spdlog::set_pattern("%+");
    return loaded_scene;
}

/*
correct: 98 9a aa 9  f  7f 0 0 b0 6d 0 a8 e  7f 0 0 20 0 0 0 0 0 0 0 3c 0 0 0 0 0 0 0 63 65 73 2f 69 6d 61 0 0 0 0 0 0 0 0 0
wrong  : c8 fc 44 9c 91 7f 0 0 b0 6d 0 64 91 7f 0 0 20 0 0 0 0 0 0 0 3c 0 0 0 0 0 0 0 63 65 73 2f 69 6d 61 0 0 0 0 0 0 0 0 0
*/

DFComponent *DFSceneLoader::LoadComponent()
{
    std::string component_name;
    m_deserializer >> component_name;
    spdlog::info("Loading component: {}", component_name);
    DFComponent_loader_func func = (DFComponent_loader_func)m_dynlib.FindSymbol(component_name + std::string("_loader"));
    if (!func)
    {
        spdlog::throw_spdlog_ex("unable to find component: " + component_name);
    }
    spdlog::info("Loading component: {} OK", component_name);
    auto res = func(m_deserializer);
    return res;
}
