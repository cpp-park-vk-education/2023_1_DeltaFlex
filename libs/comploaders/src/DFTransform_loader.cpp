#include <DFTransform.hpp>

#include "../../../game/include/menu/MainMenuBack.hpp"
#include "../../../game/include/menu/MainMenuButtons.hpp"

#include <DFBinaryDeserializer.hpp>

extern "C"
{
    DFComponent *DFTransform_loader(DFBinaryDeserializer &bds)
    {
        DFTransform *result = new DFTransform();
        bds.Deserialize(result->position);
        return result;
    }


    DFComponent *MainMenuBack_loader(DFBinaryDeserializer &bds)
    {
        MainMenuBack *result = new MainMenuBack();
        bds.Deserialize(result->img_path);
        return result;
    }

    DFComponent *MainMenuPlay_loader(DFBinaryDeserializer &bds)
    {
        MainMenuPlay *result = new MainMenuPlay();
        bds.Deserialize(result->img_path);
        bds.Deserialize(result->halign);
        return result;
    }

    DFComponent *MainMenuOptions_loader(DFBinaryDeserializer &bds)
    {
        MainMenuOptions *result = new MainMenuOptions();
        bds.Deserialize(result->img_path);
        bds.Deserialize(result->halign);
        return result;
    }

    DFComponent *MainMenuExit_loader(DFBinaryDeserializer &bds)
    {
        MainMenuExit *result = new MainMenuExit();
        bds.Deserialize(result->img_path);
        bds.Deserialize(result->halign);
        return result;
    }
}