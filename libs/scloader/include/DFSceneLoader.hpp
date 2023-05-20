#pragma once

#include "DFBinaryDeserializer.hpp"
#include "DFLazyLibraryLoader.hpp"

#include <DFScene.hpp>
#include <DFEntity.hpp>
#include <DFComponent.hpp>

#include <map>

using DFComponent_loader_func = DFComponent * (*)(DFBinaryDeserializer &);
class DFSceneLoader
{
public:
    DFSceneLoader(const std::string &path);
    DFScene *Load();

private:
    DFComponent *LoadComponent();

    DFBinaryDeserializer m_deserializer;
    DFLazyLibraryLoader m_dynlib;
};